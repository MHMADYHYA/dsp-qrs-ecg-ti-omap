# Real-Time ECG QRS Detection on TI OMAP-L138 DSP

## Overview

Embedded DSP project for real-time ECG processing, QRS/R-peak detection, RR interval estimation, and BPM logging on a TI OMAP-L138 / C674x platform.

## Technical Highlights

- 225 Hz ECG sampling pipeline.
- IIR biquad filtering and derivative-based QRS detection.
- Adaptive thresholding based on recent R-peak behavior.
- 250 ms refractory guard to reduce double detections.
- Circular buffers for real-time sample and beat logging.

## Tech Stack

C, TI-RTOS/SYS-BIOS, Code Composer Studio, TI OMAP-L138, C674x DSP

## Results

- 336-sample buffer covers about 1.5 seconds of ECG data.
- Beat log stores P, Q, R, S, T amplitudes, RR interval, and BPM.
- Structured for TI-RTOS/SYS-BIOS with hardware/software interrupt separation.

## How to Run or Review

- Open `ccs_project` in Code Composer Studio.
- Build for the OMAP-L138 / C674x target.
- Review `src/main_QRS.c` for the detection pipeline.

## Public Portfolio Notes

- This repository is prepared as a clean public GitHub portfolio version.
- Original course reports that contain student IDs or private details are not committed.
- The committed material focuses on source code, safe visuals, result screenshots, and a technical summary.
