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
* File Name        : r_cg_vect_table.c
* Version          : 1.0.30
* Device(s)        : R9A02G0214CNE
* Description      : None
* Creation Date    : 
***********************************************************************************************************************/

#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"


static void nvect_function (void);
static void nmi_handler (void);
void initialize_vect (void);

#define VECT_SECT          __attribute__ ((section (".vects")))
const void * gp_Vectors[] VECT_SECT = {
/*
 * Reserved (0x00)
 */
    INT_DUMMY,

/*
 * Reserved (0x04)
 */
    INT_DUMMY,

/*
 * Reserved (0x08)
 */
    INT_DUMMY,

/*
 * INT_ACLINT_MSIP (0x0C)
 */
    INT_ACLINT_MSIP,

/*
 * Reserved (0x10)
 */
    INT_DUMMY,

/*
 * Reserved (0x14)
 */
    INT_DUMMY,

/*
 * Reserved (0x18)
 */
    INT_DUMMY,

/*
 * INT_ACLINT_MTIP (0x1C)
 */
    INT_ACLINT_MTIP,

/*
 * Reserved (0x20)
 */
    INT_DUMMY,

/*
 * Reserved (0x24)
 */
    INT_DUMMY,

/*
 * Reserved (0x28)
 */
    INT_DUMMY,

/*
 * Reserved (0x2C)
 */
    INT_DUMMY,

/*
 * Reserved (0x30)
 */
    INT_DUMMY,

/*
 * Reserved (0x34)
 */
    INT_DUMMY,

/*
 * Reserved (0x38)
 */
    INT_DUMMY,

/*
 * Reserved (0x3C)
 */
    INT_DUMMY,

/*
 * Reserved (0x40)
 */
    INT_DUMMY,

/*
 * Reserved (0x44)
 */
    INT_DUMMY,

/*
 * Reserved (0x48)
 */
    INT_DUMMY,

/*
 * INT_IELSR0 (0x4C)
 */
    INT_IELSR0,

/*
 * INT_IELSR1 (0x50)
 */
    INT_IELSR1,

/*
 * INT_IELSR2 (0x54)
 */
    INT_IELSR2,

/*
 * INT_IELSR3 (0x58)
 */
    INT_IELSR3,

/*
 * INT_IELSR4 (0x5C)
 */
    r_Config_ICU_irq4_interrupt,

/*
 * INT_IELSR5 (0x60)
 */
    INT_IELSR5,

/*
 * INT_IELSR6 (0x64)
 */
    INT_IELSR6,

/*
 * INT_IELSR7 (0x68)
 */
    INT_IELSR7,

/*
 * INT_IELSR8 (0x6C)
 */
    r_Config_UART0_interrupt_send,

/*
 * INT_IELSR9 (0x70)
 */
    r_Config_UART0_interrupt_receive,

/*
 * INT_IELSR10 (0x74)
 */
    INT_IELSR10,

/*
 * INT_IELSR11 (0x78)
 */
    INT_IELSR11,

/*
 * INT_IELSR12 (0x7C)
 */
    INT_IELSR12,

/*
 * INT_IELSR13 (0x80)
 */
    INT_IELSR13,

/*
 * INT_IELSR14 (0x84)
 */
    INT_IELSR14,

/*
 * INT_IELSR15 (0x88)
 */
    INT_IELSR15,

/*
 * INT_IELSR16 (0x8C)
 */
    INT_IELSR16,

/*
 * INT_IELSR17 (0x90)
 */
    r_Config_UART0_interrupt_error,

/*
 * INT_IELSR18 (0x94)
 */
    INT_IELSR18,

/*
 * INT_IELSR19 (0x98)
 */
    INT_IELSR19,

/*
 * INT_IELSR20 (0x9C)
 */
    INT_IELSR20,

/*
 * INT_IELSR21 (0xA0)
 */
    INT_IELSR21,

/*
 * INT_IELSR22 (0xA4)
 */
    INT_IELSR22,

/*
 * INT_IELSR23 (0xA8)
 */
    INT_IELSR23,

/*
 * INT_IELSR24 (0xAC)
 */
    INT_IELSR24,

/*
 * INT_IELSR25 (0xB0)
 */
    INT_IELSR25,

/*
 * INT_IELSR26 (0xB4)
 */
    INT_IELSR26,

/*
 * INT_IELSR27 (0xB8)
 */
    INT_IELSR27,

/*
 * INT_IELSR28 (0xBC)
 */
    INT_IELSR28,

/*
 * INT_IELSR29 (0xC0)
 */
    INT_IELSR29,

/*
 * INT_IELSR30 (0xC4)
 */
    INT_IELSR30,

/*
 * INT_IELSR31 (0xC8)
 */
    INT_IELSR31,
};
#define EXVECT_SECT          __attribute__ ((section (".nvect")))
const void * gp_ExceptVectors[] EXVECT_SECT = {
    nvect_function
};

void nvect_function(void)
{
    /* Check the contents of mcause and implement a process to branch to the appropriate process
       after determining what happened. */
    /* Start user code for nvect_function. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
};

void nmi_handler(void)
{
    /* Start user code for nmi_handler. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
};

void initialize_vect(void)
{
    R_CPU_AUX->NMIADDR = (uint32_t)nmi_handler;
    /* The mtvec register must be set even if the interrupt vector table is not used. */
    /* Set the value (address of nvect_function()(0x1C0) >> 6)  to mtvec[31:6] */
    /* mtvec.BASE = 0x07; */
    asm( "li t0, 0x1C2" );
    asm( "csrw mtvec, t0" );    /* Set mtvec. */

    /* The mtvt register must be set when using the interrupt vector table. */
    /* Set the value (address of VECT_SECT(0xC0) >> 6) to mtvt[31:6] */
    /* mtvt.MTVT = 0x03; */
    asm( "li t0, 0xC0" );
    asm( "csrw mtvt, t0" );    /* Set mtvt. */
};
