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
* File Name    : r_bsp_common.h
* Description  : Implements functions that apply to all r_bsp boards and MCUs.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 20.01.2024 1.00     First Release
          : 29.03.2024 1.10     Add #include <stdlib.h> for Segger
                                Change the Smart Configurator version which can be used with BSP v1.10 to 101
*         : 10.06.2024 1.20     Change the macro name endwith "DISABLE" to "FUNCTIONS"
***********************************************************************************************************************/

/*************************************************
 * Includes  <System Includes> , "Project Includes"
 *************************************************/
#if defined(__SEGGER_CC__)
#include    <stdlib.h>
#endif
#include    <stdint.h>
#include    <stdbool.h>
#include    <stdio.h>
#include    <stddef.h>
#include    "r_bsp_config.h"

/* Multiple inclusion prevention macro */
#ifndef R_BSP_COMMON_H
#define R_BSP_COMMON_H

#if BSP_CFG_CONFIGURATOR_VERSION < 1010
#error "Make sure that the value of BSP_CFG_CONFIGURATOR_VERSION defined in r_config/r_bsp_config.h matches the version of Smart Configurator you are using. If they do not match, change the settings. If they match, you need to upgrade your Smart Configurator. Please upgrade Smart Configurator."
#endif

/*************************************************
 * Macro definitions
 *************************************************/
/* Version Number of r_bsp. */
#define R_BSP_VERSION_MAJOR           (1U)
#define R_BSP_VERSION_MINOR           (10U)

/* Function-like macro used to wait for a condition to be met, most often used to wait for hardware register updates.
 * This macro can be redefined to add a timeout if necessary. */
#ifndef BSP_HARDWARE_REGISTER_WAIT
 #define BSP_HARDWARE_REGISTER_WAIT(reg, required_value)    while (reg != required_value) { /* Wait. */}
#endif

#define BSP_UNUSED_PARAMETER(x)    ((void)x)
/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum
{
   HOCO,    // High-speed on-chip oscillator
   MOCO,    // Middle-speed on-chip oscillator
   LOCO,    // Low-speed on-chip oscillator
   EXTAL,   // External clock
   SOSC,    // Subsystem clock
} e_clock_mode_t;

typedef enum
{
   DIV_BY_1,
   DIV_BY_2,
   DIV_BY_4,
   DIV_BY_8,
   DIV_BY_16,
   DIV_BY_32,
   DIV_BY_64,
   DIV_BY_128,
} e_clock_div_t;

/* Error identification */
typedef enum
{
   BSP_OK,
   BSP_ARG_ERROR,
   BSP_ERROR1,
   BSP_ERROR2,
   BSP_ERROR3
} e_bsp_err_t;

/* Available delay units. */
typedef enum
{
   BSP_DELAY_SECS = 1U,              /* Requested delay amount is in seconds. */
   BSP_DELAY_MILLISECS = 1000U,      /* Requested delay amount is in milliseconds. */
   BSP_DELAY_MICROSECS = 1000000U    /* Requested delay amount is in microseconds. */
} e_bsp_delay_units_t;

/* The different types of registers that can be protected. */
typedef enum
{
   /* PRC0
      Enables writing to the registers related to the clock generation circuit: SCKDIVCR, SCKSCR, HOCOCR, MOCOCR, 
      CKOCR, HOCOUTCR, LOCOCR, LPOPT, OSMCR, MOSCCR, SOSCCR, SOMCR, SOMRG, MEMWAIT, LOCOUTCR, MOCOUTCR */
   BSP_REG_PROTECT_CGC = 0,

   /* PRC1
      Enables writing to the registers related to low power mode: SBYCR, OPCCR, SYOCDCR, PSMCR, SNZCR, SNZEDCR0, 
      SNZEDCR1, SNZREQCR0, SOPCCR, SYOCDCR, PSMCR */
   BSP_REG_PROTECT_LPM,

   /* PRC3
      Enables writing to the registers related to the LVD: LVD1CR1, LVD1SR, LVD2CR1, LVD2SR, LVCMPCR, LVDLVLR, 
      LVD1CR0, LVD2CR0 */
   BSP_REG_PROTECT_LVD,

   /* SRAM.SRAMPRCR
      Enables writing to the PARIOAD register.  */
   BSP_REG_PROTECT_SRAM,
    
   /* SRAM.ECCPRCR
      Enables writing to the ECCMODE, ECC1STSEN, and ECCOAD registers.  */
   BSP_REG_PROTECT_ECC,

   /* SRAM.ECCPRCR2
      Enables writing to the ECCETST register.  */
   BSP_REG_PROTECT_ECC2,
   
   /* PWPR
      Enable write to the PmnPFS register */
   BSP_REG_PROTECT_PMNPFS,

   /* This entry is used for getting the number of enum items. This must be the last entry. DO NOT REMOVE THIS ENTRY!*/
   BSP_REG_PROTECT_TOTAL_ITEMS
} e_bsp_reg_protect_t;

/*************************************************
 * Function declaration
 *************************************************/
#if BSP_CFG_CLOCK_OPERATION_API_FUNCTIONS == 0
e_bsp_err_t R_BSP_StartClock (e_clock_mode_t mode);
e_bsp_err_t R_BSP_StopClock (e_clock_mode_t mode);
#endif
uint32_t R_BSP_GetIClkFreqHz (void);
void R_BSP_DelayCycle (uint32_t wait_cycle);
e_bsp_err_t R_BSP_SoftwareDelay (uint32_t delay, e_bsp_delay_units_t units);
#if BSP_CFG_CHANGE_CLOCK_SETTING_API_FUNCTIONS == 0
e_bsp_err_t R_BSP_ChangeICLKClockSetting (e_clock_mode_t mode, e_clock_div_t iclkdiv, e_clock_div_t pclkdiv);
#endif
uint32_t R_BSP_GetVersion (void);
void R_BSP_RegisterProtectEnable (e_bsp_reg_protect_t regs_to_protect);
void R_BSP_RegisterProtectDisable (e_bsp_reg_protect_t regs_to_unprotect);
void bsp_register_protect_open (void);

/* End of multiple inclusion prevention macro */


#endif /* #define R_BSP_COMMON_H */