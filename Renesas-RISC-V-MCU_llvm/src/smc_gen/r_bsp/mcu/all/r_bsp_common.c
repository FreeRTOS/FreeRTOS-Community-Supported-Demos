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
* File Name    : r_bsp_common.c
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 20.01.2024 1.00     First Release
*         : 10.06.2024 1.20     Change the macro name endwith "DISABLE" to "FUNCTIONS"
***********************************************************************************************************************/

/*************************************************
 * Includes  <System Includes> , "Project Includes"
 *************************************************/
#include "platform.h"

/*************************************************
 * Macro definitions
 *************************************************/
#define BSP_PRV_OVERHEAD_CYCLES        (90U)    /* R_BSP_SoftwareDelay() overhead per call */
#define BSP_PRV_OVERHEAD_CYCLES_64     (1300U)    /* R_BSP_SoftwareDelay() overhead per call using 64-bit ints */
#define BSP_CPU_CYCLES_PER_LOOP        (3U)
#define BSP_CPU_CYCLES_ADJUST          (4U)
/* Key code for writing PRCR register. */
#define BSP_PRV_PRCR_KEY        (0xA500U)
/* Key code for writing SRAMPRCR, ECC, ECC2 registers. */
#define BSP_PRV_SRAM_KEY        (0x78U << 1)
/*************************************************
 * Private global variables and functions
 *************************************************/
/* Used for holding reference counters for protection bits. */
static volatile uint16_t s_protect_counters[BSP_REG_PROTECT_TOTAL_ITEMS];

/* Masks for setting or clearing the PRCR register. Use -3 for size because SRAMPRCR, ECC and ECC2 in SRAM is used
   differently. */
static const uint16_t s_prcr_masks[] = 
{
    0x0001U,         /* PRC0. */
    0x0002U,         /* PRC1. */
    0x0008U          /* PRC3. */

};
/*************************************************
 * Function definition
 *************************************************/
extern void _delay_wait (uint32_t count);

/**********************************************************************************************************************
 * Function Name: R_BSP_GetVersion
 ******************************************************************************************************************//**
 * @brief Returns the current version of the r_bsp.
 * @return Version of the r_bsp.
 * @details This function will return the version of the currently installed r_bsp. The version number is encoded 
 * where the top 2 bytes are the major version number and the bottom 2 bytes are the minor version number. For 
 * example, Version 4.25 would be returned as 0x00040019.
 */
uint32_t R_BSP_GetVersion(void)
{
    /* These version macros are defined in platform.h. */
    return ((((uint32_t)R_BSP_VERSION_MAJOR) << 16) | ((uint32_t)R_BSP_VERSION_MINOR));
} /* End of function R_BSP_GetVersion() */

/**********************************************************************************************************************
 * Function Name: R_BSP_GetIClkFreqHz
 ******************************************************************************************************************//**
 * @brief Returns the system clock frequency.
 * @return System clock frequency specified by the r_bsp.
 * @details This function returns the system clock frequency. For example, when the system clock is set to 120 MHz in 
 * r_bsp_config_h and the r_bsp has completed to specify the clock setting, then even if the user changed the system 
 * clock frequency to 60 MHz, the return value is '60000000'.
 */
uint32_t R_BSP_GetIClkFreqHz(void)
{
    return get_iclk_freq_hz();  // Get the MCU specific ICLK frequency
}

/**********************************************************************************************************************
 * Function Name: R_BSP_StartClock
 ******************************************************************************************************************//**
 * @brief Start the specified clock and return.
 * @param[in] mode Clock to start.
 * @retval BSP_OK BSP_OK if the specified clock is started.
 * @retval BSP_ARG_ERROR BSP_ARG_ERROR if the specified clock is incorrect.
 * @details This function starts the specified clock.
 * Specify one of the following for mode.
 * HOCO  : High-speed on-chip oscillator
 * EXTAL : External clock
 * SOSC  : Subsystem clock
 * MOCO  : Middle-speed on-chip oscillator
 * LOCO  : Low-speed on-chip oscillator
 */
#if BSP_CFG_CLOCK_OPERATION_API_FUNCTIONS == 0
e_bsp_err_t R_BSP_StartClock(e_clock_mode_t mode)
{
    return (start_clock(mode));
} 
#endif /* End of function R_BSP_StartClock() */

/**********************************************************************************************************************
 * Function Name: R_BSP_StopClock
 ******************************************************************************************************************//**
 * @brief Stop the specified clock and return.
 * @param[in] mode Clock to stop.
 * @retval BSP_OK BSP_OK if the specified clock is stopped.
 * @retval BSP_ERROR2 BSP_ERROR2 if the specified clock can not be stopped because it is ICLK clock's source.
 * @retval BSP_ARG_ERROR BSP_ARG_ERROR if the specified clock is incorrect.
 * @details This function stops the specified clock.
 * Specify one of the following for mode.
 * HOCO  : High-speed on-chip oscillator
 * EXTAL : External clock
 * SOSC  : Subsystem clock
 * MOCO  : Middle-speed on-chip oscillator
 * LOCO  : Low-speed on-chip oscillator
 */
#if BSP_CFG_CLOCK_OPERATION_API_FUNCTIONS == 0
e_bsp_err_t R_BSP_StopClock(e_clock_mode_t mode)
{
    return (stop_clock(mode));
} 
#endif /* End of function R_BSP_StopClock() */

/**********************************************************************************************************************
 * Function Name: R_BSP_ChangeICLKClockSetting
 ******************************************************************************************************************//**
 * @brief Switch CPU/peripheral hardware clock (ICLK) clock source and return.
 * @param[in] mode Clock to switch.
 * @param[in] iclkdiv Frequency divider.
 * @retval BSP_OK BSP_OK when switching to the specified clock.
 * @retval BSP_ERROR1 BSP_ERROR1 when the specified clock is not oscillating.
 * @retval BSP_ERROR3 BSP_ERROR3 when an unsupported state transition was specified. Refer to the user's manual.
 * @retval BSP_ARG_ERROR BSP_ARG_ERROR if the specified clock is incorrect.
 * @details This function switches the specified clock.
 * Specify one of the following for mode.
 * HOCO  : High-speed on-chip oscillator
 * EXTAL : External clock
 * SOSC  : Subsystem clock
 * MOCO  : Middle-speed on-chip oscillator
 * LOCO  : Low-speed on-chip oscillator
 */
#if BSP_CFG_CHANGE_CLOCK_SETTING_API_FUNCTIONS == 0
e_bsp_err_t R_BSP_ChangeICLKClockSetting(e_clock_mode_t mode, e_clock_div_t iclkdiv, e_clock_div_t pclkdiv)
{
    return (change_iclk_clock_setting(mode, iclkdiv, pclkdiv));
}
#endif /* End of function R_BSP_SetClockSource() */

/**********************************************************************************************************************
 * Function Name: R_BSP_DelayCycle
 ******************************************************************************************************************//**
 * @brief Delay the specified duration in CPU cycle.
 * @param[in] wait_cycle The number of CPU cycle to delay.
 * @details This is function that may be called for all MCU targets to implement a specific wait time.
 * _delay_wait function which is called by this function is written in assembly language. It takes 3 CPU cycles.
 * So, please use following formula to calculate your input value: wait_cycle = Delay time (us) * Frequency (MHz) / 3
 */
void R_BSP_DelayCycle(uint32_t wait_cycle)
{
    _delay_wait(wait_cycle);
}

/**********************************************************************************************************************
 * Function Name: R_BSP_SoftwareDelay
 ******************************************************************************************************************//**
 * @brief Delay the specified duration in units and return.
 * @param[in] delay The number of 'units' to delay.
 * @param[in] units The 'base' for the unitsspecified.
 * @retval BSP_OK BSP_OK if delay executed.
 * @retval BSP_ERROR1 BSP_ERROR1 if delay/units combination resulted in overflow/underflow.
 * @details This is function that may be called for all MCU targets to implement a specific wait time.
 * The actual delay time is plus the overhead at a specified duration. The overhead changes under the influence of
 * the compiler, operating frequency and ROM cache. When the operating frequency is low, or the specified duration in
 * units of microsecond level, please note that the error becomes large.
 */
e_bsp_err_t R_BSP_SoftwareDelay(uint32_t delay, e_bsp_delay_units_t units)
{
    volatile uint32_t iclk_rate;
    volatile uint32_t delay_cycles;
    volatile uint32_t loop_cnt;
    volatile uint64_t loop_cnt_64;
    volatile uint64_t delay_cycles_64;

    iclk_rate = R_BSP_GetIClkFreqHz();    /* Get the current ICLK frequency. */

    /*
     * In order to handle all possible combinations of delay/ICLK it is necessary to use 64-bit
     * integers (not all MCUs have floating point support). However, there is no native hw support
     * for 64 bitintegers so it requires many more clock cycles. This is not an issue if the
     * requested delay is long enough and the ICLK is fast, but for delays in the low microseconds
     * and/or a slow ICLK we use 32 bit integers to reduce the overhead cycles of this function
     * by approximately a third and stand the best chance of achieving the requested delay.
     */
    if ((BSP_DELAY_MICROSECS == units) &&
        (delay <= (0xFFFFFFFFUL / iclk_rate)))    /* Ensure (iclk_rate * delay) will not exceed 32 bits. */
    {
        delay_cycles = ((iclk_rate * delay) / units);

        if (delay_cycles > BSP_PRV_OVERHEAD_CYCLES)
        {
            delay_cycles -= BSP_PRV_OVERHEAD_CYCLES;
        }
        else
        {
            delay_cycles = 0U;
        }

        loop_cnt = delay_cycles / BSP_CPU_CYCLES_PER_LOOP;

        if (0U == loop_cnt)
        {
            /* The requested delay is too large/small for the current ICLK. Return BSP_ERROR1 which
             * also results in the minimum possible delay. */
            return BSP_ERROR1;
        }
    }
    else
    {
        /* Casting is valid because it matches the type to the right side or argument. */
        delay_cycles_64 = (((uint64_t)iclk_rate * (uint64_t)delay) / units);

        if (delay_cycles_64 > BSP_PRV_OVERHEAD_CYCLES_64)
        {
            delay_cycles_64 -= BSP_PRV_OVERHEAD_CYCLES_64;
        }
        else
        {
            delay_cycles_64 = 0U;
        }

        loop_cnt_64 = delay_cycles_64 / BSP_CPU_CYCLES_PER_LOOP;

        if ((loop_cnt_64 > 0xFFFFFFFFUL) || (0U == loop_cnt_64))
        {
            /* The requested delay is too large/small for the current ICLK. Return BSP_ERROR1 which
             * also results in the minimum possible delay. */
            return BSP_ERROR1;
        }

        /* Casting is valid because it matches the type to the right side or argument. */
        loop_cnt = (uint32_t)loop_cnt_64;
    }
    /* The BSP_CPU_CYCLES_ADJUST is necessary necessary for the accuracy of the delay function */
    _delay_wait (loop_cnt);

    return BSP_OK;
} /* End of function R_BSP_SoftwareDelay() */

/**********************************************************************************************************************
 * Function Name: R_BSP_RegisterProtectEnable
 ******************************************************************************************************************//**
 * @brief Enables write protection for selected registers.
 * @param[in] regs_to_protect Which registers to enable write protection for.
 * @details This function enables write protection for the input registers. Only certain MCU registers have the 
 * ability to be write protected. To see which registers are available to be protected by this function look at the 
 * e_bsp_reg_protect_t enum in r_bsp_common.h for your MCU.
 * This function, and R_BSP_RegisterProtectDisable(), use counters for each entry in the e_bsp_reg_protect_t enum so 
 * that users can call these functions multiple times without problem.
 * @note 
 * (1) About why counters are needed. 
 * See the application note for details. (TBD)
 */
void R_BSP_RegisterProtectEnable(e_bsp_reg_protect_t regs_to_protect)
{
    /* Is it safe to disable write access? */
    if (0 != s_protect_counters[regs_to_protect])
    {
        /* Decrement the protect counter */
        s_protect_counters[regs_to_protect]--;
    }

    /* Is it safe to disable write access? */
    if (0 == s_protect_counters[regs_to_protect])
    {
        if (BSP_REG_PROTECT_SRAM == regs_to_protect)
        {
            /* Enable protection using SRAMPRCR register. */
            /* When writing to the PRCR register the upper 8-bits must be the correct key. Set lower bits to 0 to
               disable writes.
               b7:b1  KW - Write 0x78 to upper 7 bits simultaneously to enable writing to bit 0
               b0     SRAMPRCR  - Please check the user's manual.*/
            R_SRAM->SRAMPRCR = BSP_PRV_SRAM_KEY & (~0x01U);
        }
        else if (BSP_REG_PROTECT_ECC == regs_to_protect)
        {
            /* Enable protection using ECCPRCR register. */
            /* When writing to the PRCR register the upper 8-bits must be the correct key. Set lower bits to 0 to
               disable writes.
               b7:b1  KW - Write 0x78 to upper 7 bits simultaneously to enable writing to bit 0
               b0     ECCPRCR  - Please check the user's manual.*/
            R_SRAM->ECCPRCR = BSP_PRV_SRAM_KEY & (~0x01U);
        }
        else if (BSP_REG_PROTECT_ECC2 == regs_to_protect)
        {
            /* Enable protection using ECCPRCR2 register. */
            /* When writing to the PRCR register the upper 8-bits must be the correct key. Set lower bits to 0 to
               disable writes.
               b7:b1  KW - Write 0x78 to upper 7 bits simultaneously to enable writing to bit 0
               b0     ECCPRCR2  - Please check the user's manual.*/
            R_SRAM->ECCPRCR2 = BSP_PRV_SRAM_KEY & (~0x01U);
        }
        else if (BSP_REG_PROTECT_PMNPFS == regs_to_protect)
        {
            /* Enable protection using PWPR register */
            /* Clear the PFSWE bit, this disables writing to the PmnPFS register.
               Set 1 to the B0WI bit, this disables writing to the PFSWE bit in the PWPR register.*/
            R_PFS->PWPR_b.PFSWE = 0U;
            R_PFS->PWPR_b.B0WI = 1U;
        }
        else
        {
            /* Enable protection using PRCR register. */
            /* When writing to the PRCR register the upper 8-bits must be the correct key. Set lower bits to 0 to
               disable writes.
               b15:b8 PRKEY - Write 0xA5 to upper byte to enable writing to lower byte
               b7:b4  Reserved (set to 0)
               b3     PRC3  - Please check the user's manual.
               b2     Reserved (set to 0)
               b1     PRC1  - Please check the user's manual.
               b0     PRC0  - Please check the user's manual.
            */
            R_SYSC->PRCR = (uint16_t)((R_SYSC->PRCR | BSP_PRV_PRCR_KEY) & (~s_prcr_masks[regs_to_protect]));
        }
    }
} /* End of function R_BSP_RegisterProtectEnable() */

/**********************************************************************************************************************
 * Function Name: R_BSP_RegisterProtectDisable
 ******************************************************************************************************************//**
 * @brief Disables write protection for selected registers.
 * @param[in] regs_to_unprotect Which registers to disable write protection for.
 * @details This function disables write protection for the input registers. Only certain MCU registers have the 
 * ability to be write protected. To see which registers are available to be protected by this function look at the 
 * e_bsp_reg_protect_t enum in r_bsp_common.h for your MCU.
 * This function, and R_BSP_RegisterProtectEnable(), use counters for each entry in the e_bsp_reg_protect_t enum so that 
 * users can call these functions multiple times without problem.
 * @note 
 * (1) About why counters are needed. 
 * See the application note for details. (TBD)
 */
void R_BSP_RegisterProtectDisable(e_bsp_reg_protect_t regs_to_unprotect)
{
    /* If this is first entry then disable protection. */
    if (0 == s_protect_counters[regs_to_unprotect])
    {
        if (BSP_REG_PROTECT_SRAM == regs_to_unprotect)
        {
            /* Disable protection using SRAMPRCR register. */
            /* When writing to the PRCR register the upper 8-bits must be the correct key. Set lower bits to 0 to
               enable writes.
               b7:b1  KW - Write 0x78 to upper 7 bits simultaneously to enable writing to bit 0
               b0     SRAMPRCR  - Please check the user's manual.*/
            R_SRAM->SRAMPRCR = BSP_PRV_SRAM_KEY | 0x01U;
        }
        else if (BSP_REG_PROTECT_ECC == regs_to_unprotect)
        {
            /* Disable protection using ECCPRCR register. */
            /* When writing to the PRCR register the upper 8-bits must be the correct key. Set lower bits to 0 to
               enable writes.
               b7:b1  KW - Write 0x78 to upper 7 bits simultaneously to enable writing to bit 0
               b0     ECCPRCR  - Please check the user's manual.*/
            R_SRAM->ECCPRCR = BSP_PRV_SRAM_KEY | 0x01U;
        }
        else if (BSP_REG_PROTECT_ECC2 == regs_to_unprotect)
        {
            /* Disable protection using ECCPRCR2 register. */
            /* When writing to the PRCR register the upper 8-bits must be the correct key. Set lower bits to 1 to
               enable writes.
               b7:b1  KW - Write 0x78 to upper 7 bits simultaneously to enable writing to bit 0
               b0     ECCPRCR2  - Please check the user's manual.*/
            R_SRAM->ECCPRCR2 = BSP_PRV_SRAM_KEY | 0x01U;
        }
        else if (BSP_REG_PROTECT_PMNPFS == regs_to_unprotect)
        {
            /* Disable protection using PWPR register */
            /* Clear the B0WI bit, this enables writing to the PFSWE bit in the PWPR register.
               Set 1 to the PFSWE bit, this enables writing to the PmnPFS register.*/
            R_PFS->PWPR_b.B0WI = 0U;
            R_PFS->PWPR_b.PFSWE = 1U;
        }
        else
        {
            /* Disable protection using PRCR register. */
            /* When writing to the PRCR register the upper 8-bits must be the correct key.
               Set lower bits to 1 to enable writes.
               b15:b8 PRKEY - Write 0xA5 to upper byte to enable writing to lower byte
               b7:b4  Reserved (set to 0)
               b3     PRC3  - Please check the user's manual.
               b2     Reserved (set to 0)
               b1     PRC1  - Please check the user's manual.
               b0     PRC0  - Please check the user's manual.
            */
            R_SYSC->PRCR = (uint16_t)((R_SYSC->PRCR | BSP_PRV_PRCR_KEY) | s_prcr_masks[regs_to_unprotect]);
        }
    }

    /* Increment the protect counter */
    s_protect_counters[regs_to_unprotect]++;

} /* End of function R_BSP_RegisterProtectDisable() */

/***********************************************************************************************************************
* Function Name: bsp_register_protect_open
* Description  : Initializes variables needed for register protection functionality.
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void bsp_register_protect_open(void)
{
    uint32_t i;
    /* Initialize reference counters to 0. */
    /* WAIT_LOOP */
    for (i = 0; i < BSP_REG_PROTECT_TOTAL_ITEMS; i++ )
    {
        s_protect_counters[i] = 0;
    }
} /* End of function bsp_register_protect_open() */

