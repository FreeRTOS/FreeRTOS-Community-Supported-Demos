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
* File Name    : mcu_mapped_interrupts.h
* H/W Platform : GENERIC_R9A02G021
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 20.01.2024 1.00     First Release
*         : 10.06.2024 1.20     Change the macro name endwith "DISABLE" to "FUNCTIONS"
                                Change macro name ICU_EVENT_RTC_ALM to ICU_EVENT_RTC_ALM_OR_PRD
***********************************************************************************************************************/
#ifndef MCU_MAPPED_INTERRUPTS_H
#define MCU_MAPPED_INTERRUPTS_H
 
#define ICU_EVENT_PORT_IRQ0              (0x01)  /* group0 (IELSR0/8/16/24) or group4 (IELSR4/12/20/28) */
#define ICU_EVENT_PORT_IRQ1              (0x01)  /* group1 (IELSR1/9/17/25) or group5 (IELSR5/13/21/29) */
#define ICU_EVENT_PORT_IRQ2              (0x01)  /* group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30) */
#define ICU_EVENT_PORT_IRQ3              (0x01)  /* group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31) */
#define ICU_EVENT_PORT_IRQ4              (0x16)  /* group4 (IELSR4/12/20/28) */
#define ICU_EVENT_PORT_IRQ5              (0x13)  /* group5 (IELSR5/13/21/29) */
#define ICU_EVENT_PORT_IRQ6              (0x13)  /* group6 (IELSR6/14/22/30) */
#define ICU_EVENT_PORT_IRQ7              (0x11)  /* group7 (IELSR7/15/23/31) */
#define ICU_EVENT_DTC_COMPLETE           (0x02)  /* group0 (IELSR0/8/16/24) or group4 (IELSR4/12/20/28)  */
#define ICU_EVENT_ICU_SNZCANCEL          (0x04)  /* group7 (IELSR7/15/23/31) */
#define ICU_EVENT_FCU_FRDYI              (0x02)  /* group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30) */
#define ICU_EVENT_LVD_LVD1               (0x04)  /* group0 (IELSR0/8/16/24) or group4 (IELSR4/12/20/28) */
#define ICU_EVENT_LVD_LVD2               (0x04)  /* group1 (IELSR1/9/17/25) or group5 (IELSR5/13/21/29) */
#define ICU_EVENT_SYSTEM_SNZREQ          (0x05)  /* group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30) */
#define ICU_EVENT_IWDT_NMIUNDF           (0x03)  /* group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31) */
#define ICU_EVENT_WDT_NMIUNDF            (0x06)  /* group0 (IELSR0/8/16/24) or group4 (IELSR4/12/20/28) */
#define ICU_EVENT_RTC_ALM_OR_PRD         (0x05)  /* group1 (IELSR1/9/17/25) or group5 (IELSR5/13/21/29) */
#define ICU_EVENT_IIC0_ENDI_IIC0_WUI     (0x0b)  /* group0 (IELSR0/8/16/24) */
#define ICU_EVENT_IIC1_ENDI_IIC1_WUI     (0x0b)  /* group1 (IELSR1/9/17/25) */
#define ICU_EVENT_KEY_INTKR              (0x0c)  /* group3 (IELSR3/11/19/27) or group7 (IELSR7/15/23/31) */
#define ICU_EVENT_CAC_FEERI              (0x10)  /* group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30) */
#define ICU_EVENT_CAC_MENDI              (0x10)  /* group4 (IELSR4/12/20/28) */
#define ICU_EVENT_CAC_OVFI               (0x10)  /* group4 (IELSR4/12/20/28) */
#define ICU_EVENT_IOPORT_GROUP1          (0x11)  /* group2 (IELSR2/10/18/26) */
#define ICU_EVENT_IOPORT_GROUP2          (0x11)  /* group6 (IELSR6/14/22/30) */
#define ICU_EVENT_TRNG_RD_REQ            (0x0e)  /* group0 (IELSR0/8/16/24) */
#define ICU_EVENT_ELC_SWEVT0             (0x0d)  /* group1 (IELSR1/9/17/25) */
#define ICU_EVENT_ELC_SWEVT1             (0x0c)  /* group5 (IELSR5/13/21/29) */
#define ICU_EVENT_SAU0_ENDI0_0           (0x12)  /* group0 (IELSR0/8/16/24) */
#define ICU_EVENT_SAU0_ENDI0_4           (0x1e)  /* group4 (IELSR4/12/20/28) */
#define ICU_EVENT_SAU0_ENDI1_1           (0x12)  /* group1 (IELSR1/9/17/25) */
#define ICU_EVENT_SAU0_ENDI1_5           (0x1e)  /* group5 (IELSR5/13/21/29) */
#define ICU_EVENT_SAU0_ENDI2             (0x12)  /* group2 (IELSR2/10/18/26) */
#define ICU_EVENT_SAU0_ENDI3             (0x12)  /* group3 (IELSR3/11/19/27) */
#define ICU_EVENT_SAU1_ENDI0             (0x12)  /* group4 (IELSR4/12/20/28) */
#define ICU_EVENT_SAU1_ENDI1             (0x12)  /* group5 (IELSR5/13/21/29) */
#define ICU_EVENT_SAU0_INTSRE0           (0x14)  /* group1 (IELSR1/ 9/17/25) */
#define ICU_EVENT_SAU0_INTSRE1           (0x14)  /* group3 (IELSR3/11/19/27) */
#define ICU_EVENT_SAU1_INTSRE2           (0x14)  /* group5 (IELSR5/13/21/29) */
#define ICU_EVENT_TAU0_ENDI0             (0x16)  /* group0 (IELSR0/8/16/24) */
#define ICU_EVENT_TAU0_ENDI1             (0x16)  /* group1 (IELSR1/ 9/17/25) */
#define ICU_EVENT_TAU0_ENDI2             (0x16)  /* group2 (IELSR2/10/18/26) */
#define ICU_EVENT_TAU0_ENDI3             (0x16)  /* group3 (IELSR3/11/19/27) */
#define ICU_EVENT_TAU0_ENDI4             (0x15)  /* group4 (IELSR4/12/20/28) */
#define ICU_EVENT_TAU0_ENDI5             (0x15)  /* group5 (IELSR5/13/21/29) */
#define ICU_EVENT_TAU0_ENDI6             (0x15)  /* group6 (IELSR6/14/22/30) */
#define ICU_EVENT_TAU0_ENDI7             (0x15)  /* group7 (IELSR7/15/23/31) */
#define ICU_EVENT_TAU0_MODE8_ENDI1       (0x17)  /* group2 (IELSR2/10/18/26) */
#define ICU_EVENT_TAU0_MODE8_ENDI3       (0x17)  /* group3 (IELSR3/11/19/27) */
#define ICU_EVENT_TML32_OUTI_0           (0x19)  /* group0 (IELSR0/8/16/24) */
#define ICU_EVENT_TML32_OUTI_4           (0x1F)  /* group4 (IELSR4/12/20/28) */
#define ICU_EVENT_REMC_OUTI              (0x19)  /* group2 (IELSR2/10/18/26) or group6 (IELSR6/14/22/30) */
#define ICU_EVENT_UARTA_TX_ENDI0         (0x1c)  /* group0 (IELSR0/8/16/24) */
#define ICU_EVENT_UARTA_RX_ENDI0         (0x1c)  /* group1 (IELSR1/ 9/17/25) */
#define ICU_EVENT_UARTA_RX_ERI0          (0x1c)  /* group2 (IELSR2/10/18/26) */
#define ICU_EVENT_UARTA_TX_ENDI1         (0x1b)  /* group4 (IELSR4/12/20/28) */
#define ICU_EVENT_UARTA_RX_ENDI1         (0x1b)  /* group5 (IELSR5/13/21/29) */
#define ICU_EVENT_UARTA_RX_ERI1          (0x1b)  /* group6 (IELSR6/14/22/30) */
#define ICU_EVENT_COMP_DET0              (0x1d)  /* group0 (IELSR0/8/16/24) */
#define ICU_EVENT_COMP_DET1              (0x1d)  /* group1 (IELSR1/ 9/17/25) */
#define ICU_EVENT_ADC_ENDI_3             (0x1e)  /* group3 (IELSR3/11/19/27) */
#define ICU_EVENT_ADC_ENDI_7             (0x1f)  /* group7 (IELSR7/15/23/31) */
#define ICU_EVENT_DOC_DOPCI              (0x1f)  /* group3 (IELSR3/11/19/27) */

#if BSP_CFG_INTERRUPT_SETTING_API_FUNCTIONS == 0
void bsp_mapped_interrupt_open (void);
#endif
#endif
