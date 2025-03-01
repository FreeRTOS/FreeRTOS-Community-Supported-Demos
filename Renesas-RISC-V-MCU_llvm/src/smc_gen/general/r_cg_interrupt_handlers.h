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
* Copyright (C) 2021, 2023 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : r_cg_interrupt_handlers.h
* Version          : 1.0.30
* Device(s)        : R9A02G0214CNE
* Description      : None
* Creation Date    : 
***********************************************************************************************************************/

#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

/*
 * INT_ACLINT_MSIP (0x0)
 */
void INT_ACLINT_MSIP (void)__attribute__((interrupt));

/*
 * INT_ACLINT_MTIP (0x1C)
 */
void INT_ACLINT_MTIP (void)__attribute__((interrupt));

/*
 * INT_IELSR0 (0x4C)
 */
void INT_IELSR0 (void)__attribute__((interrupt));

/*
 * INT_IELSR1 (0x50)
 */
void INT_IELSR1 (void)__attribute__((interrupt));

/*
 * INT_IELSR2 (0x54)
 */
void INT_IELSR2 (void)__attribute__((interrupt));

/*
 * INT_IELSR3 (0x58)
 */
void INT_IELSR3 (void)__attribute__((interrupt));

/*
 * INT_IELSR4 (0x5C)
 */
void r_Config_ICU_irq4_interrupt (void) __attribute__ ((interrupt));

/*
 * INT_IELSR5 (0x60)
 */
void INT_IELSR5 (void)__attribute__((interrupt));

/*
 * INT_IELSR6 (0x64)
 */
void INT_IELSR6 (void)__attribute__((interrupt));

/*
 * INT_IELSR7 (0x68)
 */
void INT_IELSR7 (void)__attribute__((interrupt));

/*
 * INT_IELSR8 (0x6C)
 */
void r_Config_UART0_interrupt_send (void) __attribute__ ((interrupt));

/*
 * INT_IELSR9 (0x70)
 */
void r_Config_UART0_interrupt_receive (void) __attribute__ ((interrupt));

/*
 * INT_IELSR10 (0x74)
 */
void INT_IELSR10 (void)__attribute__((interrupt));

/*
 * INT_IELSR11 (0x78)
 */
void INT_IELSR11 (void)__attribute__((interrupt));

/*
 * INT_IELSR12 (0x7C)
 */
void INT_IELSR12 (void)__attribute__((interrupt));

/*
 * INT_IELSR13 (0x80)
 */
void INT_IELSR13 (void)__attribute__((interrupt));

/*
 * INT_IELSR14 (0x84)
 */
void INT_IELSR14 (void)__attribute__((interrupt));

/*
 * INT_IELSR15 (0x88)
 */
void INT_IELSR15 (void)__attribute__((interrupt));

/*
 * INT_IELSR16 (0x8C)
 */
void INT_IELSR16 (void)__attribute__((interrupt));

/*
 * INT_IELSR17 (0x90)
 */
void r_Config_UART0_interrupt_error (void) __attribute__ ((interrupt));

/*
 * INT_IELSR18 (0x94)
 */
void INT_IELSR18 (void)__attribute__((interrupt));

/*
 * INT_IELSR19 (0x98)
 */
void INT_IELSR19 (void)__attribute__((interrupt));

/*
 * INT_IELSR20 (0x9C)
 */
void INT_IELSR20 (void)__attribute__((interrupt));

/*
 * INT_IELSR21 (0xA0)
 */
void INT_IELSR21 (void)__attribute__((interrupt));

/*
 * INT_IELSR22 (0xA4)
 */
void INT_IELSR22 (void)__attribute__((interrupt));

/*
 * INT_IELSR23 (0xA8)
 */
void INT_IELSR23 (void)__attribute__((interrupt));

/*
 * INT_IELSR24 (0xAC)
 */
void INT_IELSR24 (void)__attribute__((interrupt));

/*
 * INT_IELSR25 (0xB0)
 */
void INT_IELSR25 (void)__attribute__((interrupt));

/*
 * INT_IELSR26 (0xB4)
 */
void INT_IELSR26 (void)__attribute__((interrupt));

/*
 * INT_IELSR27 (0xB8)
 */
void INT_IELSR27 (void)__attribute__((interrupt));

/*
 * INT_IELSR28 (0xBC)
 */
void INT_IELSR28 (void)__attribute__((interrupt));

/*
 * INT_IELSR29 (0xC0)
 */
void INT_IELSR29 (void)__attribute__((interrupt));

/*
 * INT_IELSR30 (0xC4)
 */
void INT_IELSR30 (void)__attribute__((interrupt));

/*
 * INT_IELSR31 (0xC8)
 */
void INT_IELSR31 (void)__attribute__((interrupt));

/*
 * INT_DUMMY for reserved interrupt source
 */
void INT_DUMMY (void)__attribute__((interrupt));

#endif
