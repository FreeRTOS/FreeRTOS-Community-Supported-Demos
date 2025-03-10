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
 *********************************************************************************************************************/
/*********************************************************************************************************************
 * File Name    : hdwinit.c
 * H/W Platform : GENERIC_R9A02G021
 * Description  :
 *********************************************************************************************************************/
/*********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 20.01.2024 1.00     First Release
*         : 10.06.2024 1.20     Change the macro name endwith "DISABLE" to "FUNCTIONS"

**********************************************************************************************************************/
/*************************************************
 * Includes  <System Includes> , "Project Includes"
 *************************************************/
/* I/O Register and board definitions */
#include "platform.h"
#if BSP_CFG_CONFIGURATOR_SELECT == 1
#include "r_cg_macrodriver.h"
#endif

/*************************************************
 * Macro definitions
 *************************************************/

/*************************************************
 * Private global variables and functions
 *************************************************/
/* MCU I/O port configuration function declaration */
static void output_ports_configure (void);

/* Interrupt configuration function declaration */
static void interrupts_configure (void);

/* MCU peripheral module configuration function declaration */
static void peripheral_modules_enable (void);

/*************************************************
 * Function definition
 *************************************************/
/*************************************************
 * Function name: hdwinit
 * Description  : Peripheral function initialization
 * Arguments    : none
 * Return value : none
 **************************************************/
void hdwinit(void)
{
#if BSP_CFG_DATA_FLASH_ACCESS_ENABLE == 1
    volatile uint32_t w_count;
#endif
    bsp_register_protect_open();
#if BSP_CFG_INTERRUPT_SETTING_API_FUNCTIONS == 0
    bsp_mapped_interrupt_open();
#endif
    output_ports_configure();
    interrupts_configure();
    peripheral_modules_enable();

    /* Data flash access control */
#if BSP_CFG_DATA_FLASH_ACCESS_ENABLE == 1
    R_FLCN->DFLCTL_b.DFLEN = 1U;
    /* WAIT_LOOP */
    for (w_count = 0U; w_count < 2U; w_count++)
    {
        R_BSP_NOP();
    }
#endif
} /* End of function hdwinit() */

/*************************************************
 * Function name: output_ports_configure
 * Description  : Output port setting
 * Arguments    : none
 * Return value : none
 **************************************************/
static void output_ports_configure(void)
{
    /* Add code here to setup additional output ports */
    R_BSP_NOP();
} /* End of function output_ports_configure() */

/*************************************************
 * Function name: interrupts_configure
 * Description  : Interrupt setting
 * Arguments    : none
 * Return value : none
 **************************************************/
static void interrupts_configure(void)
{
    /* Add code here to setup additional interrupts */
    R_BSP_NOP();
    machine_timer_create();
} /* End of function interrupts_configure() */

/*************************************************
 * Function name: peripheral_modules_enable
 * Description  : Peripheral module setting
 * Arguments    : none
 * Return value : none
 **************************************************/
static void peripheral_modules_enable(void)
{
    /* Add code here to enable peripherals used by the application */
#if BSP_CFG_CONFIGURATOR_SELECT == 1
    /* Smart Configurator initialization function */
    R_Systeminit();
#endif
} /* End of function peripheral_modules_enable() */
