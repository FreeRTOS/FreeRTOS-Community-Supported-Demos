/*
 * bsp_compiler_support.h
 *
 *  Created on: Feb 27, 2024
 *      Author: tin.nguyen-van
 */

#ifndef COMMON_BSP_COMPILER_SUPPORT_H_
#define COMMON_BSP_COMPILER_SUPPORT_H_

#if defined(__CCRH__)
 #define BSP_DONT_REMOVE
 #define EIPC     0
 #define EIPSW    1
 #define FEPC     2
 #define FEPSW    3
 #define PSW      5
 #define FPSR     6
 #define FPEPC    7
 #define FPST     8
 #define FPCC     9
 #define FPCFG    10
 #define FPEC     11
 #define EIIC     13
 #define FEIC     14
 #define CTPC     16
 #define CTPSW    17
 #define CTBP     20
 #define EIWR     28
 #define FEWR     29

 #define DI()                __DI()
 #define EI()                __EI()
 #define HALT()              __halt()
 #define NOP()               __nop()
 #define SYNCP()             __syncp()
 #define SCH1R(x)            __sch1r((x))
 #define LDSR(regid, ret)    __ldsr((regid), (ret))
 #define STSR(regid)         __stsr((regid))
#endif

#endif                                 /* COMMON_BSP_COMPILER_SUPPORT_H_ */
