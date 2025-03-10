/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_bsp_riscv_mcu_compiler.h
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 20.01.2024 1.00     First Release
*         : 29.03.2024 1.10     Add macro definitions for Segger toolchain.
***********************************************************************************************************************/

/*************************************************
 * Includes  <System Includes> , "Project Includes"
 *************************************************/

#ifndef R_RISCV_ASSPEASY_COMPILER_H
#define R_RISCV_ASSPEASY_COMPILER_H
#if defined(__ICCRISCV__)
#include "intrinsics.h"
#endif
/* ========== Check Compiler ========== */
#if defined(__llvm__) || defined(__ICCRISCV__) || defined(__SEGGER_CC__)
    /* supported */
#else
    #error "Unrecognized compiler"
#endif

#if defined(__SEGGER_CC__)
#define R_BSP_NOP()                  NOP() 
__attribute__((always_inline)) static inline void NOP(void)
{
  __asm volatile("nop");
}
#elif defined(__llvm__)
#define R_BSP_NOP()                  NOP()
#define NOP() asm("nop")
#elif defined(__ICCRISCV__)
#define R_BSP_NOP()                  __no_operation()
#endif

/* Sections */


/* ========== #pragma Directive ========== */
#if defined(__ICCRISCV__)
#define R_BSP_PRAGMA(...)                                      _Pragma(#__VA_ARGS__)
#endif

/* ---------- Interrupt Function Creation ---------- */
#if defined(__SEGGER_CC__)
/* Permissible values for int_type are user, supervisor and machine */
#define R_BSP_PRAGMA_INTERRUPT(function_name, int_type)         void function_name(void) \
                                                                __attribute__ ((interrupt(#int_type)));
#elif defined(__llvm__)
/* R_BSP_PRAGMA_INTERRUPT */
#define R_BSP_PRAGMA_INTERRUPT(function_name, vector)           extern void function_name(void) \
                                                                __attribute__((interrupt(vect=vector), used));
#define R_BSP_PRAGMA_STATIC_INTERRUPT(function_name, vector)    static void function_name(void) \
                                                                __attribute__((interrupt(vect=vector), used));
#define R_BSP_ATTRIB_INTERRUPT                                  extern
#define R_BSP_ATTRIB_STATIC_INTERRUPT                           static
#elif defined(__ICCRISCV__)
/* Standard */
#define R_BSP_PRAGMA_INTERRUPT(function_name, vect)             R_BSP_PRAGMA(vector=vect)\
                                                                extern __interrupt void function_name(void);
#define R_BSP_PRAGMA_STATIC_INTERRUPT(function_name, vect)      R_BSP_PRAGMA(vector=vect)\
                                                                static __interrupt void function_name(void);
#define R_BSP_ATTRIB_INTERRUPT                                  extern __interrupt
#define R_BSP_ATTRIB_STATIC_INTERRUPT                           static __interrupt
#endif

#endif /* R_RISCV_ASSPEASY_COMPILER_H */

