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
* File Name    : mcu_clocks.c
* Description  : Contains clock specific routines
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 20.01.2024 1.00     First Release
*         : 10.06.2024 1.20     Change the macro name endwith "DISABLE" to "FUNCTIONS"
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define BSP_PRV_CKSEL_HOCO            (0x00U)
#define BSP_PRV_CKSEL_MOCO            (0x01U)
#define BSP_PRV_CKSEL_LOCO            (0x02U)
#define BSP_PRV_CKSEL_EXTCLK          (0x03U)
#define BSP_PRV_CKSEL_SUBCLK          (0x04U)
#define BSP_PRV_CLOCK_SUPPLY_TYPE_B   (((BSP_CFG_OFS1_REG_VALUE >> 31) & 0x00000001U) == 0U)

/* Convert divisor bitfield settings into divisor values to calculate startup clocks */
#define BSP_PRV_SCKDIVCR_DIV_VALUE(div)    (((div) & 8U) ? (3U << ((div) & ~8U)) : (1U << (div)))
#define BSP_PRV_ICLK_DIV_VALUE             BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_ICLK_DIV)
#define BSP_PRV_PCLKB_DIV_VALUE            BSP_PRV_SCKDIVCR_DIV_VALUE(BSP_CFG_PCLKB_DIV)
#define BSP_PRV_SCKDIVCR_DEFAULT           (0x4U)

/* Startup clock frequency of each system clock. */
#define BSP_STARTUP_ICLK_HZ                (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_ICLK_DIV_VALUE)
#define BSP_STARTUP_PCLKB_HZ               (BSP_STARTUP_SOURCE_CLOCK_HZ / BSP_PRV_PCLKB_DIV_VALUE)

#if  BSP_PRV_CKSEL_HOCO == BSP_CFG_CLOCK_SOURCE_SEL
#define BSP_STARTUP_SOURCE_CLOCK_HZ    (BSP_CFG_HOCO_HZ)
#elif  BSP_PRV_CKSEL_MOCO == BSP_CFG_CLOCK_SOURCE_SEL
#define BSP_STARTUP_SOURCE_CLOCK_HZ    (BSP_MOCO_HZ)
#elif  BSP_PRV_CKSEL_LOCO == BSP_CFG_CLOCK_SOURCE_SEL
#define BSP_STARTUP_SOURCE_CLOCK_HZ    (BSP_LOCO_HZ)
#elif  BSP_PRV_CKSEL_SUBCLK == BSP_CFG_CLOCK_SOURCE_SEL
#define BSP_STARTUP_SOURCE_CLOCK_HZ    (BSP_SOSC_HZ)
#else
#define BSP_STARTUP_SOURCE_CLOCK_HZ    (BSP_CFG_EXTAL_HZ)
#endif

#define BSP_HOCO_FREQ_SETTING           ((BSP_CFG_OFS1_REG_VALUE >> 12) & 0x7U)
#if BSP_HOCO_FREQ_SETTING == 0
#define BSP_CFG_HOCO_HZ                 (24000000U)
#elif BSP_HOCO_FREQ_SETTING == 2
#define BSP_CFG_HOCO_HZ                 (32000000U)
#elif BSP_HOCO_FREQ_SETTING == 4
#define BSP_CFG_HOCO_HZ                 (48000000U)
#else
#if BSP_CFG_HOCO_OPERATION == 1
#error "Error! Invalid HOCO frequency chosen (BSP_HOCO_FREQ_SETTING)"
#endif
#endif

/* Wait state definitions for MEMWAIT. */
#define BSP_PRV_MEMWAIT_NO_WAIT                 (0U)
#define BSP_PRV_MEMWAIT_WAIT                    (1U)
#define BSP_PRV_MEMWAIT_MAX_ZERO_WAIT_FREQ      (32000000U)

/* Wait state definitions for FLDWAITR. */
#define BSP_PRV_FLDWAITR_ONE_WAIT_CYCLES        (0U)
#define BSP_PRV_FLDWAITR_TWO_WAIT_CYCLES        (1U)
#define BSP_PRV_FLDWAITR_MAX_ONE_WAIT_FREQ      (32000000U)

/* Operating mode definitions */
#define BSP_PRV_OPERATING_MODE_HIGH_SPEED      (0U)
#define BSP_PRV_OPERATING_MODE_MIDDLE_SPEED    (1U)
#define BSP_PRV_OPERATING_MODE_LOW_SPEED       (3U)
#define BSP_PRV_OPERATING_MODE_SUBOSC_SPEED    (2U)

/* HOCO register value definitions */
#define BSP_PRV_HOCOCR2_VALUE                  (((BSP_CFG_OFS1_REG_VALUE >> 12) & 0x07U) << 3)

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* When using the user startup program, disable the following code. */
#if BSP_CFG_STARTUP_FUNCTIONS == 0
static void set_operating_frequency (void);
static void set_clock_source (void);
#endif /* BSP_CFG_STARTUP_FUNCTIONS == 0 */

static uint32_t get_clock_source_freq (e_clock_mode_t mode);

#if BSP_CFG_CHANGE_CLOCK_SETTING_API_FUNCTIONS == 0
static e_bsp_err_t change_iclk_clock_source (e_clock_mode_t mode);
static void bsp_clock_set_prechange (uint32_t requested_freq_hz);
static void bsp_clock_set_postchange (uint32_t requested_freq_hz);
#endif

/* When using the user startup program, disable the following code. */
#if BSP_CFG_STARTUP_FUNCTIONS == 0
/***********************************************************************************************************************
* Function name: mcu_clock_setup
* Description  : Contains clock functions called at device restart.
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
void mcu_clock_setup(void)
{
    /* Switch to high-speed operation */
    set_operating_frequency();
} /* End of function mcu_clock_setup() */

/***********************************************************************************************************************
* Function name: set_operating_frequency
* Description  : Configures the clock settings for each of the device clocks
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void set_operating_frequency(void)
{
    /* Protect off. */
    R_SYSC->PRCR = 0xA50BU;
    /* Some MCUs are not operating at full speed when they come out of reset.
       Set the MCU is operating at full speed before initializing any memory sections. */
    set_operating_mode(BSP_PRV_OPERATING_MODE_HIGH_SPEED);

    /* System clock source select - SCKSCR register */
    R_SYSC->SCKSCR = (uint8_t)BSP_CFG_CLOCK_SOURCE_SEL;

    /* Select the clock based upon user's choice. */
    set_clock_source();

#if !BSP_PRV_CLOCK_SUPPLY_TYPE_B
if (BSP_STARTUP_ICLK_HZ > BSP_PRV_MEMWAIT_MAX_ZERO_WAIT_FREQ)
{
    R_SYSC->MEMWAIT = BSP_PRV_MEMWAIT_WAIT;
}
if (BSP_STARTUP_ICLK_HZ > BSP_PRV_FLDWAITR_MAX_ONE_WAIT_FREQ)
{
    R_FLCN->FLDWAITR = BSP_PRV_FLDWAITR_TWO_WAIT_CYCLES;
}
#endif

    /* Set operating mode according to user setting */
    set_operating_mode(BSP_CFG_OPERATION_MODE);

    /* Set SCKDIVCR register*/
#if BSP_CFG_PARAM_CHECKING_ENABLE
#if   BSP_CFG_PCLKB_DIV > 6
    #error "Error! Invalid setting for BSP_CFG_PCLKB_DIV in r_bsp_config.h"
#endif
#if   BSP_CFG_ICLK_DIV > 6
    #error "Error! Invalid setting for BSP_CFG_ICLK_DIV in r_bsp_config.h"
#endif
#endif
    R_SYSC->SCKDIVCR = (uint32_t)(((BSP_CFG_ICLK_DIV & 0xFU) << 24) | ((BSP_CFG_PCLKB_DIV & 0xFU) << 8) 
                                    | BSP_PRV_SCKDIVCR_DEFAULT);

    /* Set CLKOUT */
#if BSP_CFG_CLKOUT_ENABLE == 1
    R_SYSC->CKOCR &= 0x7FU;    /* Disable CLKOUT */

    /* Set CLKOUT source */
#if BSP_CFG_PARAM_CHECKING_ENABLE
#if   BSP_CFG_CLKOUT_SOURCE_SEL > 4
    #error "Error! Invalid setting for BSP_CFG_CLKOUT_SEL in r_bsp_config.h"
#endif
#if BSP_CFG_CLKOUT_DIV > 7
    #error "Error! Invalid setting for BSP_CFG_CLKOUT_DIV in r_bsp_config.h"
#endif
#endif
    R_SYSC->CKOCR = (uint8_t)((BSP_CFG_CLKOUT_DIV & 0xFU)<<4) | (BSP_CFG_CLKOUT_SEL & 0xFU);

    /* Enable CLKOUT */
    R_SYSC->CKOCR |= 0x80U;
#else /* BSP_CFG_CLKOUT_ENABLE == 0 */
    /* Do nothing */
#endif /* BSP_CFG_CLKOUT_ENABLE == 1 */

    /* SUBCLK supply mode - OSMCR register */
    R_SYSC->OSMCR = (uint8_t)BSP_CFG_SUBCLK_SEL;

    /* Protect on. */
    R_SYSC->PRCR = 0xA500U;
}

/***********************************************************************************************************************
* Function name: set_clock_source
* Description  : Enables and disables clocks as chosen by the user. This function also implements the delays
*                needed for the clocks to stabilize.
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void set_clock_source(void)
{
    /* Set HOCO */
#if BSP_CFG_HOCO_OPERATION == 1
    /* HOCO is chosen. Start it operating if it is not already operating. */
    if (1 == R_SYSC->HOCOCR_b.HCSTP)
    {
        R_SYSC->HOCOCR2 = (uint8_t)BSP_PRV_HOCOCR2_VALUE;
        /* HOCO is chosen. Start it operating. */
        R_SYSC->HOCOCR = 0x00U;
    }
    /* WAIT_LOOP to make sure that the HOCO has stabilized */
    /* WAIT_LOOP */
    BSP_HARDWARE_REGISTER_WAIT(R_SYSC->OSCSF_b.HOCOSF,1);
    
#else /* BSP_CFG_HOCO_OPERATION == 0 */
    if (0 == R_SYSC->HOCOCR_b.HCSTP)
    {   
        /* Stop HOCO. */
        R_SYSC->HOCOCR = 0x01U;
        /* Confirm HOCO clock is stopped */
        /* WAIT_LOOP */
        BSP_HARDWARE_REGISTER_WAIT(R_SYSC->OSCSF_b.HOCOSF,0);
    }
#endif /* BSP_CFG_HOCO_OPERATION == 1 */

    /* Set EXTCLK */
#if BSP_CFG_EXTCLK_OPERATION == 1
    /* Operate EXTCLK */
    if (1 == R_SYSC->MOSCCR_b.MOSTP)
    {
        /* Start EXTCLK */
        R_SYSC->MOSCCR = 0x00U;
    }
#else /* BSP_CFG_EXTCLK_OPERATION == 0 */
    if (0 == R_SYSC->MOSCCR_b.MOSTP)
    {
        R_SYSC->MOSCCR = 0x01U;
    }
#endif /* BSP_CFG_EXTCLK_OPERATION == 1 */

    /* Set SUBCLK */
#if BSP_CFG_SUBCLK_OPERATION == 1
    if (1 == R_SYSC->SOSCCR_b.SOSTP)
    {
        /* Before operate SUBCLK, set SOMCR register */
        /* Set SOSCCR.SOSTP to 1 before set SOMCR register */
        /* Wait for five the SUBCLK cycles */
        /* 5 count of SUBCLK : (1000000/32768)*5 = 152.588us
           153 + 2 = 155us ("+2" is overhead cycle) */
        /* WAIT_LOOP */
        R_BSP_SoftwareDelay((uint32_t)155, BSP_DELAY_MICROSECS);

        R_SYSC->SOMCR = (uint8_t)BSP_CFG_SUBCLK_MODE;

        /* Set SUBCLK margin check */
        R_SYSC->SOMRG = (uint8_t)BSP_CFG_SUBCLK_MARGIN;

        /* Operate SUBCLK */
        R_SYSC->SOSCCR = 0x00U;
        /* Wait for the SUBCLK has stabilized (tSUBOSCWT) */
        /* tSUBOSCWT = 0.5s */
        /* WAIT_LOOP */
        R_BSP_SoftwareDelay((uint32_t)500, BSP_DELAY_MILLISECS);
    }
#else /* BSP_CFG_SUBCLK_OPERATION == 0 */
    /* Do nothing since default status of SUBCLK is stop */
#endif /* BSP_CFG_SUBCLK_OPERATION == 1 */

    /* Set LOCO */
#if BSP_CFG_LOCO_OPERATION == 1
    R_SYSC->LOCOCR = 0x00U;
    /* Wait for the LOCO has stabilized - tLOCOWT = 100us */
    /* WAIT_LOOP */
    R_BSP_SoftwareDelay((uint32_t)100, BSP_DELAY_MICROSECS);
#else /* BSP_CFG_LOCO_OPERATION == 0 */
    R_SYSC->LOCOCR = 0x01U;
    /* Wait for five the LOCO cycles */
    /* 5 count of LOCO : (1000000/32768)*5 = 152.588us
       153 + 2 = 155us ("+2" is overhead cycle) */
    /* WAIT_LOOP */
    R_BSP_SoftwareDelay((uint32_t)155, BSP_DELAY_MICROSECS);
#endif /* BSP_CFG_LOCO_OPERATION == 1 */

    /* Set MOCO */
#if BSP_CFG_MOCO_OPERATION == 1
    R_SYSC->MOCOCR = 0x00U;
    /* Wait for the MOCO has stabilized - tMOCOWT = 1us */
    /* WAIT_LOOP */
    R_BSP_SoftwareDelay((uint32_t)1, BSP_DELAY_MICROSECS);
#else /* BSP_CFG_MOCO_OPERATION == 0 */
    R_SYSC->MOCOCR = 0x01U;
    /* Wait for five the MOCO cycles */
    /* 5 count of MOCO : (1/8)*5 = 0.625us
        1 + 2 = 3us ("+2" is overhead cycle) */
    /* WAIT_LOOP */
    R_BSP_SoftwareDelay((uint32_t)3, BSP_DELAY_MICROSECS);
#endif /* BSP_CFG_MOCO_OPERATION == 1 */
}
#endif /* BSP_CFG_STARTUP_FUNCTIONS == 0 */

/***********************************************************************************************************************
* Function Name: get_clock_source_freq
* Description  : Return the clock sourec frequency in Hz.
* Arguments    : Clock source
* Return Value : uint32_t - the clock source frequency in Hz
***********************************************************************************************************************/
static uint32_t get_clock_source_freq(e_clock_mode_t mode)
{
    uint32_t sys_clock_src_freq = 0U;
    switch ((int)mode)
    {
        case BSP_PRV_CKSEL_LOCO:
            sys_clock_src_freq = BSP_LOCO_HZ;
            break;

        case BSP_PRV_CKSEL_HOCO:
            sys_clock_src_freq = BSP_CFG_HOCO_HZ;
            break;

        case BSP_PRV_CKSEL_EXTCLK:
            sys_clock_src_freq = BSP_CFG_EXTAL_HZ;
            break;

        case BSP_PRV_CKSEL_SUBCLK:
            sys_clock_src_freq = BSP_SOSC_HZ;
            break;

        default:
            sys_clock_src_freq = BSP_MOCO_HZ;
            break;
    }
    return sys_clock_src_freq;
}
/***********************************************************************************************************************
* Function Name: get_iclk_freq_hz
* Description  : Return the current ICLK frequency in Hz. Called by R_BSP_GetIClkFreqHz().
*                The system clock source can be changed at any time via SYSTEM.SCKCR3.BIT.CKSEL, so in order to
*                determine the ICLK frequency we need to first find the current system clock source and then,
*                in some cases where the clock source can be configured for multiple frequencies, calculate the
*                frequency at which it is currently running.
* Arguments    : None
* Return Value : uint32_t - the iclk frequency in Hz
***********************************************************************************************************************/
uint32_t get_iclk_freq_hz(void)
{
    uint32_t sys_clock_src_freq;

    /* Casting is valid because it matches the type to the retern value. */
    e_clock_mode_t cksel = (e_clock_mode_t)R_SYSC->SCKSCR;

    sys_clock_src_freq = get_clock_source_freq(cksel);

    /* Finally, divide the system clock source frequency by the currently set ICLK divider to get the ICLK frequency */
    return (sys_clock_src_freq / (uint32_t)(1U << R_SYSC->SCKDIVCR_b.ICK));
} /* End of function get_iclk_freq_hz() */

/***********************************************************************************************************************
 * Function name: start_clock
 * Description  : Start the specified clock
 * Arguments    : Clock to start
 * Return value : BSP_OK if the specified clock is started.
 *                BSP_ARG_ERROR if the specified clock is incorrect.
***********************************************************************************************************************/
#if BSP_CFG_CLOCK_OPERATION_API_FUNCTIONS == 0
e_bsp_err_t start_clock(e_clock_mode_t mode)
{
    e_bsp_err_t status = BSP_OK;
    switch (mode)
    {
        case HOCO:
            if (1U == R_SYSC->HOCOCR_b.HCSTP)
            {
                R_SYSC->HOCOCR = 0x00U;
                /* WAIT_LOOP to make sure that the HOCO has stabilized */
                /* WAIT_LOOP */
                BSP_HARDWARE_REGISTER_WAIT(R_SYSC->OSCSF_b.HOCOSF,1);
            }
            break;
        case SOSC:
            if (1U == R_SYSC->SOSCCR_b.SOSTP)
            {
                R_SYSC->SOSCCR = 0x00U;
                /* Wait for the SUBCLK has stabilized (tSUBOSCWT) */
                /* tSUBOSCWT = 0.5s */
                /* WAIT_LOOP */
                R_BSP_SoftwareDelay((uint32_t)500, BSP_DELAY_MILLISECS);
            }
            break;
        case MOCO:
            if (1U == R_SYSC->MOCOCR_b.MCSTP)
            {
                R_SYSC->MOCOCR = 0x00U;
                /* Wait for the MOCO has stabilized - tMOCOWT = 1us */
                /* WAIT_LOOP */
                R_BSP_SoftwareDelay((uint32_t)1, BSP_DELAY_MICROSECS);
            }
            break;
        case LOCO:
            if (1U == R_SYSC->LOCOCR_b.LCSTP)
            {
                R_SYSC->LOCOCR = 0x00U;
                /* Wait for the LOCO has stabilized - tLOCOWT = 100us */
                /* WAIT_LOOP */
                R_BSP_SoftwareDelay((uint32_t)100, BSP_DELAY_MICROSECS);
            }
            break;
        case EXTAL:
            if (1U == R_SYSC->MOSCCR_b.MOSTP)
            {
                /* Start EXTCLK */
                R_SYSC->MOSCCR = 0x00U;
            }
            break;
        default:
            status = BSP_ARG_ERROR;
            break;

    }
    return status;
}
#endif /* BSP_CFG_CLOCK_OPERATION_API_FUNCTIONS == 0 */

/***********************************************************************************************************************
 * Function name: stop_clock
 * Description  : Stop the specified clock
 * Arguments    : Clock to stop
 * Return value : BSP_OK if the specified clock is stopped.
 *                BSP_ERROR2 if the specified clock can not be stopped because it is ICLK clock's source.
 *                BSP_ARG_ERROR if the specified clock is incorrect.
***********************************************************************************************************************/
#if BSP_CFG_CLOCK_OPERATION_API_FUNCTIONS == 0
e_bsp_err_t stop_clock(e_clock_mode_t mode)
{
    e_bsp_err_t status = BSP_OK;

#if BSP_CFG_PARAM_CHECKING_ENABLE
    if ((uint8_t)mode == R_SYSC->SCKSCR)
    {
        return BSP_ERROR2;
    }
#endif

    switch (mode)
    {
        case HOCO:
            if (0U == R_SYSC->HOCOCR_b.HCSTP)
            {
                R_SYSC->HOCOCR = 0x01U;
                /* Confirm HOCO clock is stopped */
                /* WAIT_LOOP */
                BSP_HARDWARE_REGISTER_WAIT(R_SYSC->OSCSF_b.HOCOSF,0);
            }
            break;
        case SOSC:
            if (0U == R_SYSC->SOSCCR_b.SOSTP)
            {
                R_SYSC->SOSCCR = 0x01U;
                /* Wait for five the SUBCLK cycles */
                /* 5 count of SUBCLK : (1000000/32768)*5 = 152.588us
                153 + 2 = 155us ("+2" is overhead cycle) */
                /* WAIT_LOOP */
                R_BSP_SoftwareDelay((uint32_t)155, BSP_DELAY_MICROSECS);
            }
            break;
        case MOCO:
            if (0U == R_SYSC->MOCOCR_b.MCSTP)
            {
                R_SYSC->MOCOCR = 0x01U;
                /* Wait for five the MOCO cycles */
                /* 5 count of MOCO : (1/8)*5 = 0.625us
                1 + 2 = 3us ("+2" is overhead cycle) */
                /* WAIT_LOOP */
                R_BSP_SoftwareDelay((uint32_t)3, BSP_DELAY_MICROSECS);
            }
            break;
        case LOCO:
            if (0U == R_SYSC->LOCOCR_b.LCSTP)
            {
                R_SYSC->LOCOCR = 0x01U;
                /* Wait for five the LOCO cycles */
                /* 5 count of LOCO : (1000000/32768)*5 = 152.588us
                153 + 2 = 155us ("+2" is overhead cycle) */
                /* WAIT_LOOP */
                R_BSP_SoftwareDelay((uint32_t)155, BSP_DELAY_MICROSECS);
            }
            break;
        case EXTAL:
            if (0U == R_SYSC->MOSCCR_b.MOSTP)
            {
                R_SYSC->MOSCCR = 0x01U;
            }
            break;
        default:
            status = BSP_ARG_ERROR;
            break;

    }
    return status;
}
#endif /* BSP_CFG_CLOCK_OPERATION_API_FUNCTIONS == 0 */

/***********************************************************************************************************************
 * Function name: change_iclk_clock_source
 * Description  : Switch CPU/peripheral hardware clock(iCLK) clock source.
 * Arguments    : mode - Clock to switch.
 * Return value : BSP_OK when switching to the specified clock.
 *                BSP_ERROR1 The specified clock is not oscillating.
 *                BSP_ARG_ERROR An invalid argument was input.
 * Attention    : Start the clock to switch to before calling this function.
***********************************************************************************************************************/
#if BSP_CFG_CHANGE_CLOCK_SETTING_API_FUNCTIONS == 0
static e_bsp_err_t change_iclk_clock_source(e_clock_mode_t mode)
{
    e_bsp_err_t       status = BSP_OK;
    e_clock_mode_t    old_mode;

    /* Get current clock source */
    switch (R_SYSC->SCKSCR)
        {
            case 1:
                old_mode = MOCO;
                break;
            case 2:
                old_mode = LOCO;
                break;
            case 3:
                old_mode = EXTAL;
                break;
            case 4:
                old_mode = SOSC;
                break;
            default:
                old_mode = HOCO;
                break;
        }
    /* Only switch if the current clock source and the
     * specified clock source are different.
     */
    if (mode != old_mode)
    {
        switch (mode)
        {
            case HOCO:
                if (1U == R_SYSC->HOCOCR_b.HCSTP)
                {
                    /* Error if the high-speed on-chip oscillator is stopped. */
                    status = BSP_ERROR1;
                }
                else
                {
                    R_SYSC->SCKSCR = 0x00U;
                }
                break;
            case MOCO:
                if (1U == R_SYSC->MOCOCR_b.MCSTP)
                {
                    /* Error if the middle-speed on-chip oscillator is stopped. */
                    status = BSP_ERROR1;
                }
                else
                {
                    R_SYSC->SCKSCR = 0x01U;
                }
                break;
            case LOCO:
                if (1U == R_SYSC->LOCOCR_b.LCSTP)
                {
                    /* Error if the low-speed on-chip oscillator is stopped. */
                    status = BSP_ERROR1;
                }
                else
                {
                    R_SYSC->SCKSCR = 0x02U;
                }
                break;
            case EXTAL:
                if (1U == R_SYSC->MOSCCR_b.MOSTP)
                {
                    /* Error if the external clock input is stopped. */
                    status = BSP_ERROR1;
                }
                else
                {
                    R_SYSC->SCKSCR = 0x03U;
                }
                break;
            case SOSC:
                if (1U == R_SYSC->SOSCCR_b.SOSTP)
                {
                    /* Error if the sub-clock oscillator is stopped. */
                    status = BSP_ERROR1;
                }
                else
                {
                    R_SYSC->SCKSCR = 0x04U;
                }
                break;
            default:
                status = BSP_ARG_ERROR;
                break;
        }
    }
    return status;
}
#endif /* BSP_CFG_CHANGE_CLOCK_SETTING_API_FUNCTIONS == 0 */

/***********************************************************************************************************************
 * Function name: change_iclk_clock_setting
 * Description  : Change the ICLK clock value by changing its clock source and division.
 *                This function is also used to change PCLKB clock value.
 * Arguments    : mode - Clock to switch.
 *                iclkdiv - ICLK frequency divider
 *                pclkdiv - PCLKB frequency divider
 * Return value : BSP_OK when changing setting is done.
 *                BSP_ERROR1 The specified clock is not oscillating.
 *                BSP_ERROR3 An unsupported state transition was specified. Refer to the user's manual.
 *                BSP_ARG_ERROR An invalid argument was input.
 * Attention    : Start the clock to switch to before calling this function.
***********************************************************************************************************************/
#if BSP_CFG_CHANGE_CLOCK_SETTING_API_FUNCTIONS == 0
e_bsp_err_t change_iclk_clock_setting(e_clock_mode_t mode, e_clock_div_t iclkdiv, e_clock_div_t pclkdiv)
{
    e_bsp_err_t status = BSP_OK;

#if BSP_CFG_PARAM_CHECKING_ENABLE
    if (iclkdiv > 6U || pclkdiv > 6U || iclkdiv > pclkdiv)
    {
        return BSP_ERROR3;
    }
#if BSP_PRV_CLOCK_SUPPLY_TYPE_B
    if (iclkdiv != pclkdiv)
    {
        return BSP_ERROR3;
    }
#endif
#endif

    /* Adjust the MCU specific wait state right before the system clock is set, 
       if the system clock frequency to be set is higher than before. */
    uint32_t clock_freq_hz_post_change = (uint32_t)(get_clock_source_freq(mode) / iclkdiv);
    bsp_clock_set_prechange(clock_freq_hz_post_change);

    /* Switching to a faster source clock. */
    if (get_clock_source_freq(mode) >= get_clock_source_freq((e_clock_mode_t)R_SYSC->SCKSCR))
    {
        /* Set the clock dividers before switching to the new clock source. */
        R_SYSC->SCKDIVCR = (uint32_t)(((iclkdiv & 0xFU) << 24U) | ((pclkdiv & 0xFU) << 8U) | BSP_PRV_SCKDIVCR_DEFAULT);
        /* Switch to the new clock source. */
        status = change_iclk_clock_source(mode);
    }
    /* Switching to a slower source clock. */
    else
    {
        status = change_iclk_clock_source(mode);
        /* Set the clock dividers after switching to the new clock source. */
        R_SYSC->SCKDIVCR = (uint32_t)(((iclkdiv & 0xFU) << 24U) | ((pclkdiv & 0xFU) << 8U) | BSP_PRV_SCKDIVCR_DEFAULT);
    }

    /* Adjust the MCU specific wait state soon after the system clock is set, if the system clock frequency to be
       set is lower than previous. */
    bsp_clock_set_postchange(clock_freq_hz_post_change);
    return status;
}
#endif

/***********************************************************************************************************************
 * Function name: bsp_clock_set_prechange
 * Description  : Set MEMWAIT and FLDWAITR register before changing ICLK clock > 32MHz
 * Arguments    : The requested ICLK clock value
 * Return value : None
***********************************************************************************************************************/
#if BSP_CFG_CHANGE_CLOCK_SETTING_API_FUNCTIONS == 0
static void bsp_clock_set_prechange(uint32_t requested_freq_hz)
{
#if BSP_PRV_CLOCK_SUPPLY_TYPE_B
    BSP_UNUSED_PARAMETER(requested_freq_hz);
#else
    if (requested_freq_hz > BSP_PRV_MEMWAIT_MAX_ZERO_WAIT_FREQ)
    {
        /* The MCU must be in high speed mode to set wait states to 2. The MCU should already be in high speed mode as
           a precondition. */
        R_SYSC->MEMWAIT = (uint8_t)BSP_PRV_MEMWAIT_WAIT;
    }
    if (requested_freq_hz > BSP_PRV_FLDWAITR_MAX_ONE_WAIT_FREQ)
    {
        /* The MCU must be in high speed mode to set wait states to 2. The MCU should already be in high speed mode as
           a precondition. */
        R_FLCN->FLDWAITR = (uint8_t)BSP_PRV_FLDWAITR_TWO_WAIT_CYCLES;
    }
#endif
}
#endif
/***********************************************************************************************************************
 * Function name: bsp_clock_set_postchange
 * Description  : Set MEMWAIT and FLDWAITR register after changing ICLK clock <= 32MHz from ICLK clock > 32MHz
 * Arguments    : The requested ICLK clock value
 * Return value : None
***********************************************************************************************************************/
#if BSP_CFG_CHANGE_CLOCK_SETTING_API_FUNCTIONS == 0
static void bsp_clock_set_postchange(uint32_t requested_freq_hz)
{
#if BSP_PRV_CLOCK_SUPPLY_TYPE_B
    BSP_UNUSED_PARAMETER(requested_freq_hz);
#else
    if (requested_freq_hz <= BSP_PRV_MEMWAIT_MAX_ZERO_WAIT_FREQ)
    {
        R_SYSC->MEMWAIT = (uint8_t)BSP_PRV_MEMWAIT_NO_WAIT;
    }
    if (requested_freq_hz <= BSP_PRV_FLDWAITR_MAX_ONE_WAIT_FREQ)
    {
        R_FLCN->FLDWAITR = (uint8_t)BSP_PRV_FLDWAITR_ONE_WAIT_CYCLES;
    }
#endif
}
#endif

/***********************************************************************************************************************
 * Function name: set_operating_mode_oppcr
 * Description  : Set the operating mode in the OPPCR register
 * Arguments    : The operating mode
 * Return value : None
***********************************************************************************************************************/
void set_operating_mode_oppcr(uint8_t operating_mode)
{
    /* If the desired operating mode is already set, return. */
    if (operating_mode == R_SYSC->OPCCR)
    {
        return;
    }

    /* On some MCUs, the HOCO must be stable before updating OPCCR.OPCM. */
    if (0U == R_SYSC->HOCOCR)
    {
        /* Wait for HOCO to stabilize. */
        /* WAIT_LOOP */
        BSP_HARDWARE_REGISTER_WAIT(R_SYSC->OSCSF_b.HOCOSF, 1U);
    }

    /* Wait for transition to complete. */
    /* WAIT_LOOP */
    BSP_HARDWARE_REGISTER_WAIT(R_SYSC->OPCCR_b.OPCMTSF, 0U);

    /* Apply requested operating speed mode. */
    R_SYSC->OPCCR = operating_mode;

    /* Wait for transition to complete. */
    /* WAIT_LOOP */
    BSP_HARDWARE_REGISTER_WAIT(R_SYSC->OPCCR_b.OPCMTSF, 0U);
}
/***********************************************************************************************************************
 * Function name: set_operating_mode
 * Description  : Set the operating mode according to setting of user.
 * Arguments    : The operating mode
 * Return value : None
***********************************************************************************************************************/
void set_operating_mode(uint8_t operating_mode)
{
    if (BSP_PRV_OPERATING_MODE_SUBOSC_SPEED == operating_mode)
    {
        /* Wait for transition to complete. */
        /* WAIT_LOOP */
        BSP_HARDWARE_REGISTER_WAIT(R_SYSC->SOPCCR_b.SOPCMTSF, 0U);

        /* Set subosc speed mode. */
        R_SYSC->SOPCCR = 0x1U;

        /* Wait for transition to complete. */
        /* WAIT_LOOP */
        BSP_HARDWARE_REGISTER_WAIT(R_SYSC->SOPCCR_b.SOPCMTSF, 0U);
    }
    else
    {
        if (BSP_PRV_OPERATING_MODE_SUBOSC_SPEED == R_SYSC->SOPCCR_b.SOPCM)
        {
            /* Wait for transition to complete. */
            /* WAIT_LOOP */
            BSP_HARDWARE_REGISTER_WAIT(R_SYSC->SOPCCR_b.SOPCMTSF, 0U);

            /* Exit subosc speed mode first. */
            R_SYSC->SOPCCR = 0U;

            /* Wait for transition to complete.
             * Check the entire register here since it should be set to 0 at this point.
             * Checking the entire register is slightly more efficient. This will also hang the program if the LPM
             * registers are not unlocked, which can help catch programming errors. */
            /* WAIT_LOOP */
            BSP_HARDWARE_REGISTER_WAIT(R_SYSC->SOPCCR, 0U);
        }
        set_operating_mode_oppcr(operating_mode);
    }

}
