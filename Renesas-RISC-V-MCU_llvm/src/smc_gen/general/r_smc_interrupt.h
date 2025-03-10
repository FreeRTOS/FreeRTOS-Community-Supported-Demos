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
* File Name        : r_smc_interrupt.h
* Version          : 1.0.30
* Device(s)        : R9A02G0214CNE
* Description      : This file implements interrupt priority setting.
* Creation Date    : 
***********************************************************************************************************************/


#ifndef SMC_INTC_H
#define SMC_INTC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* The macro definitions below list the full set of priority levels as selected in the Interrupts tab
 * Please do not modify this file manually
 */
#define ICU_PORT_PORT_IRQ0_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_DTC_DTC_COMPLETE_PRIORITY            (_0F_INT_PRIORITY_15)
#define ICU_LVD_LVD_LVD1_PRIORITY                (_0F_INT_PRIORITY_15)
#define ICU_WDT_WDT_NMIUNDF_PRIORITY             (_0F_INT_PRIORITY_15)
#define ICU_IICA_IIC0_ENDI_IIC0_WUI_PRIORITY     (_0F_INT_PRIORITY_15)
#define ICU_TRNG_TRNG_RD_REQ_PRIORITY            (_0F_INT_PRIORITY_15)
#define ICU_SAU0_SAU0_ENDI0_PRIORITY             (_FF_INT_PRIORITY_0)
#define ICU_TAU0_TAU0_ENDI0_PRIORITY             (_0F_INT_PRIORITY_15)
#define ICU_TML32_TML32_OUTI_PRIORITY            (_0F_INT_PRIORITY_15)
#define ICU_UARTA_UARTA_TX_ENDI0_PRIORITY        (_0F_INT_PRIORITY_15)
#define ICU_COMP_COMP_DET0_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_PORT_PORT_IRQ1_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_LVD_LVD_LVD2_PRIORITY                (_0F_INT_PRIORITY_15)
#define ICU_RTC_RTC_ALM_PRIORITY                 (_0F_INT_PRIORITY_15)
#define ICU_IICA_IIC1_ENDI_IIC1_WUI_PRIORITY     (_0F_INT_PRIORITY_15)
#define ICU_ELC_ELC_SWEVT0_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_SAU0_SAU0_ENDI1_PRIORITY             (_EF_INT_PRIORITY_1)
#define ICU_SAU0_SAU0_INTSRE0_PRIORITY           (_EF_INT_PRIORITY_1)
#define ICU_TAU0_TAU0_ENDI1_PRIORITY             (_0F_INT_PRIORITY_15)
#define ICU_UARTA_UARTA_RX_ENDI0_PRIORITY        (_0F_INT_PRIORITY_15)
#define ICU_COMP_COMP_DET1_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_PORT_PORT_IRQ2_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_FLASH_FCU_FRDYI_PRIORITY             (_0F_INT_PRIORITY_15)
#define ICU_LowPowerMode_SYSTEM_SNZREQ_PRIORITY  (_0F_INT_PRIORITY_15)
#define ICU_CAC_CAC_FEERI_PRIORITY               (_0F_INT_PRIORITY_15)
#define ICU_I_OPort_IOPORT_GROUP1_PRIORITY       (_0F_INT_PRIORITY_15)
#define ICU_SAU0_SAU0_ENDI2_PRIORITY             (_0F_INT_PRIORITY_15)
#define ICU_TAU0_TAU0_ENDI2_PRIORITY             (_0F_INT_PRIORITY_15)
#define ICU_TAU0_TAU0_MODE8_ENDI1_PRIORITY       (_0F_INT_PRIORITY_15)
#define ICU_REMC_REMC_OUTI_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_UARTA_UARTA_RX_ERI0_PRIORITY         (_0F_INT_PRIORITY_15)
#define ICU_PORT_PORT_IRQ3_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_IWDT_IWDT_NMIUNDF_PRIORITY           (_0F_INT_PRIORITY_15)
#define ICU_KINT_KEY_INTKR_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_CAC_CAC_MENDI_PRIORITY               (_0F_INT_PRIORITY_15)
#define ICU_SAU0_SAU0_ENDI3_PRIORITY             (_0F_INT_PRIORITY_15)
#define ICU_SAU0_SAU0_INTSRE1_PRIORITY           (_0F_INT_PRIORITY_15)
#define ICU_TAU0_TAU0_ENDI3_PRIORITY             (_0F_INT_PRIORITY_15)
#define ICU_TAU0_TAU0_MODE8_ENDI3_PRIORITY       (_0F_INT_PRIORITY_15)
#define ICU_ADC12_ADC_ENDI_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_DOC_DOC_DOPCI_PRIORITY               (_0F_INT_PRIORITY_15)
#define ICU_PORT_PORT_IRQ4_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_CAC_CAC_OVFI_PRIORITY                (_0F_INT_PRIORITY_15)
#define ICU_SAU1_SAU1_ENDI0_PRIORITY             (_0F_INT_PRIORITY_15)
#define ICU_TAU0_TAU0_ENDI4_PRIORITY             (_0F_INT_PRIORITY_15)
#define ICU_UARTA_UARTA_TX_ENDI1_PRIORITY        (_0F_INT_PRIORITY_15)
#define ICU_PORT_PORT_IRQ5_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_ELC_ELC_SWEVT1_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_SAU1_SAU1_ENDI1_PRIORITY             (_0F_INT_PRIORITY_15)
#define ICU_SAU1_SAU1_INTSRE2_PRIORITY           (_0F_INT_PRIORITY_15)
#define ICU_TAU0_TAU0_ENDI5_PRIORITY             (_0F_INT_PRIORITY_15)
#define ICU_UARTA_UARTA_RX_ENDI1_PRIORITY        (_0F_INT_PRIORITY_15)
#define ICU_PORT_PORT_IRQ6_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_I_OPort_IOPORT_GROUP2_PRIORITY       (_0F_INT_PRIORITY_15)
#define ICU_TAU0_TAU0_ENDI6_PRIORITY             (_0F_INT_PRIORITY_15)
#define ICU_UARTA_UARTA_RX_ERI1_PRIORITY         (_0F_INT_PRIORITY_15)
#define ICU_PORT_PORT_IRQ7_PRIORITY              (_0F_INT_PRIORITY_15)
#define ICU_ICU_ICU_SNZCANCEL_PRIORITY           (_0F_INT_PRIORITY_15)
#define ICU_TAU0_TAU0_ENDI7_PRIORITY             (_0F_INT_PRIORITY_15)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_Interrupt_Create (void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif

