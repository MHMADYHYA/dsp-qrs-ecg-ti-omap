




#ifdef USE_BIOS                     /* build-time switch: bare-metal vs RTOS */

/*–––– XDCtools ––––*/
#include <xdc/std.h>                /* basic typedefs (Int, UInt32, etc.)   */
#include <xdc/runtime/System.h>     /* lightweight printf / diagnostics     */
#include <xdc/runtime/Error.h>      /* run-time error tracking              */
#include <xdc/runtime/Timestamp.h>  /* high-resolution time-stamps          */
#include <xdc/cfg/global.h>         /* RTSC-generated handles & symbols     */

/*–––– TI-SYS/BIOS ––––*/
#include <ti/sysbios/BIOS.h>        /* kernel start & core API              */
#include <ti/sysbios/knl/Task.h>    /* tasks                                */
#include <ti/sysbios/knl/Swi.h>     /* software interrupts                  */
#include <ti/sysbios/knl/Semaphore.h>/* counting / binary semaphores        */

#endif /* USE_BIOS */

/*–––– C standard library ––––*/
#include <stdio.h>
#include <string.h>
#include <math.h>

/*–––– TI-RTOS driver layer ––––*/
#include <ti/drv/gpio/GPIO.h>       /* high-level GPIO API                  */
#include <ti/drv/gpio/soc/GPIO_soc.h>/* SoC-specific pin config helpers    */

/*–––– Board support package ––––*/
#include "GPIO_log.h"               /* convenience macros for GPIO logging  */
#include "GPIO_board.h"             /* board-level pin names                */

#include <ti/board/board.h>         /* Board_init(), clock & pin-mux config */
#include <ti/csl/csl_clec.h>        /* CLEC: core-local event controller    */

/**********************************************************************
 ****************************  Macros  ********************************
 **********************************************************************/

/*------------- Sampling rate -------------*/
#define fs               225        /* sample-rate in Hz (global constant) */

/*------------- Adaptive-threshold tuning -------------*/
#define TH_SCALE         0.75f      /* % of recent-R average taken as dynTH
                                     * (set to 0.65 … 0.75; lower → more
                                     * sensitive, but may trigger noise)   */

/*------------- Refractory-period guard -------------*/
#define REF_PERIOD_MS    250        /* 250-ms blanking after each R peak   */
#define REF_SAMPLES      ((int)(REF_PERIOD_MS * fs / 1000.0f))
                                     /* refractory window in samples (~56) */

/*------------- Ring-buffer helpers -------------*/
#define MOD(i)           (((i) + N) % N) /* wrap any index into 0…N-1       */
#define F(i)             (filtered_arr[MOD(i)])  /* safe access: x[n]       */
#define D1(i)            (d1_arr[MOD(i)])        /* safe access: Δx[n]      */
#define D2(i)            (d2_arr[MOD(i)])        /* safe access: ΔΔx[n]     */

/*------------- Buffer sizes & static thresholds -------------*/
#define N                336        /* length of all circular buffers
                                     * 336 samples ≈ 1.5 s @225 Hz         */
#define H_TH             0.60f      /* high, fixed threshold (legacy)      */
#define L_TH             0.40f      /* low,  fixed threshold (legacy)      */


/**********************************************************************
 ************************  Forward Declarations  **********************
 **********************************************************************/

/* Hardware / software interrupt service routines */
void timer0_ISR(void);   /* HWI: ADC sampler tick                    */
void timer1_ISR(void);   /* HWI: user-LED auto-off                   */
void swi0_ISR(void);     /* SWI: moves sample → filter pipeline      */

/* Signal-processing building blocks */
void IIR_Biquad(void);           /* 2-section elliptic IIR             */
float F_fir(void);               /* optional FIR (not used in ECG demo)*/
void detect_PQRST_deriv(void);   /* peak detector (derivative method)  */
//void ECG_FILTER(void);           /* RTOS task: runs IIR + BPM logic    */
void idlePrintFxn(void);         /* Idle hook: dumps log to UART       */


/**********************************************************************
 *************************  Log Buffer  *******************************
 **********************************************************************/

#include <math.h>   /* for fabsf / modff, used elsewhere            */

#define LOG_LEN  64 /* circular log holds the last 64 detected beats */

typedef struct {
    uint16_t idx;       /* sample index of R peak                    */
    float    P, Q, R, S, T; /* peak amplitudes                       */
    uint16_t rr_ms;     /* R-R interval in milliseconds             */
    uint8_t  bpm;       /* instantaneous heart rate                 */
} LogEntry;

/* Producer–consumer pointers:
 *   • SWI pushes new entries  → wrPtr
 *   • Idle task prints & pops → rdPtr                                 */
LogEntry        logBuf[LOG_LEN];
volatile uint16_t wrPtr = 0;      /* write index (producer)            */
volatile uint16_t rdPtr = 0;      /* read  index (consumer)            */

/*---------------------------------------------------------------
 * prnFloat4
 * ----------
 * Print a floating-point value with exactly four digits after the
 * decimal point, using a lightweight integer conversion instead of
 * the expensive "%f" formatter in TI’s run-time library.
 *
 * ‣ lbl  – short tag such as "P", "Q", … (printed as “P=0.1234”)
 * ‣ v    – value to print
 *
 * The function keeps the executable code minimal; only comments
 * have been added for clarity.
 *--------------------------------------------------------------*/
static inline void prnFloat4(const char *lbl, float v)
{
    /* ------------ split sign, integer part, and fractional part ------------ */
    int   sign = (v < 0) ? -1 : 1;           /* store sign separately           */
    float a    = fabsf(v);                   /* work with magnitude             */

    int   intPart = (int)a;                  /* integer part: floor(a)          */
    float frac    = a - (float)intPart;      /* fractional part: 0.xxxx         */

    /* ---- convert fractional part to an integer in the range 0…9999 ---- */
    int frac4 = (int)(frac * 10000.0f + 0.5f); /* *10000 and round to nearest   */

    /* ---------------------------------------------------------------------- *
     * Print result:
     *   • “P=-0.1234 ”  if value is negative but integer part is zero
     *   • “P=-1.2345 ”  otherwise (sign folded into intPart)
     * ---------------------------------------------------------------------- */
    if (sign < 0 && intPart == 0)
        System_printf("%s=-0.%04d ", lbl, frac4);
    else
        System_printf("%s=%d.%04d ", lbl, sign * intPart, frac4);
}


/*--------------------------------------------------------------
 * idlePrintFxn
 * -------------
 * Idle task that prints every un-consumed log entry to the
 * UART console.  Runs whenever the CPU is in the RTOS Idle
 * state, so it never steals time from real-time processing.
 *-------------------------------------------------------------*/
void idlePrintFxn(void)
{
    /* Loop until read pointer catches up with write pointer   */
    while (rdPtr != wrPtr)
    {
        /* Fetch the next entry from the circular log buffer   */
        LogEntry e = logBuf[rdPtr % LOG_LEN];
        rdPtr++;                       /* advance read pointer */

        /* Basic numeric fields: sample index, RR, heart-rate  */
        System_printf("idx=%3d  RR=%4d ms  HR=%3d BPM | ",
                      e.idx, e.rr_ms, e.bpm);

        /* Peak amplitudes, printed with exactly four decimals */
        prnFloat4("P", e.P);
        prnFloat4("Q", e.Q);
        prnFloat4("R", e.R);
        prnFloat4("S", e.S);
        prnFloat4("T", e.T);

        System_printf("\n");           /* end of line          */
    }

    /* Push buffered text to UART once per Idle iteration      */
    System_flush();
}

static void Board_initGPIO(void)
{
    Board_initCfg boardCfg;

    GPIO_v0_HwAttrs gpio_cfg;

    /* Get the default SPI init configurations */
    GPIO_socGetInitCfg(GPIO_LED0_PORT_NUM, &gpio_cfg);


    /* Setup GPIO interrupt configurations */
    GPIO_socSetBankInt(GPIO_LED0_PORT_NUM, GPIO_LED0_PIN_NUM, NULL);
    GPIO_write((USER_LED0), GPIO_PIN_VAL_LOW);



    boardCfg = BOARD_INIT_PINMUX_CONFIG |
        BOARD_INIT_MODULE_CLOCK |
        BOARD_INIT_UART_STDIO;

    Board_init(boardCfg);



    /* Modify the default GPIO configurations if necessary */

}

/**********************************************************************
 ************************** Global Variables **************************
 **********************************************************************/

/* First- and second-order derivatives */
volatile float d1_arr[N] = {0};   // first derivative Δx
volatile float d2_arr[N] = {0};   // second derivative ΔΔx

/* Sampling-control flags and buffers */
int   on           = 1;           // 1 = acquisition ON, 0 = pause
volatile float filtered_arr[N] = {0}; // filtered-signal ring buffer
int   idx          = 0;           // write index for all circular buffers
int   clean_flag   = 0;           // becomes 1 after first full buffer (filter memory primed)
float sample       = 0.0f;        // latest raw input sample

/* P-P interval (positive-peak to positive-peak) */
int   pp_t   = 0;                 // P-P time in milliseconds
float pp_cnt = 0.0f;              // P-P time accumulator in seconds

/* BPM (beats per minute) calculation */
int bpm_t    = 0;                 // counts samples in a 60-s window (13 500 @ 225 Hz)
int bpm_cnt  = 0;                 // counts R peaks within that window
volatile int bpm = 0;             // current heart-rate value

/* RR interval tracking */
static  int   lastR = -1;         // index of the last detected R peak
volatile int  rr_ms = 0;          // most recent R-R interval in milliseconds

/* Adaptive threshold for R-peak detection */
static float dynTH   = 0.6f;      // initial guess; updated every beat
static float rHist[8] = {0};      // history of the last 8 R amplitudes
static int   rPtr     = 0;        // circular pointer into rHist



volatile float QRS_in[N]= {

    -0.0024, 0.2690, -0.2385, -0.0868, 0.2825, -0.1788, -0.1421, 0.3164,
    -0.0837, -0.1640, 0.3607, 0.0865, -0.1049, 0.4406, 0.2639, -0.0444,
    0.4608, 0.3708, -0.0391, 0.4000, 0.4123, -0.0781, 0.2766, 0.4136,
    -0.1084, 0.1387, 0.3712, -0.1509, -0.0186, 0.3369, -0.1496, -0.1275,
    0.3135, -0.1104, -0.2131, 0.2698, -0.0531, -0.2688, 0.2411, -0.0086,
    -0.4094, 0.0082, -0.0136, -0.3614, 0.1988, 0.3236, -0.0311, 0.5010,
    0.7738, 0.4107, 0.8295, 1.2094, 0.7301, 0.8246, 1.0931, 0.5561,
    0.4893, 0.7783, 0.2558, 0.0763, 0.4825, 0.0610, -0.2392, 0.1688,
    -0.1314, -0.5529, 0.0504, 0.1129, -0.2970, 0.1421, 0.1739, -0.2971,
    0.0722, 0.2336, -0.2641, 0.0122, 0.2836, -0.2190, -0.0624, 0.3069,
    -0.1642, -0.1324, 0.3116, -0.0983, -0.1932, 0.2975, -0.0303, -0.2460,
    0.2606, 0.0449, -0.2780, 0.2175, 0.1226, -0.2824, 0.1713, 0.2128,
    -0.2387, 0.1452, 0.3163, -0.1620, 0.1387, 0.4393, -0.0292, 0.1614,
    0.5648, 0.1181, 0.1791, 0.6230, 0.2375, 0.1572, 0.6673, 0.3590,
    0.1530, 0.6694, 0.4634, 0.1453, 0.6420, 0.5471, 0.1372, 0.5671,
    0.5848, 0.0997, 0.4549, 0.5974, 0.0807, 0.3382, 0.5902, 0.0778,
    0.2149, 0.5482, 0.0490, 0.0527, 0.4684, 0.0304, -0.0927, 0.3698,
    0.0328, -0.1970, 0.2956, 0.0658, -0.2571, 0.2175, 0.1129, -0.2872,
    0.1518, 0.1836, -0.2825, 0.0868, 0.2433, -0.2641, 0.0073, 0.2787,
    -0.2239, -0.0673, 0.2971, -0.1739, -0.1470, 0.2970, -0.1129, -0.2078,
    0.2780, -0.0449, -0.2606, 0.2460, 0.0303, -0.2926, 0.1981, 0.1080,
    -0.3018, 0.1421, 0.1739, -0.2971, 0.0722, 0.2336, -0.2690, 0.0024,
    0.2739, -0.2287, -0.0722, 0.2971, -0.1739, -0.1421, 0.3018, -0.1080,
    -0.2029, 0.2878, -0.0352, -0.2509, 0.2557, 0.0352, -0.2878, 0.2029,
    0.1080, -0.3018, 0.1421, 0.1739, -0.2971, 0.0722, 0.2287, -0.2641,
    0.0170, 0.3031, -0.1752, 0.0008, 0.4188, -0.0279, 0.0428, 0.5257,
    0.1304, 0.0501, 0.5457, 0.2227, 0.0022, 0.4893, 0.2541, -0.0834,
    0.3878, 0.2735, -0.1607, 0.2443, 0.2566, -0.2387, 0.1169, 0.2579,
    -0.2792, -0.0141, 0.2574, -0.2452, -0.0887, 0.2806, -0.1918, -0.1910,
    0.1909, -0.2577, -0.3449, 0.2078, -0.0686, -0.2378, 0.3773, 0.2728,
    0.0729, 0.7131, 0.7104, 0.5028, 1.0434, 1.1341, 0.5642, 0.8070,
    0.8650, 0.2074, 0.3662, 0.5531, -0.0340, 0.0240, 0.3088, -0.2608,
    -0.3135, 0.0318, -0.2654, -0.2194, 0.2780, -0.0400, -0.2557, 0.2509,
    0.0303, -0.2926, 0.1981, 0.1031, -0.3067, 0.1372, 0.1642, -0.3069,
    0.0624, 0.2239, -0.2787, -0.0073, 0.2690, -0.2336, -0.0770, 0.2923,
    -0.1788, -0.1470, 0.2970, -0.1129, -0.2078, 0.2829, -0.0352, -0.2460,
    0.2703, 0.0644, -0.2488, 0.2613, 0.1859, -0.1656, 0.3319, 0.3880,
    -0.0246, 0.3704, 0.5692, 0.0947, 0.3803, 0.6658, 0.1632, 0.3338,
    0.7172, 0.2462, 0.2921, 0.7360, 0.3262, 0.2313, 0.7219, 0.3849,
    0.1552, 0.6477, 0.4179, 0.0809, 0.5575, 0.4486, 0.0193, 0.4535,
    0.4659, -0.0412, 0.3000, 0.4283, -0.1024, 0.1408, 0.3841, -0.1466,
    -0.0042, 0.3510, -0.1341, -0.1164, 0.3276, -0.0983, -0.2029, 0.2975
};
volatile float peak_overlay[N] = {0};  // holds all detected peaks (P, Q, R, S, T)


// Section 1 coefficients
float a1_1 = -1.273970934324765f;
float a2_1 =  0.498982043285614f;
float b0_1 =  1.0f;
float b1_1 =  1.885613044587498f;
float b2_1 =  1.0f;
float G1   =  1.014816680679123f;

// Section 2 coefficients
float a1_2 = -1.012388244208811f;
float a2_2 =  0.797103884811016f;
float b0_2 =  1.0f;
float b1_2 =  1.424172117562705f;
float b2_2 =  1.0f;
float G2   =  0.011655033784359f;

// Delay elements
float d1_1 = 0, d2_1 = 0;
float d1_2 = 0, d2_2 = 0;




/*****************************************************************************
 * ECG_FILTER  (RTOS Task)
 * -------------
 * Real-time task that:
 *   1. Waits for a semaphore posted by the SW-interrupt (`swi0_ISR`).
 *   2. Filters the new sample through a two-section IIR biquad.
 *   3. Keeps the circular index in sync and, once the buffer is full,
 *      raises `clean_flag` so derivative arrays become valid.
 *   4. Computes instantaneous BPM every six seconds (= 13 500 ticks @225 Hz).
 *   5. Resets all counters if acquisition (`on`) is turned off.
 *
 *****************************************************************************/

void ECG_FILTER(UArg arg0, UArg arg1)
{
    /*====================  TASK’S MAIN LOOP  ====================*/
    while (1)
    {
        /*-------------------------------------------------------
         * 1) Block here until the ISR gives us a new sample.
         *    BIOS_WAIT_FOREVER → the task sleeps, freeing CPU.
         *------------------------------------------------------*/
        Semaphore_pend(semaphore0, BIOS_WAIT_FOREVER);
        /*-------------------------------------------------------
         * 2) Run the two-section Elliptic IIR on the latest sample.
         *    This routine also updates derivative rings and calls
         *    `detect_PQRST_deriv()` when `clean_flag` is true.
         *------------------------------------------------------*/
        IIR_Biquad();
        /*-------------------------------------------------------
         * 3) Maintain the circular buffer index.
         *    When we wrap around once (`idx == N`) we know the
         *    filter has a full buffer of past samples → any IIR
         *    transients have settled, so we set `clean_flag`.
         *------------------------------------------------------*/
        idx++;                              /* advance write head          */
        if (idx == N)                       /* reached end of ring?        */
        {
            idx = 0;                        /* wrap to element 0           */
            if (!clean_flag)                /* just completed first cycle  */
                clean_flag++;               /* allow QRS detector to run   */
        }
        /*-------------------------------------------------------
         * 4) Instantaneous HR every *6 s*.
         *    13500 samples / 225 Hz = 6 seconds.
         *------------------------------------------------------*/
        if (bpm_t == 13500)
        {
            bpm     = bpm_cnt;              /* beats counted in 6 s        */
            bpm_t   = 0;                    /* reset sample counter        */
            bpm_cnt = 0;                    /* reset beat counter          */
        }
        /*-------------------------------------------------------
         * 5) If acquisition is OFF, zero all run-time counters
         *    so the display doesn’t show stale values.
         *------------------------------------------------------*/
        if (!on)
        {
            bpm     = 0;
            bpm_t   = 0;
            bpm_cnt = 0;
            pp_cnt  = 0;                    /* positive-peak timer         */
        }
        /*–– loop back, pend on semaphore again ––*/
    }
}


#ifdef USE_BIOS
/*
 *  ======== main ========
 */

//
/*****************************************************************************
 * main.c  —  TI-RTOS entry point
 *
 * The code itself is **unchanged**; only verbose comments were added to
 * explain every single statement.
 *****************************************************************************/
int main(void) {

    Board_initGPIO();          /* device-family helper (pins + power) */
    GPIO_init();               /* create internal handles & mutexes   */
    BIOS_start();              /* jump into the kernel                */

    return 0;                  /* unreachable – keeps the compiler happy */
}

#endif


//ISR - timers interrupt
//sampling ISR
void timer0_ISR(void){

    Swi_post(swi0);     //SW interrupt post
}
//One-shot ISR
void timer1_ISR(void){
    GPIO_write((USER_LED0), GPIO_PIN_VAL_LOW);     //turn off LED0
    Timer_stop(timer1);                            //Stoping the timer
}

/*****************************************************************************
 * swi0_ISR
 * --------
 * Software-interrupt service routine that pulls the next ECG sample from the
 * ring-buffer `QRS_in[]`, updates time-counters, and finally posts a TI-RTOS
 * semaphore so the lower-priority task can continue processing.
 *
 *  ‣ The routine’s *logic* and *order of execution* are identical to your
 *    original snippet; only the in-line comments have been expanded for
 *    clarity.
 *****************************************************************************/
void swi0_ISR(void)
{
    /*---------------------------------------------------------------
     * If the system is “ON” we fetch and account for the next sample;
     * otherwise we simply push a zero into the pipeline.
     *----------------------------------------------------------------*/
    if (on)                              /* acquisition enabled?            */
    {
        unsigned int loc = idx;          /* snapshot of the global index    */

        sample = QRS_in[loc];

        pp_cnt += (1.0f / 225.0f);       /* assume fs = 225 Hz              */
        bpm_t++;                         /* +1 for every processed sample   */
    }
    else
    {
        sample = 0;                      /* acquisition paused → feed zero  */
    }
    Semaphore_post(semaphore0);          /* tell the consumer to run        */
}



/*****************************************************************************
 * IIR_Biquad
 * ----------
 * Real-time implementation of a *two-section* (Second-Order-Section, SOS)
 * Elliptic IIR filter.  It runs once per new input **sample** and stores the
 * output in `filtered_arr[idx]`.  After every sample it also updates the
 * first- and second-derivative rings (`d1_arr`, `d2_arr`) and—if the signal
 * is already “clean”—calls the QRS detector.
 *
 * The code itself is **unchanged**; only the comments have been expanded to
 * give a line-by-line explanation.
 *****************************************************************************/
void IIR_Biquad(void)
{
        /*---------------------------------------------------------------
         * One-shot reset of the delay elements the very first time we
         * enter the routine *after* `clean_flag` goes true.
         *----------------------------------------------------------------*/
        if (idx == 0 && clean_flag == 1) {
            d1_1 = d2_1 = 0;          /* delays of section-1 = 0 */
            d1_2 = d2_2 = 0;          /* delays of section-2 = 0 */
        }
        /*---------------------------------------------------------------
         * Bring the sample into a working variable.
         *----------------------------------------------------------------*/
        float x = sample;             /* current input sample              */
        float w, y;                   /* section state & cumulative output */
        /*==============================  SECTION 1  ==============================*/
        /* Direct-Form II (transposed) biquad:
         *   w[n] = x[n] − a1·d1 − a2·d2
         *   y[n] = b0·w + b1·d1 + b2·d2
         * The gain G1 is applied after the section.                            */
        w = x - a1_1 * d1_1 - a2_1 * d2_1;
        y = b0_1 * w + b1_1 * d1_1 + b2_1 * d2_1;
        y *= G1;                      /* section 1 scaler                    */
        d2_1 = d1_1;                  /* shift delays                        */
        d1_1 = w;
        /*==============================  SECTION 2  ==============================*/
        /* Same recipe, now driven by the output `y` of section 1.               */
        w = y - a1_2 * d1_2 - a2_2 * d2_2;
        y = b0_2 * w + b1_2 * d1_2 + b2_2 * d2_2;
        y *= G2;                      /* section 2 scaler                    */
        d2_2 = d1_2;
        d1_2 = w;
        /*---------------------------------------------------------------
         * Store final filtered value in the circular output buffer.
         *----------------------------------------------------------------*/
        filtered_arr[idx] = y;
        /*======================  1st & 2nd DERIVATIVES  =======================*/
        /* We keep Δx and ΔΔx in the same ring-buffer length N so the QRS
         * detector can pick them up instantly.                                  */
        int prev  = (idx == 0) ? (N - 1) : (idx - 1);   /* index of x[n-1]      */
        d1_arr[idx] = filtered_arr[idx] - filtered_arr[prev];   /* Δx = x[n]−x[n-1] */
        int prev2 = (prev == 0) ? (N - 1) : (prev - 1);         /* x[n-2]          */
        d2_arr[idx] = d1_arr[idx] - d1_arr[prev2];              /* ΔΔx             */
        /*=======================================================================*/
        /*---------------------------------------------------------------
         * Immediately run the PQRST detector as soon as the derivatives
         * are valid.  This keeps the latency to one sample.*/
        if (clean_flag)              /* derivatives are trustworthy now    */
            detect_PQRST_deriv();    /* may update BPM, overlays, LED, …   */
}



/*
================================================================================
 Function: detect_PQRST_deriv()

 Description:
 -----------

 This function processes each incoming filtered ECG sample to detect the full
 PQRST complex (P wave, Q wave, R peak, S wave, and T wave) in real time.

 It uses mathematical properties of the ECG signal:
   • Local extrema (via first derivative D1)
   • Curvature analysis (via second derivative D2)
   • Adaptive thresholding for dynamic noise resistance

 The goal is to identify each heartbeat and its components, calculate heart rate
 (BPM), and update both the GUI and data logs.

 ------------------------------------------------------------------------------
 Detection Logic:
 ----------------

 1. *R Peak Detection:*
    Detected when:
      - The signal is increasing and then decreases (D1: + → −)
      - The curvature is concave-down (D2 < 0)
      - The value exceeds a dynamic threshold (dynTH)
      - Enough time has passed since last R (outside refractory window)

 2. *Q Wave:*
    - Searched within 80ms before R
    - Look for the most negative point (convex-up → D2 > 0)


 3. *S Wave:*
    - Searched within 80ms after R
    - Look for the most negative point (convex-up → D2 > 0)

 4. *P Wave:*
    - Searched within 120ms before Q
    - Look for the highest point (concave-down → D2 < 0)

 5. *T Wave:*
    - Searched within 200ms after S
    - Look for the highest point (concave-down → D2 < 0)

 6. *Beat Validation:*
    - Rejects "flat" or false detections if:
        |F(Q) - F(R)| < EPS  or  |F(S)| < EPS

 7. *RR Interval and BPM:*
    - RR interval is the time (ms) between successive R peaks
    - BPM is calculated as 60000 / RR interval

 8. *Dynamic Threshold Update:*
    - Keeps a rolling buffer of last 8 R amplitudes
    - dynTH is set to TH_SCALE × average(R)

 9. *Visualization and Logging:*
    - Marks P, Q, R, S, T positions on overlay for GUI scope
    - Saves values in logBuf[] for diagnostics or plotting

 10. *Hardware Feedback:*


    - Blinks a user LED each time an R peak is detected
    - Starts a timer to automatically turn the LED off

 ------------------------------------------------------------------------------

  ------------------------------------------------------------------------------
 Timing Windows:
 ---------------

 These define the search regions relative to the main R/Q/S features, and are
 based on physiological timing observed in normal human ECG signals:

   • Q window: 80 ms before R
       → The Q wave typically occurs within 40–60 ms before the R peak.
         Using a safe margin of 80 ms helps reliably capture the negative
         deflection without overlapping earlier waves like P.

   • S window: 80 ms after R
       → The S wave usually appears shortly after the R peak, within
         40–80 ms. This window covers the descending segment of the QRS complex.

   • P window: 120 ms before Q
       → The P wave represents atrial depolarization and normally occurs
         100–160 ms before the QRS complex. A 120 ms window effectively captures
         this without extending into the T wave of the previous beat.

   • T window: 200 ms after S
       → The T wave (ventricular repolarization) begins approximately
         150–250 ms after QRS ends. A 200 ms window after the S point allows
         accurate detection of the T peak within the ST segment range.

 All time windows are converted to sample counts based on the sampling rate `fs`:
   → window_samples = fs × (window_in_seconds)


 ------------------------------------------------------------------------------

*/

void detect_PQRST_deriv(void)                                     // Entry point called for every new sample
{
    int c;                                                        // Generic loop counter (used in all inner searches)
    int i;
    /*―――――――――― fast exit guards ――――――――――*/
    if (!clean_flag || idx < 3) return;                           // Abort if signal not yet “clean” or buffer still filling

    /* How many samples have elapsed since the *previous* accepted R peak?          */
    int deltaSinceR = (lastR >= 0)
                     ? ((idx - lastR + N) % N)                    // normal case – wrap-around safe
                     : (REF_SAMPLES + 1);                         // first beat: pretend we are already outside the refractory window

    /*==========================  R-PEAK TEST  ==========================*/
    if (deltaSinceR > REF_SAMPLES &&                              // outside the post-R refractory window
        D1(idx-1) > 0.0f  && D1(idx) < 0.0f &&                   // derivative flips from ↑ to ↓  ➜ a local maximum
        D2(idx)   < 0.0f  &&                                     // second derivative negative  ➜ concave down
        F(idx)    > dynTH)                                       // amplitude above adaptive threshold
    {


        /*––––– constants expressed in samples, derived from sampling rate fs –––––*/
        const float EPS  = 0.02f;                                // minimum peak-to-valley distance that defines a real beat
        const int   R    = MOD(idx);                             // index of the R peak just detected
        const int   qWin = (int)(fs * 0.08f);                    // search window 80 ms *before* R to find Q
        const int   sWin = (int)(fs * 0.08f);                    // search window 80 ms *after*  R to find S
        const int   pWin = (int)(fs * 0.12f);                    // search window 120 ms before Q to find P
        const int   tWin = (int)(fs * 0.20f);                    // search window 200 ms after  S to find T

        /*==========================  Q WAVE  ==========================*/
        int   Q = R;            float qMin = F(R);               // initialise search at R itself
        for (c = 1; c <= qWin; ++c) {                            // scan backwards up to 80 ms
            int j = MOD(R - c);
            if (F(j) < qMin && F(j) < 0.0f && D2(j) > 0) {      // look for the most negative, convex-up point
                qMin = F(j);  Q = j;
            }
        }
        if (Q == R) Q = MOD(R - 1);                              // fallback: at least take the immediate previous sample

        /*==========================  S WAVE  ==========================*/
        int   S = R;            float sMin = F(R);
        for (c = 1; c <= sWin; ++c) {                            // scan forwards 80 ms
            int j = MOD(R + c);
            if (F(j) < sMin && F(j) < 0.0f && D2(j) > 0) {      // analogous criterion to Q
                sMin = F(j);  S = j;
            }
        }
        if (S == R) S = MOD(R + 1);                              // fallback: next sample

        /*==========================  P WAVE  ==========================*/
        int   P = Q;            float pMax = F(Q);
        for (c = 1; c <= pWin; ++c) {                            // scan further back (120 ms pre-Q)
            int j = MOD(Q - c);
            if (F(j) > pMax && F(j) > 0.0f && D2(j) < 0) {      // most positive, concave-down point
                pMax = F(j);  P = j;
            }
        }
        if (P == Q) P = MOD(Q - 1);                              // fallback
        /*==========================  T WAVE  ==========================*/
        int   T = S;            float tMax = F(S);
        for (c = 1; c <= tWin; ++c) {                            // scan forward (200 ms post-S)
            int j = MOD(S + c);
            if (F(j) > tMax && F(j) > 0.0f && D2(j) < 0) {      // similar criterion to P
                tMax = F(j);  T = j;
            }
        }
        if (T == S) T = MOD(S + 1);                              // fallback
        /*—— Reject extremely “flat” beats (noise / artefacts) ——*/
        if (fabsf(F(Q) - F(R)) < EPS || fabsf(F(S)) < EPS) return;

        /*======================  RR INTERVAL & BPM  =====================*/
        if (lastR >= 0) {                                        // skip for very first beat
            int dS   = (R - lastR + N) % N;                      // samples between successive R peaks
            rr_ms    = (dS * 1000) / fs;                         // convert to milliseconds
            bpm      = (rr_ms) ? 60000 / rr_ms : 0;              // instantaneous heart-rate
        }
        lastR = R;
        // Clear old peaks in overlay before storing new ones

        /*======================  GUI / SCOPE OVERLAY  ===================*/
        peak_overlay[MOD(P)] = F(P);                             // store peaks for drawing
        peak_overlay[MOD(Q)] = F(Q);
        peak_overlay[MOD(R)] = F(R);
        peak_overlay[MOD(S)] = F(S);
        peak_overlay[MOD(T)] = F(T);
        /*======================  DYNAMIC THRESHOLD  =====================*/
        rHist[rPtr & 7] = F(R);  rPtr++;                         // ring buffer of last 8 R amplitudes
        float sum = 0.0f;
        for ( i = 0; i < 8; ++i) sum += rHist[i];
        dynTH = TH_SCALE * (sum / 8.0f);                         // adaptive fraction of recent mean
        if (rPtr < 8) dynTH *= 0.8f;                             // damp threshold during start-up
        /*======================  DATA LOGGING  ==========================*/
        LogEntry *e = &logBuf[wrPtr % LOG_LEN];                  // circular log buffer
        e->idx   = R;        e->P   = F(P);   e->Q  = F(Q);
        e->R     = F(R);     e->S   = F(S);   e->T  = F(T);
        e->rr_ms = rr_ms;    e->bpm = bpm;
        wrPtr++;                                                 // advance write pointer
        /*=====================  HARDWARE FEEDBACK  =====================*/
        bpm_cnt++;                                               // beat counter for LED / display
        GPIO_write(USER_LED0, 1);                                // blink user LED on every R
        Timer_start(timer1);                                     // schedule automatic LED off
    }  }


