/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2018 - 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

#ifndef COMMON_BSP_COMPILER_SUPPORT_H_
#define COMMON_BSP_COMPILER_SUPPORT_H_

#if defined( __CCRH__ )
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

    #define DI()                  __DI()
    #define EI()                  __EI()
    #define HALT()                __halt()
    #define NOP()                 __nop()
    #define SYNCP()               __syncp()
    #define SCH1R( x )            __sch1r( ( x ) )
    #define LDSR( regid, ret )    __ldsr( ( regid ), ( ret ) )
    #define STSR( regid )         __stsr( ( regid ) )
#endif /* if defined( __CCRH__ ) */

#endif /* COMMON_BSP_COMPILER_SUPPORT_H_ */
