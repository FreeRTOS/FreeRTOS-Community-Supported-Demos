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
* File Name    : r_bsp_machine_timer.c
* Description  : Implements functions that generate interrupt support.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 10.06.2024 1.20     Support machine timer setting
*         : 26.07.2024 1.21     Add the code to extern set_mtimer_cmp, reset_mtimer and get_mtimer function.
*         :                     Add interval_value variable.
*         :                     Add new functions: get_interval_value(), machine_timer_refresh().
*         :                     In machine_timer_create(), remove setting of counter and compare register, add the code
*         :                     to get the interval value in the count unit.
*         :                     In machine_timer_start(), call machine_timer_refresh() at first.
*         :                     In machine_timer_stop(), call reset_mtimer() at the end.
*         :                     In trigger_software_interrupt() and clear_software_interrupt, correct the value of MSIP bit.
*         : 17.09.2024 1.22     Remove volitale in machine_timer_refresh() function.
*         :                     Remove get interval value step in machine_timer_create().
*         :                     Add get interval value step in machine_timer_start() function.
***********************************************************************************************************************/
#include "platform.h"
#include "r_cg_macrodriver.h"
#include "r_bsp_machine_timer.h"

#if BSP_CFG_MACHINE_TIMER == 1
extern void set_mtimer_cmp(uint64_t count);
extern void reset_mtimer(void);
extern uint64_t get_mtimer(void);
volatile uint64_t interval_value;
#endif
/***********************************************************************************************************************
* Function Name: machine_timer_create
* Description  : This function initializes machine timer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void machine_timer_create(void)
{
#if BSP_CFG_MACHINE_TIMER == 1
    /* Select clock source */
    R_CPU_AUX->MACTCR_b.CLOCKSOURCE = BSP_CFG_MTIME_CLOCK_SOURCE;
    /* Set mtip priority */
    R_CLIC->clicintie7_b.IE = 0U;    /* disable mtip interrupt */
    R_CLIC->clicintctl7 = BSP_CFG_MTIP_PRIORITY;
    R_CLIC->clicintattr7 = _C3_INT_VECTOR_MODE;
#endif
#if BSP_CFG_SOFTWARE_INTERRUPT == 1
    /* Set msip priority */
    R_CLIC->clicintie3_b.IE = 0U;    /* disable msip interrupt */
    R_CLIC->clicintctl3 = (uint8_t)BSP_CFG_MSIP_PRIORITY;
    R_CLIC->clicintattr3 = _C3_INT_VECTOR_MODE;
#endif
}

#if BSP_CFG_MACHINE_TIMER == 1
/***********************************************************************************************************************
* Function Name: machine_timer_start
* Description  : This function starts machine timer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void machine_timer_start(void)
{
    /* Get interval value */
    interval_value = get_interval_value();
    /* Set compare value */
    machine_timer_refresh();
    R_CPU_AUX->MACTCR_b.ENABLE = 1U;
    R_CLIC->clicintie7_b.IE = 1U;    /* enable mtip interrupt */
}
/***********************************************************************************************************************
* Function Name: machine_timer_stop
* Description  : This function stops machine timer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void machine_timer_stop(void)
{
    R_CLIC->clicintie7_b.IE = 0U;    /* disable mtip interrupt */
    R_CPU_AUX->MACTCR_b.ENABLE = 0U;
    reset_mtimer();
}
/***********************************************************************************************************************
* Function Name: machine_timer_refresh
* Description  : This function sets the compare registers of machine timer.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void machine_timer_refresh(void)
{
    uint64_t value = get_mtimer();
    set_mtimer_cmp(value + interval_value);
}
/***********************************************************************************************************************
* Function Name: get_interval_value
* Description  : This function converts the interval value in ms/us/ns to the value in count unit.
*              : In order to handle all possible combinations of interval value and clock, it is necessary to use 64-bit
               : integers (not all MCUs have floating point support)
* Arguments    : None
* Return Value : result - The value in count unit
***********************************************************************************************************************/
uint64_t get_interval_value(void)
{
    uint64_t result = 0;
#if BSP_CFG_MTIME_INTERVAL_UNIT == 1
    result = BSP_CFG_MTIME_INTERVAL_VALUE;
#else
    volatile uint64_t clockValue;
#if BSP_CFG_MTIME_CLOCK_SOURCE == 0
    // Using Machine timer clock
    clockValue = 32768; //Hz
#else
    // Using CPU clock
    clockValue = R_BSP_GetIClkFreqHz();
#endif
    /* calculation: result = clock value * interval value / unit.
     * the result is rounded up by half */
    result = (uint64_t) ((2 * (clockValue * BSP_CFG_MTIME_INTERVAL_VALUE)
            + BSP_CFG_MTIME_INTERVAL_UNIT) / (2 * BSP_CFG_MTIME_INTERVAL_UNIT));
#endif
    return result;
}
#endif
#if BSP_CFG_SOFTWARE_INTERRUPT == 1
/***********************************************************************************************************************
* Function Name: trigger_software_interrupt
* Description  : This function trigger software interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void trigger_software_interrupt(void)
{
    R_MTIME->msip_b.MSIP = 0U;    /* clear msip interrupt */
    R_CLIC->clicintie3_b.IE = 1U;    /* enable msip interrupt */
    R_MTIME->msip_b.MSIP = 1U;    /* trigger msip interrupt */
}
/***********************************************************************************************************************
* Function Name: clear_software_interrupt
* Description  : This function clear software interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void clear_software_interrupt(void)
{
    R_CLIC->clicintie3_b.IE = 0U;    /* disable msip interrupt */
    R_MTIME->msip_b.MSIP = 0U;    /* clear msip interrupt */
}
#endif
