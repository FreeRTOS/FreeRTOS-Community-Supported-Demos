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

/* Start user code */
extern void freertos_risc_v_mtimer_interrupt_handler( void );
extern void freertos_risc_v_interrupt_handler( void );
extern void freertos_renesas_risc_v_exception_handler( void );
extern void freertos_renesas_risc_v_trap_handler( void );
/* End user code */

static void nvect_function (void);
static void nmi_handler (void) __attribute__((naked)) __attribute__((used));
void initialize_vect (void);

#define VECT_SECT          __attribute__ ((section (".vects")))
const void * gp_Vectors[] VECT_SECT = {
/*
 * Reserved (0x00)
 */
		freertos_risc_v_interrupt_handler,

/*
 * Reserved (0x04)
 */
		freertos_risc_v_interrupt_handler,

/*
 * Reserved (0x08)
 */
		freertos_risc_v_interrupt_handler,

/*
 * INT_ACLINT_MSIP (0x0C)
 */
		freertos_risc_v_mtimer_interrupt_handler,

/*
 * Reserved (0x10)
 */
		freertos_risc_v_interrupt_handler,

/*
 * Reserved (0x14)
 */
		freertos_risc_v_interrupt_handler,

/*
 * Reserved (0x18)
 */
		freertos_risc_v_interrupt_handler,

/*
 * INT_ACLINT_MTIP (0x1C)
 */
	freertos_risc_v_mtimer_interrupt_handler,

/*
 * Reserved (0x20)
 */
	freertos_risc_v_interrupt_handler,

/*
 * Reserved (0x24)
 */
	freertos_risc_v_interrupt_handler,

/*
 * Reserved (0x28)
 */
	freertos_risc_v_interrupt_handler,

/*
 * Reserved (0x2C)
 */
	freertos_risc_v_interrupt_handler,

/*
 * Reserved (0x30)
 */
	freertos_risc_v_interrupt_handler,

/*
 * Reserved (0x34)
 */
	freertos_risc_v_interrupt_handler,

/*
 * Reserved (0x38)
 */
	freertos_risc_v_interrupt_handler,

/*
 * Reserved (0x3C)
 */
	freertos_risc_v_interrupt_handler,

/*
 * Reserved (0x40)
 */
	freertos_risc_v_interrupt_handler,

/*
 * Reserved (0x44)
 */
	freertos_risc_v_interrupt_handler,

/*
 * Reserved (0x48)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR0 (0x4C)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR1 (0x50)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR2 (0x54)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR3 (0x58)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR4 (0x5C)
 */
	//freertos_risc_v_interrupt_handler,
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR5 (0x60)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR6 (0x64)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR7 (0x68)
 */
	freertos_risc_v_interrupt_handler,

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
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR11 (0x78)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR12 (0x7C)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR13 (0x80)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR14 (0x84)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR15 (0x88)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR16 (0x8C)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR17 (0x90)
 */
	r_Config_UART0_interrupt_error,

/*
 * INT_IELSR18 (0x94)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR19 (0x98)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR20 (0x9C)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR21 (0xA0)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR22 (0xA4)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR23 (0xA8)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR24 (0xAC)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR25 (0xB0)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR26 (0xB4)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR27 (0xB8)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR28 (0xBC)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR29 (0xC0)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR30 (0xC4)
 */
	freertos_risc_v_interrupt_handler,

/*
 * INT_IELSR31 (0xC8)
 */
	freertos_risc_v_interrupt_handler,
};
#define EXVECT_SECT          __attribute__ ((section (".nvect"))) __attribute__((naked)) __attribute__((used))

void nvect_function(void) EXVECT_SECT;

void nvect_function(void)

{

    asm( "j freertos_renesas_risc_v_trap_handler" );

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
