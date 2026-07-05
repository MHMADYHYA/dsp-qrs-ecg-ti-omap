# Full Redacted Project Report

This public GitHub version keeps the complete technical report text while removing private identifiers such as student IDs and email addresses.

Original binary report files are intentionally not committed to the public repository because they may contain private front-matter metadata.

---

[FILE QRS/.config/xconfig_ECG/package/package.defs.h]
/*
 * Do not modify this file; it is automatically 
 * generated and any modifications will be overwritten.
 *
 * @(#) xdc-G16
 */

#ifndef xconfig_ECG__
#define xconfig_ECG__

#endif /* xconfig_ECG__ */ 

[FILE QRS/.config/xconfig_ECG/package/package_xconfig_ECG.c]
/*
 * Do not modify this file; it is automatically 
 * generated and any modifications will be overwritten.
 *
 * @(#) xdc-G16
 */

#include <xdc/std.h>

__FAR__ char xconfig_ECG__dummy__;

#define __xdc_PKGVERS null
#define __xdc_PKGNAME xconfig_ECG
#define __xdc_PKGPREFIX xconfig_ECG_

#ifdef __xdc_bld_pkg_c__
#define __stringify(a) #a
#define __local_include(a) __stringify(a)
#include __local_include(__xdc_bld_pkg_c__)
#endif

[FILE QRS/.config/xconfig_ECG/package/xconfig_ECG.java]
/*
 * Do not modify this file; it is automatically 
 * generated and any modifications will be overwritten.
 *
 * @(#) xdc-G16
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class xconfig_ECG
{
 static final String VERS = "@(#) xdc-G16\n";

 static final Proto.Elm $$T_Bool = Proto.Elm.newBool();
 static final Proto.Elm $$T_Num = Proto.Elm.newNum();
 static final Proto.Elm $$T_Str = Proto.Elm.newStr();
 static final Proto.Elm $$T_Obj = Proto.Elm.newObj();

 static final Proto.Fxn $$T_Met = new Proto.Fxn(null, null, 0, -1, false);
 static final Proto.Map $$T_Map = new Proto.Map($$T_Obj);
 static final Proto.Arr $$T_Vec = new Proto.Arr($$T_Obj);

 static final XScriptO $$DEFAULT = Value.DEFAULT;
 static final Object $$UNDEF = Undefined.instance;

 static final Proto.Obj $$Package = (Proto.Obj)Global.get("$$Package");
 static final Proto.Obj $$Module = (Proto.Obj)Global.get("$$Module");
 static final Proto.Obj $$Instance = (Proto.Obj)Global.get("$$Instance");
 static final Proto.Obj $$Params = (Proto.Obj)Global.get("$$Params");

 static final Object $$objFldGet = Global.get("$$objFldGet");
 static final Object $$objFldSet = Global.get("$$objFldSet");
 static final Object $$proxyGet = Global.get("$$proxyGet");
 static final Object $$proxySet = Global.get("$$proxySet");
 static final Object $$delegGet = Global.get("$$delegGet");
 static final Object $$delegSet = Global.get("$$delegSet");

 Scriptable xdcO;
 Session ses;
 Value.Obj om;

 boolean isROV;
 boolean isCFG;

 Proto.Obj pkgP;
 Value.Obj pkgV;

 ArrayList<Object> imports = new ArrayList<Object>();
 ArrayList<Object> loggables = new ArrayList<Object>();
 ArrayList<Object> mcfgs = new ArrayList<Object>();
 ArrayList<Object> icfgs = new ArrayList<Object>();
 ArrayList<String> inherits = new ArrayList<String>();
 ArrayList<Object> proxies = new ArrayList<Object>();
 ArrayList<Object> sizes = new ArrayList<Object>();
 ArrayList<Object> tdefs = new ArrayList<Object>();

 void $$IMPORTS()
 {
 Global.callFxn("loadPackage", xdcO, "xdc");
 Global.callFxn("loadPackage", xdcO, "xdc.corevers");
 }

 void $$OBJECTS()
 {
 pkgP = (Proto.Obj)om.bind("xconfig_ECG.Package", new Proto.Obj());
 pkgV = (Value.Obj)om.bind("xconfig_ECG", new Value.Obj("xconfig_ECG", pkgP));
 }

 void $$SINGLETONS()
 {
 pkgP.init("xconfig_ECG.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "xconfig_ECG"));
 Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xconfig_ECG/package.xs");
 om.bind("xdc.IPackage$$capsule", cap);
 Object fxn;
 fxn = Global.get(cap, "init");
 if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "xconfig_ECG"), fxn);
 fxn = Global.get(cap, "close");
 if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "xconfig_ECG"), fxn);
 fxn = Global.get(cap, "validate");
 if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "xconfig_ECG"), fxn);
 fxn = Global.get(cap, "exit");
 if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "xconfig_ECG"), fxn);
 fxn = Global.get(cap, "getLibs");
 if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "xconfig_ECG"), fxn);
 fxn = Global.get(cap, "getSects");
 if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "xconfig_ECG"), fxn);
 pkgP.bind("$capsule", cap);
 pkgV.init2(pkgP, "xconfig_ECG", Value.DEFAULT, false);
 pkgV.bind("$name", "xconfig_ECG");
 pkgV.bind("$category", "Package");
 pkgV.bind("$$qn", "xconfig_ECG.");
 pkgV.bind("$vers", Global.newArray());
 Value.Map atmap = (Value.Map)pkgV.getv("$attr");
 atmap.seal("length");
 imports.clear();
 pkgV.bind("$imports", imports);
 StringBuilder sb = new StringBuilder();
 sb.append("var pkg = xdc.om['xconfig_ECG'];\n");
 sb.append("if (pkg.$vers.length >= 3) {\n");
 sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
 sb.append("}\n");
 sb.append("if ('xconfig_ECG$$stat$base' in xdc.om) {\n");
 sb.append("pkg.packageBase = xdc.om['xconfig_ECG$$stat$base'];\n");
 sb.append("pkg.packageRepository = xdc.om['xconfig_ECG$$stat$root'];\n");
 sb.append("}\n");
 sb.append("pkg.build.libraries = [\n");
 sb.append("];\n");
 sb.append("pkg.build.libDesc = [\n");
 sb.append("];\n");
 Global.eval(sb.toString());
 }

 void $$INITIALIZATION()
 {
 Value.Obj vo;

 if (isCFG) {
 }//isCFG
 Global.callFxn("init", pkgV);
 ((Value.Arr)om.findStrict("$packages", "xconfig_ECG")).add(pkgV);
 }

 public void exec( Scriptable xdcO, Session ses )
 {
 this.xdcO = xdcO;
 this.ses = ses;
 om = (Value.Obj)xdcO.get("om", null);

 Object o = om.geto("$name");
 String s = o instanceof String ? (String)o : null;
 isCFG = s != null && s.equals("cfg");
 isROV = s != null && s.equals("rov");

 $$IMPORTS();
 $$OBJECTS();
 if (isROV) {
 }//isROV
 $$SINGLETONS();
 $$INITIALIZATION();
 }
}

[FILE QRS/.config/xconfig_gpio_test/package/package.defs.h]
/*
 * Do not modify this file; it is automatically 
 * generated and any modifications will be overwritten.
 *
 * @(#) xdc-G16
 */

#ifndef xconfig_gpio_test__
#define xconfig_gpio_test__

#endif /* xconfig_gpio_test__ */ 

[FILE QRS/.config/xconfig_gpio_test/package/package_xconfig_gpio_test.c]
/*
 * Do not modify this file; it is automatically 
 * generated and any modifications will be overwritten.
 *
 * @(#) xdc-G16
 */

#include <xdc/std.h>

__FAR__ char xconfig_gpio_test__dummy__;

#define __xdc_PKGVERS null
#define __xdc_PKGNAME xconfig_gpio_test
#define __xdc_PKGPREFIX xconfig_gpio_test_

#ifdef __xdc_bld_pkg_c__
#define __stringify(a) #a
#define __local_include(a) __stringify(a)
#include __local_include(__xdc_bld_pkg_c__)
#endif

[FILE QRS/.config/xconfig_gpio_test/package/xconfig_gpio_test.java]
/*
 * Do not modify this file; it is automatically 
 * generated and any modifications will be overwritten.
 *
 * @(#) xdc-G16
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class xconfig_gpio_test
{
 static final String VERS = "@(#) xdc-G16\n";

 static final Proto.Elm $$T_Bool = Proto.Elm.newBool();
 static final Proto.Elm $$T_Num = Proto.Elm.newNum();
 static final Proto.Elm $$T_Str = Proto.Elm.newStr();
 static final Proto.Elm $$T_Obj = Proto.Elm.newObj();

 static final Proto.Fxn $$T_Met = new Proto.Fxn(null, null, 0, -1, false);
 static final Proto.Map $$T_Map = new Proto.Map($$T_Obj);
 static final Proto.Arr $$T_Vec = new Proto.Arr($$T_Obj);

 static final XScriptO $$DEFAULT = Value.DEFAULT;
 static final Object $$UNDEF = Undefined.instance;

 static final Proto.Obj $$Package = (Proto.Obj)Global.get("$$Package");
 static final Proto.Obj $$Module = (Proto.Obj)Global.get("$$Module");
 static final Proto.Obj $$Instance = (Proto.Obj)Global.get("$$Instance");
 static final Proto.Obj $$Params = (Proto.Obj)Global.get("$$Params");

 static final Object $$objFldGet = Global.get("$$objFldGet");
 static final Object $$objFldSet = Global.get("$$objFldSet");
 static final Object $$proxyGet = Global.get("$$proxyGet");
 static final Object $$proxySet = Global.get("$$proxySet");
 static final Object $$delegGet = Global.get("$$delegGet");
 static final Object $$delegSet = Global.get("$$delegSet");

 Scriptable xdcO;
 Session ses;
 Value.Obj om;

 boolean isROV;
 boolean isCFG;

 Proto.Obj pkgP;
 Value.Obj pkgV;

 ArrayList<Object> imports = new ArrayList<Object>();
 ArrayList<Object> loggables = new ArrayList<Object>();
 ArrayList<Object> mcfgs = new ArrayList<Object>();
 ArrayList<Object> icfgs = new ArrayList<Object>();
 ArrayList<String> inherits = new ArrayList<String>();
 ArrayList<Object> proxies = new ArrayList<Object>();
 ArrayList<Object> sizes = new ArrayList<Object>();
 ArrayList<Object> tdefs = new ArrayList<Object>();

 void $$IMPORTS()
 {
 Global.callFxn("loadPackage", xdcO, "xdc");
 Global.callFxn("loadPackage", xdcO, "xdc.corevers");
 }

 void $$OBJECTS()
 {
 pkgP = (Proto.Obj)om.bind("xconfig_gpio_test.Package", new Proto.Obj());
 pkgV = (Value.Obj)om.bind("xconfig_gpio_test", new Value.Obj("xconfig_gpio_test", pkgP));
 }

 void $$SINGLETONS()
 {
 pkgP.init("xconfig_gpio_test.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "xconfig_gpio_test"));
 Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "xconfig_gpio_test/package.xs");
 om.bind("xdc.IPackage$$capsule", cap);
 Object fxn;
 fxn = Global.get(cap, "init");
 if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "xconfig_gpio_test"), fxn);
 fxn = Global.get(cap, "close");
 if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "xconfig_gpio_test"), fxn);
 fxn = Global.get(cap, "validate");
 if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "xconfig_gpio_test"), fxn);
 fxn = Global.get(cap, "exit");
 if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "xconfig_gpio_test"), fxn);
 fxn = Global.get(cap, "getLibs");
 if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "xconfig_gpio_test"), fxn);
 fxn = Global.get(cap, "getSects");
 if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "xconfig_gpio_test"), fxn);
 pkgP.bind("$capsule", cap);
 pkgV.init2(pkgP, "xconfig_gpio_test", Value.DEFAULT, false);
 pkgV.bind("$name", "xconfig_gpio_test");
 pkgV.bind("$category", "Package");
 pkgV.bind("$$qn", "xconfig_gpio_test.");
 pkgV.bind("$vers", Global.newArray());
 Value.Map atmap = (Value.Map)pkgV.getv("$attr");
 atmap.seal("length");
 imports.clear();
 pkgV.bind("$imports", imports);
 StringBuilder sb = new StringBuilder();
 sb.append("var pkg = xdc.om['xconfig_gpio_test'];\n");
 sb.append("if (pkg.$vers.length >= 3) {\n");
 sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
 sb.append("}\n");
 sb.append("if ('xconfig_gpio_test$$stat$base' in xdc.om) {\n");
 sb.append("pkg.packageBase = xdc.om['xconfig_gpio_test$$stat$base'];\n");
 sb.append("pkg.packageRepository = xdc.om['xconfig_gpio_test$$stat$root'];\n");
 sb.append("}\n");
 sb.append("pkg.build.libraries = [\n");
 sb.append("];\n");
 sb.append("pkg.build.libDesc = [\n");
 sb.append("];\n");
 Global.eval(sb.toString());
 }

 void $$INITIALIZATION()
 {
 Value.Obj vo;

 if (isCFG) {
 }//isCFG
 Global.callFxn("init", pkgV);
 ((Value.Arr)om.findStrict("$packages", "xconfig_gpio_test")).add(pkgV);
 }

 public void exec( Scriptable xdcO, Session ses )
 {
 this.xdcO = xdcO;
 this.ses = ses;
 om = (Value.Obj)xdcO.get("om", null);

 Object o = om.geto("$name");
 String s = o instanceof String ? (String)o : null;
 isCFG = s != null && s.equals("cfg");
 isROV = s != null && s.equals("rov");

 $$IMPORTS();
 $$OBJECTS();
 if (isROV) {
 }//isROV
 $$SINGLETONS();
 $$INITIALIZATION();
 }
}

[FILE QRS/Debug/configPkg/package/cfg/ECG_pe674.h]
/*
 * Do not modify this file; it is automatically 
 * generated and any modifications will be overwritten.
 *
 * @(#) xdc-G16
 */

#include <xdc/std.h>

#include <ti/sysbios/heaps/HeapMem.h>
extern const ti_sysbios_heaps_HeapMem_Handle heap0;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle echo;

#include <ti/sysbios/hal/Timer.h>
extern const ti_sysbios_hal_Timer_Handle timer0;

#include <ti/sysbios/knl/Swi.h>
extern const ti_sysbios_knl_Swi_Handle swi0;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle semaphore0;

#include <ti/sysbios/hal/Timer.h>
extern const ti_sysbios_hal_Timer_Handle timer1;

extern int xdc_runtime_Startup__EXECFXN__C;

extern int xdc_runtime_Startup__RESETFXN__C;

extern int xdc_rov_runtime_Mon__checksum;

extern int xdc_rov_runtime_Mon__write;

[FILE QRS/Debug/configPkg/package/cfg/QRS_pe674.h]
/*
 * Do not modify this file; it is automatically 
 * generated and any modifications will be overwritten.
 *
 * @(#) xdc-G16
 */

#include <xdc/std.h>

#include <ti/sysbios/heaps/HeapMem.h>
extern const ti_sysbios_heaps_HeapMem_Handle heap0;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle echo;

#include <ti/sysbios/hal/Timer.h>
extern const ti_sysbios_hal_Timer_Handle timer0;

#include <ti/sysbios/knl/Swi.h>
extern const ti_sysbios_knl_Swi_Handle swi0;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle semaphore0;

#include <ti/sysbios/hal/Timer.h>
extern const ti_sysbios_hal_Timer_Handle timer1;

extern int xdc_runtime_Startup__EXECFXN__C;

extern int xdc_runtime_Startup__RESETFXN__C;

extern int xdc_rov_runtime_Mon__checksum;

extern int xdc_rov_runtime_Mon__write;

[FILE QRS/Debug/configPkg/package/configPkg.java]
/*
 * Do not modify this file; it is automatically 
 * generated and any modifications will be overwritten.
 *
 * @(#) xdc-G16
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class configPkg
{
 static final String VERS = "@(#) xdc-G16\n";

 static final Proto.Elm $$T_Bool = Proto.Elm.newBool();
 static final Proto.Elm $$T_Num = Proto.Elm.newNum();
 static final Proto.Elm $$T_Str = Proto.Elm.newStr();
 static final Proto.Elm $$T_Obj = Proto.Elm.newObj();

 static final Proto.Fxn $$T_Met = new Proto.Fxn(null, null, 0, -1, false);
 static final Proto.Map $$T_Map = new Proto.Map($$T_Obj);
 static final Proto.Arr $$T_Vec = new Proto.Arr($$T_Obj);

 static final XScriptO $$DEFAULT = Value.DEFAULT;
 static final Object $$UNDEF = Undefined.instance;

 static final Proto.Obj $$Package = (Proto.Obj)Global.get("$$Package");
 static final Proto.Obj $$Module = (Proto.Obj)Global.get("$$Module");
 static final Proto.Obj $$Instance = (Proto.Obj)Global.get("$$Instance");
 static final Proto.Obj $$Params = (Proto.Obj)Global.get("$$Params");

 static final Object $$objFldGet = Global.get("$$objFldGet");
 static final Object $$objFldSet = Global.get("$$objFldSet");
 static final Object $$proxyGet = Global.get("$$proxyGet");
 static final Object $$proxySet = Global.get("$$proxySet");
 static final Object $$delegGet = Global.get("$$delegGet");
 static final Object $$delegSet = Global.get("$$delegSet");

 Scriptable xdcO;
 Session ses;
 Value.Obj om;

 boolean isROV;
 boolean isCFG;

 Proto.Obj pkgP;
 Value.Obj pkgV;

 ArrayList<Object> imports = new ArrayList<Object>();
 ArrayList<Object> loggables = new ArrayList<Object>();
 ArrayList<Object> mcfgs = new ArrayList<Object>();
 ArrayList<Object> icfgs = new ArrayList<Object>();
 ArrayList<String> inherits = new ArrayList<String>();
 ArrayList<Object> proxies = new ArrayList<Object>();
 ArrayList<Object> sizes = new ArrayList<Object>();
 ArrayList<Object> tdefs = new ArrayList<Object>();

 void $$IMPORTS()
 {
 Global.callFxn("loadPackage", xdcO, "xdc");
 Global.callFxn("loadPackage", xdcO, "xdc.corevers");
 }

 void $$OBJECTS()
 {
 pkgP = (Proto.Obj)om.bind("configPkg.Package", new Proto.Obj());
 pkgV = (Value.Obj)om.bind("configPkg", new Value.Obj("configPkg", pkgP));
 }

 void $$SINGLETONS()
 {
 pkgP.init("configPkg.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "configPkg"));
 Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "configPkg/package.xs");
 om.bind("xdc.IPackage$$capsule", cap);
 Object fxn;
 fxn = Global.get(cap, "init");
 if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "configPkg"), fxn);
 fxn = Global.get(cap, "close");
 if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "configPkg"), fxn);
 fxn = Global.get(cap, "validate");
 if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "configPkg"), fxn);
 fxn = Global.get(cap, "exit");
 if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "configPkg"), fxn);
 fxn = Global.get(cap, "getLibs");
 if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "configPkg"), fxn);
 fxn = Global.get(cap, "getSects");
 if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "configPkg"), fxn);
 pkgP.bind("$capsule", cap);
 pkgV.init2(pkgP, "configPkg", Value.DEFAULT, false);
 pkgV.bind("$name", "configPkg");
 pkgV.bind("$category", "Package");
 pkgV.bind("$$qn", "configPkg.");
 pkgV.bind("$vers", Global.newArray());
 Value.Map atmap = (Value.Map)pkgV.getv("$attr");
 atmap.seal("length");
 imports.clear();
 pkgV.bind("$imports", imports);
 StringBuilder sb = new StringBuilder();
 sb.append("var pkg = xdc.om['configPkg'];\n");
 sb.append("if (pkg.$vers.length >= 3) {\n");
 sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
 sb.append("}\n");
 sb.append("if ('configPkg$$stat$base' in xdc.om) {\n");
 sb.append("pkg.packageBase = xdc.om['configPkg$$stat$base'];\n");
 sb.append("pkg.packageRepository = xdc.om['configPkg$$stat$root'];\n");
 sb.append("}\n");
 sb.append("pkg.build.libraries = [\n");
 sb.append("];\n");
 sb.append("pkg.build.libDesc = [\n");
 sb.append("];\n");
 Global.eval(sb.toString());
 }

 void $$INITIALIZATION()
 {
 Value.Obj vo;

 if (isCFG) {
 }//isCFG
 Global.callFxn("init", pkgV);
 ((Value.Arr)om.findStrict("$packages", "configPkg")).add(pkgV);
 }

 public void exec( Scriptable xdcO, Session ses )
 {
 this.xdcO = xdcO;
 this.ses = ses;
 om = (Value.Obj)xdcO.get("om", null);

 Object o = om.geto("$name");
 String s = o instanceof String ? (String)o : null;
 isCFG = s != null && s.equals("cfg");
 isROV = s != null && s.equals("rov");

 $$IMPORTS();
 $$OBJECTS();
 if (isROV) {
 }//isROV
 $$SINGLETONS();
 $$INITIALIZATION();
 }
}

[FILE QRS/Debug/configPkg/package/package.defs.h]
/*
 * Do not modify this file; it is automatically 
 * generated and any modifications will be overwritten.
 *
 * @(#) xdc-G16
 */

#ifndef configPkg__
#define configPkg__

#endif /* configPkg__ */ 

[FILE QRS/Debug/configPkg/package/package_configPkg.c]
/*
 * Do not modify this file; it is automatically 
 * generated and any modifications will be overwritten.
 *
 * @(#) xdc-G16
 */

#include <xdc/std.h>

__FAR__ char configPkg__dummy__;

#define __xdc_PKGVERS null
#define __xdc_PKGNAME configPkg
#define __xdc_PKGPREFIX configPkg_

#ifdef __xdc_bld_pkg_c__
#define __stringify(a) #a
#define __local_include(a) __stringify(a)
#include __local_include(__xdc_bld_pkg_c__)
#endif

[FILE QRS/GPIO_board.c]
/**
 * \file GPIO_board.c
 *
 * \brief OMAPL138 EVM board specific GPIO parameters.
 *
 */

/*
 * Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <ti/csl/soc.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/gpio/GPIO.h>
#include <ti/drv/gpio/soc/GPIO_soc.h>
#include <ti/drv/gpio/test/led_blink/src/GPIO_board.h>

/* GPIO Driver board specific pin configuration structure */
GPIO_PinConfig gpioPinConfigs[] =
{
 /* Input pin with interrupt enabled */
 GPIO_DEVICE_CONFIG(GPIO_LED0_PORT_NUM, GPIO_LED0_PIN_NUM) |
 GPIO_CFG_IN_INT_RISING | GPIO_CFG_OUTPUT,

 /* Output pin */
 GPIO_DEVICE_CONFIG(GPIO_LED1_PORT_NUM, GPIO_LED1_PIN_NUM) |
 GPIO_CFG_OUTPUT
};

/* GPIO Driver call back functions */
GPIO_CallbackFxn gpioCallbackFunctions[] =
{
 NULL,
 NULL
};

/* GPIO Driver configuration structure */
GPIO_v0_Config GPIO_v0_config =
{
 gpioPinConfigs,
 gpioCallbackFunctions,
 sizeof(gpioPinConfigs) / sizeof(GPIO_PinConfig),
 sizeof(gpioCallbackFunctions) / sizeof(GPIO_CallbackFxn),
 12,
};

[FILE QRS/GPIO_board.h]
/**
 * \file GPIO_board.h
 *
 * \brief GPIO board header file.
 *
 */

/*
 * Copyright (C) 2014 - 2018 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _GPIO_BOARD_H
#define _GPIO_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Example/Board Header files */
#include <ti/board/board.h>

#if defined (SOC_AM572x) || defined (SOC_AM574x)
#include <ti/csl/soc/am572x/src/cslr_soc_mpu_baseaddress.h>
#endif

#if defined (SOC_AM571x)
#include <ti/csl/soc/am571x/src/cslr_soc_mpu_baseaddress.h>
#endif

#if defined (SOC_AM65XX)
#include <ti/csl/src/ip/intr_router/V0/csl_intr_router.h>
#include <ti/csl/soc/am65xx/src/cslr_soc_baseaddress.h>
#include <ti/csl/soc/am65xx/src/cslr_mcu_ctrl_mmr.h>
#include <ti/csl/soc/am65xx/src/cslr_mcu_pll_mmr.h>
#include <ti/csl/soc/am65xx/src/cslr_wkup_ctrl_mmr.h>
#endif

#if defined (SOC_J721E)
#include <ti/csl/src/ip/intr_router/V0/csl_intr_router.h>
#include <ti/csl/soc/j721e/src/cslr_soc_baseaddress.h>
#include <ti/csl/soc/j721e/src/cslr_mcu_ctrl_mmr.h>
#include <ti/csl/soc/j721e/src/cslr_mcu_pll_mmr.h>
#include <ti/csl/soc/j721e/src/cslr_wkup_ctrl_mmr.h>
#endif

#if defined (SOC_J7200)
#include <ti/csl/soc/j7200/src/cslr_soc_baseaddress.h>
#include <ti/csl/soc/j7200/src/cslr_mcu_ctrl_mmr.h>
#include <ti/csl/soc/j7200/src/cslr_mcu_pll_mmr.h>
#include <ti/csl/soc/j7200/src/cslr_wkup_ctrl_mmr.h>
#endif
/**********************************************************************
 ************************** Macros ************************************
 **********************************************************************/
#if defined (idkAM572x) || defined (idkAM574x)
#define GPIO_INTR_LED_BASE_ADDR_1P2 (CSL_MPU_GPIO4_REGS)
#define GPIO_LED_PIN_NUM_1P2 (0x04U)
#define GPIO_INTR_LED_BASE_ADDR_1P3 (CSL_MPU_GPIO7_REGS)
#define GPIO_LED_PIN_NUM_1P3 (0x17U)
#endif

#if defined (idkAM571x)
#define GPIO_INTR_LED_BASE_ADDR (CSL_MPU_GPIO2_REGS)
#define GPIO_LED_PIN_NUM (0x15U)
#endif

#if defined (evmAM572x)
#if defined (__TI_ARM_V7M4__)
#define GPIO_INTR_LED_BASE_ADDR (CSL_MPU_GPIO1_REGS)
#define GPIO_LED_PIN_NUM (0x10U)
#else
#define GPIO_INTR_LED_BASE_ADDR (CSL_MPU_GPIO7_REGS)
#define GPIO_LED_PIN_NUM (0x08U)
#endif
#endif

#if defined (evmAM572x) || defined (idkAM571x) || \
 defined (skAM437x) || defined (evmAM437x) || \
 defined (icev2AM335x) || defined (skAM335x) || defined (bbbAM335x)
#define GPIO_BASE_ADDR GPIO_INTR_LED_BASE_ADDR
#define GPIO_LED_PIN GPIO_LED_PIN_NUM
#endif

#if defined (evmK2H) || defined (evmK2K)
#define K2H_EVM_USER0_LED_RED (12U) /* GPIO pin 12 */
#define K2H_EVM_USER0_LED_GREEN (13U) /* GPIO pin 13 */
#define K2H_EVM_USER1_LED_BLUE (14U) /* GPIO pin 14 */
#define K2H_EVM_USER2_LED_BLUE (15U) /* GPIO pin 15 */

#define GPIO_LED0_PIN_NUM K2H_EVM_USER0_LED_GREEN
#define GPIO_LED0_PORT_NUM (0U) /* GPIO port 0 */
#define GPIO_LED1_PIN_NUM K2H_EVM_USER2_LED_BLUE
#define GPIO_LED1_PORT_NUM (0U) /* GPIO port 0 */
#endif

#if defined (evmK2E)
#define K2E_EVM_USER0_LED_RED (12U) /* GPIO pin 12 */
#define K2E_EVM_USER0_LED_GREEN (13U) /* GPIO pin 13 */
#define K2E_EVM_USER1_LED_BLUE (14U) /* GPIO pin 14 */
#define K2E_EVM_USER2_LED_BLUE (15U) /* GPIO pin 15 */

#define GPIO_LED0_PIN_NUM K2E_EVM_USER0_LED_GREEN
#define GPIO_LED0_PORT_NUM (0U) /* GPIO port 0 */
#define GPIO_LED1_PIN_NUM K2E_EVM_USER1_LED_BLUE
#define GPIO_LED1_PORT_NUM (0U) /* GPIO port 0 */
#endif

#if defined (evmK2L)
/* No gpio pin directly connect to LED on K2L EVM */
#define GPIO_LED0_PIN_NUM (8U)
#define GPIO_LED0_PORT_NUM (0U) /* GPIO port 0 */
#define GPIO_LED1_PIN_NUM (9U)
#define GPIO_LED1_PORT_NUM (0U) /* GPIO port 0 */
#endif

#if defined (evmK2G)
#define GPIO_LED0_PIN_NUM (108U) /* by default PADCONFIG139 set to GPIO0_108 */
#define GPIO_LED0_PORT_NUM (0U) /* GPIO port 0 */
#define GPIO_LED1_PIN_NUM (11U) /* by default PADCONFIG186 set to GPIO1_11 */
#define GPIO_LED1_PORT_NUM (1U) /* GPIO port 1 */

#ifdef _TMS320C6X
#define GPIO_MUX_SEL (16U) /* Event slect number for DSP GPIOMUX int */
#else
#define GPIO_MUX_SEL (0U) /* Event slect number for ARM GPIOMUX int */
#endif
#endif

#if defined (iceK2G)
#define GPIO_LED0_PIN_NUM (11U) /* by default PADCONFIG139 set to GPIO0_108 */
#define GPIO_LED0_PORT_NUM (0U) /* GPIO port 0 */
#define GPIO_LED1_PIN_NUM (12U) /* by default PADCONFIG186 set to GPIO1_11 */
#define GPIO_LED1_PORT_NUM (1U) /* GPIO port 1 */

#ifdef _TMS320C6X
#define GPIO_MUX_SEL (16U) /* Event slect number for DSP GPIOMUX int */
#else
#define GPIO_MUX_SEL (0U) /* Event slect number for ARM GPIOMUX int */
#endif
#endif

#if defined (evmC6678)
/* No gpio pin directly connect to LED on C6678 EVM */
#define GPIO_LED0_PIN_NUM (8U)
#define GPIO_LED0_PORT_NUM (0U) /* GPIO port 0 */
#define GPIO_LED1_PIN_NUM (9U)
#define GPIO_LED1_PORT_NUM (0U) /* GPIO port 0 */
#endif

#if defined (evmC6657)
/* No gpio pin directly connect to LED on C6678 EVM */
#define GPIO_LED0_PIN_NUM (8U)
#define GPIO_LED0_PORT_NUM (0U) /* GPIO port 0 */
#define GPIO_LED1_PIN_NUM (9U)
#define GPIO_LED1_PORT_NUM (0U) /* GPIO port 0 */
#endif

#if defined (am65xx_evm) || defined (am65xx_idk) || defined (j721e_sim)
#if defined(AM65

[FILE QRS/GPIO_log.h]
/**
 * \file GPIO_log.h
 *
 * \brief This file contains the prototypes for the log print functions. By
 default the prints will be directed to serial console using UART.
 *
 */

/*
 * Copyright (C) 2014 - 2015 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _GPIO_LOG_H
#define _GPIO_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

/* UART Header files */
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/UART_stdio.h>
#if defined(SOC_AM571x)||defined(SOC_AM572x)||defined(SOC_AM574x)
#include <ti/csl/soc/am572x/src/cslr_control_core_pad_io.h>
#endif

/**********************************************************************
 ************************** Global Variables **************************
 **********************************************************************/
extern void UART_printf(const char *pcString, ...);
extern void ConsoleUtilsInit(void);

/**********************************************************************
 ************************** Macros ************************************
 **********************************************************************/
/* Enable the below macro to have prints on the IO Console */
//#define IO_CONSOLE

#ifndef IO_CONSOLE
#define GPIO_log UART_printf
#else
#define GPIO_log printf
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GPIO_LOG_H */

[FILE QRS/Timestamp.h]
/*
 * Do not modify this file; it is automatically 
 * generated and any modifications will be overwritten.
 *
 * @(#) xdc-G16
 */

/*
 * ======== GENERATED SECTIONS ========
 *
 * PROLOGUE
 * INCLUDES
 *
 * INTERNAL DEFINITIONS
 * MODULE-WIDE CONFIGS
 * VIRTUAL FUNCTIONS
 * FUNCTION DECLARATIONS
 * CONVERTORS
 * SYSTEM FUNCTIONS
 *
 * EPILOGUE
 * STATE STRUCTURES
 * PREFIX ALIASES
 */

/*
 * ======== PROLOGUE ========
 */

#ifndef xdc_runtime_Timestamp__include
#define xdc_runtime_Timestamp__include

#ifndef __nested__
#define __nested__
#define xdc_runtime_Timestamp__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define xdc_runtime_Timestamp___VERS 200

/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/package/package.defs.h>

#include <xdc/runtime/ITimestampClient.h>
#include <xdc/runtime/ITimestampProvider.h>
#include <xdc/runtime/package/Timestamp_SupportProxy.h>

/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/*
 * ======== INTERNAL DEFINITIONS ========
 */

/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__xdc_runtime_Timestamp_Module__diagsEnabled;
__extern __FAR__ const CT__xdc_runtime_Timestamp_Module__diagsEnabled xdc_runtime_Timestamp_Module__diagsEnabled__C;
#ifdef xdc_runtime_Timestamp_Module__diagsEnabled__CR
#define xdc_runtime_Timestamp_Module__diagsEnabled__C (*((CT__xdc_runtime_Timestamp_Module__diagsEnabled*)(xdcRomConstPtr + xdc_runtime_Timestamp_Module__diagsEnabled__C_offset)))
#else
#define xdc_runtime_Timestamp_Module__diagsEnabled (xdc_runtime_Timestamp_Module__diagsEnabled__C)
#endif

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__xdc_runtime_Timestamp_Module__diagsIncluded;
__extern __FAR__ const CT__xdc_runtime_Timestamp_Module__diagsIncluded xdc_runtime_Timestamp_Module__diagsIncluded__C;
#ifdef xdc_runtime_Timestamp_Module__diagsIncluded__CR
#define xdc_runtime_Timestamp_Module__diagsIncluded__C (*((CT__xdc_runtime_Timestamp_Module__diagsIncluded*)(xdcRomConstPtr + xdc_runtime_Timestamp_Module__diagsIncluded__C_offset)))
#else
#define xdc_runtime_Timestamp_Module__diagsIncluded (xdc_runtime_Timestamp_Module__diagsIncluded__C)
#endif

/* Module__diagsMask */
typedef xdc_Bits16 *CT__xdc_runtime_Timestamp_Module__diagsMask;
__extern __FAR__ const CT__xdc_runtime_Timestamp_Module__diagsMask xdc_runtime_Timestamp_Module__diagsMask__C;
#ifdef xdc_runtime_Timestamp_Module__diagsMask__CR
#define xdc_runtime_Timestamp_Module__diagsMask__C (*((CT__xdc_runtime_Timestamp_Module__diagsMask*)(xdcRomConstPtr + xdc_runtime_Timestamp_Module__diagsMask__C_offset)))
#else
#define xdc_runtime_Timestamp_Module__diagsMask (xdc_runtime_Timestamp_Module__diagsMask__C)
#endif

/* Module__gateObj */
typedef xdc_Ptr CT__xdc_runtime_Timestamp_Module__gateObj;
__extern __FAR__ const CT__xdc_runtime_Timestamp_Module__gateObj xdc_runtime_Timestamp_Module__gateObj__C;
#ifdef xdc_runtime_Timestamp_Module__gateObj__CR
#define xdc_runtime_Timestamp_Module__gateObj__C (*((CT__xdc_runtime_Timestamp_Module__gateObj*)(xdcRomConstPtr + xdc_runtime_Timestamp_Module__gateObj__C_offset)))
#else
#define xdc_runtime_Timestamp_Module__gateObj (xdc_runtime_Timestamp_Module__gateObj__C)
#endif

/* Module__gatePrms */
typedef xdc_Ptr CT__xdc_runtime_Timestamp_Module__gatePrms;
__extern __FAR__ const CT__xdc_runtime_Timestamp_Module__gatePrms xdc_runtime_Timestamp_Module__gatePrms__C;
#ifdef xdc_runtime_Timestamp_Module__gatePrms__CR
#define xdc_runtime_Timestamp_Module__gatePrms__C (*((CT__xdc_runtime_Timestamp_Module__gatePrms*)(xdcRomConstPtr + xdc_runtime_Timestamp_Module__gatePrms__C_offset)))
#else
#define xdc_runtime_Timestamp_Module__gatePrms (xdc_runtime_Timestamp_Module__gatePrms__C)
#endif

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__xdc_runtime_Timestamp_Module__id;
__extern __FAR__ const CT__xdc_runtime_Timestamp_Module__id xdc_runtime_Timestamp_Module__id__C;
#ifdef xdc_runtime_Timestamp_Module__id__CR
#define xdc_runtime_Timestamp_Module__id__C (*((CT__xdc_runtime_Timestamp_Module__id*)(xdcRomConstPtr + xdc_runtime_Timestamp_Module__id__C_offset)))
#else
#define xdc_runtime_Timestamp_Module__id (xdc_runtime_Timestamp_Module__id__C)
#endif

/* Module__loggerDefined */
typedef xdc_Bool CT__xdc_runtime_Timestamp_Module__loggerDefined;
__extern __FAR__ const CT__xdc_runtime_Timestamp_Module__loggerDefined xdc_runtime_Timestamp_Module__loggerDefined__C;
#ifdef xdc_runtime_Timestamp_Module__loggerDefined__CR
#define xdc_runtime_Timestamp_Module__loggerDefined__C (*((CT__xdc_runtime_Timestamp_Module__loggerDefined*)(xdcRomConstPtr + xdc_runtime_Timestamp_Module__loggerDefined__C_offset)))
#else
#define xdc_runtime_Timestamp_Module__loggerDefined (xdc_runtime_Timestamp_Module__loggerDefined__C)
#endif

/* Module__loggerObj */
typedef xdc_Ptr CT__xdc_runtime_Timestamp_Module__loggerObj;
__extern __FAR__ const CT__xdc_runtime_Timestamp_Module__loggerObj xdc_runtime_Timestamp_Module__loggerObj__C;
#ifdef xdc_runtime_Timestamp_Module__loggerObj__CR
#define xdc_runtime_Timestamp_Module__loggerObj__C (*((CT__xdc_runtime_Timestamp_Module__loggerObj*)(xdcRomConstPtr + xdc_runtime_Timestamp_Module__loggerObj__C_offset)))
#else
#define xdc_runtime_Timestamp_Module__loggerObj (xdc_runtime_Timestamp_Module__loggerObj__C)
#endif

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__xdc_runtime_Timestamp_Module__loggerFxn0;
__extern __FAR__ const CT__xdc_runtime_Timestamp_Module__loggerFxn0 xdc_runtime_Timestamp_Module__loggerFxn0__C;
#ifdef xdc_runtime_Timestamp_Module__loggerFxn0__CR
#define xdc_runtime_Timestamp_Module__loggerFxn0__C (*((CT__xdc_runtime_Timestamp_Module__loggerFxn0*)(xdcRomConstPtr + xdc_runtime_Timestamp_Module__loggerFxn0__C_offset)))
#else
#define xdc_runtime_Timestamp_Module__loggerFxn0 (xdc_runtime_Timestamp_Module__loggerFxn0__C)
#endif

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__xdc_runtime_Timestamp_Module__loggerFxn1;
__extern __FAR__ const CT__xdc_runtime_Timestamp_Module__loggerFxn1 xdc_runtime_Timestamp_Module__loggerFxn1__C;
#ifdef xdc_runtime_Timestamp_Module__loggerFxn1__CR
#define xdc_runtime_Timestamp_Module__loggerFxn1__C (*((CT__xdc_runtime_Timestamp_Module__loggerFxn1*)(xdcRomConstPtr + xdc_runtime_Timestamp_Module__loggerFxn1__C_offset)))
#else
#define xdc_runtime_Timestamp_Module__loggerFxn1 (xdc_runtime_Timestamp_Module__loggerFxn1__C)
#endif

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__xdc_runtime_Timestamp_Module__loggerFxn2;
__extern __FAR__ const CT__xdc_runtime_Timestamp_Module__loggerFxn2 xdc_runtime_Timestamp_Module__loggerFxn2__C;
#ifdef xdc_runtime_Timestamp_Module__loggerFxn2__CR
#define xdc_runtime_Timestamp_Module__loggerFxn2__C (*((CT__xdc_runtime_Timestamp_Module__loggerFxn2*)(xdcRomConstPtr + xdc_runtime_Timestamp_Modul

[FILE QRS/main_QRS.c]

#ifdef USE_BIOS /* build-time switch: bare-metal vs RTOS */

/*–––– XDCtools ––––*/
#include <xdc/std.h> /* basic typedefs (Int, UInt32, etc.) */
#include <xdc/runtime/System.h> /* lightweight printf / diagnostics */
#include <xdc/runtime/Error.h> /* run-time error tracking */
#include <xdc/runtime/Timestamp.h> /* high-resolution time-stamps */
#include <xdc/cfg/global.h> /* RTSC-generated handles & symbols */

/*–––– TI-SYS/BIOS ––––*/
#include <ti/sysbios/BIOS.h> /* kernel start & core API */
#include <ti/sysbios/knl/Task.h> /* tasks */
#include <ti/sysbios/knl/Swi.h> /* software interrupts */
#include <ti/sysbios/knl/Semaphore.h>/* counting / binary semaphores */

#endif /* USE_BIOS */

/*–––– C standard library ––––*/
#include <stdio.h>
#include <string.h>
#include <math.h>

/*–––– TI-RTOS driver layer ––––*/
#include <ti/drv/gpio/GPIO.h> /* high-level GPIO API */
#include <ti/drv/gpio/soc/GPIO_soc.h>/* SoC-specific pin config helpers */

/*–––– Board support package ––––*/
#include "GPIO_log.h" /* convenience macros for GPIO logging */
#include "GPIO_board.h" /* board-level pin names */

#include <ti/board/board.h> /* Board_init(), clock & pin-mux config */
#include <ti/csl/csl_clec.h> /* CLEC: core-local event controller */

/**********************************************************************
 **************************** Macros ********************************
 **********************************************************************/

/*------------- Sampling rate -------------*/
#define fs 225 /* sample-rate in Hz (global constant) */

/*------------- Adaptive-threshold tuning -------------*/
#define TH_SCALE 0.75f /* % of recent-R average taken as dynTH
 * (set to 0.65 … 0.75; lower → more
 * sensitive, but may trigger noise) */

/*------------- Refractory-period guard -------------*/
#define REF_PERIOD_MS 250 /* 250-ms blanking after each R peak */
#define REF_SAMPLES ((int)(REF_PERIOD_MS * fs / 1000.0f))
 /* refractory window in samples (~56) */

/*------------- Ring-buffer helpers -------------*/
#define MOD(i) (((i) + N) % N) /* wrap any index into 0…N-1 */
#define F(i) (filtered_arr[MOD(i)]) /* safe access: x[n] */
#define D1(i) (d1_arr[MOD(i)]) /* safe access: Δx[n] */
#define D2(i) (d2_arr[MOD(i)]) /* safe access: ΔΔx[n] */

/*------------- Buffer sizes & static thresholds -------------*/
#define N 336 /* length of all circular buffers
 * 336 samples ≈ 1.5 s @225 Hz */
#define H_TH 0.60f /* high, fixed threshold (legacy) */
#define L_TH 0.40f /* low, fixed threshold (legacy) */

/**********************************************************************
 ************************ Forward Declarations **********************
 **********************************************************************/

/* Hardware / software interrupt service routines */
void timer0_ISR(void); /* HWI: ADC sampler tick */
void timer1_ISR(void); /* HWI: user-LED auto-off */
void swi0_ISR(void); /* SWI: moves sample → filter pipeline */

/* Signal-processing building blocks */
void IIR_Biquad(void); /* 2-section elliptic IIR */
float F_fir(void); /* optional FIR (not used in ECG demo)*/
void detect_PQRST_deriv(void); /* peak detector (derivative method) */
//void ECG_FILTER(void); /* RTOS task: runs IIR + BPM logic */
void idlePrintFxn(void); /* Idle hook: dumps log to UART */

/**********************************************************************
 ************************* Log Buffer *******************************
 **********************************************************************/

#include <math.h> /* for fabsf / modff, used elsewhere */

#define LOG_LEN 64 /* circular log holds the last 64 detected beats */

typedef struct {
 uint16_t idx; /* sample index of R peak */
 float P, Q, R, S, T; /* peak amplitudes */
 uint16_t rr_ms; /* R-R interval in milliseconds */
 uint8_t bpm; /* instantaneous heart rate */
} LogEntry;

/* Producer–consumer pointers:
 * • SWI pushes new entries → wrPtr
 * • Idle task prints & pops → rdPtr */
LogEntry logBuf[LOG_LEN];
volatile uint16_t wrPtr = 0; /* write index (producer) */
volatile uint16_t rdPtr = 0; /* read index (consumer) */

/*---------------------------------------------------------------
 * prnFloat4
 * ----------
 * Print a floating-point value with exactly four digits after the
 * decimal point, using a lightweight integer conversion instead of
 * the expensive "%f" formatter in TI’s run-time library.
 *
 * ‣ lbl – short tag such as "P", "Q", … (printed as “P=0.1234”)
 * ‣ v – value to print
 *
 * The function keeps the executable code minimal; only comments
 * have been added for clarity.
 *--------------------------------------------------------------*/
static inline void prnFloat4(const char *lbl, float v)
{
 /* ------------ split sign, integer part, and fractional part ------------ */
 int sign = (v < 0) ? -1 : 1; /* store sign separately */
 float a = fabsf(v); /* work with magnitude */

 int intPart = (int)a; /* integer part: floor(a) */
 float frac = a - (float)intPart; /* fractional part: 0.xxxx */

 /* ---- convert fractional part to an integer in the range 0…9999 ---- */
 int frac4 = (int)(frac * 10000.0f + 0.5f); /* *10000 and round to nearest */

 /* ---------------------------------------------------------------------- *
 * Print result:
 * • “P=-0.1234 ” if value is negative but integer part is zero
 * • “P=-1.2345 ” otherwise (sign folded into intPart)
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
 * UART console. Runs whenever the CPU is in the RTOS Idle
 * state, so it never steals time from real-time processing
