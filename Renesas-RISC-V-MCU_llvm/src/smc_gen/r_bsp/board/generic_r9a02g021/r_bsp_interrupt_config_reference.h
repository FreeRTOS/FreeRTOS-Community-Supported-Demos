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
* File Name    : r_bsp_interrupt_config_reference.h
* H/W Platform : GENERIC_R9A02G021
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 20.01.2024 1.00     First Release
***********************************************************************************************************************/

#ifndef R_BSP_INTERUPT_CONFIG_REF_HEADER_FILE
#define R_BSP_INTERUPT_CONFIG_REF_HEADER_FILE

#define BSP_CFG_PORT_IRQ0_VECT              -1
#define BSP_CFG_PORT_IRQ1_VECT              -1
#define BSP_CFG_PORT_IRQ2_VECT              14
#define BSP_CFG_PORT_IRQ3_VECT              -1
#define BSP_CFG_PORT_IRQ4_VECT              -1
#define BSP_CFG_PORT_IRQ5_VECT              -1
#define BSP_CFG_PORT_IRQ6_VECT              -1
#define BSP_CFG_PORT_IRQ7_VECT              -1
#define BSP_CFG_DTC_COMPLETE_VECT           12
#define BSP_CFG_ICU_SNZCANCEL_VECT          -1
#define BSP_CFG_FCU_FRDYI_VECT              -1
#define BSP_CFG_LVD_LVD1_VECT               -1
#define BSP_CFG_LVD_LVD2_VECT               -1
#define BSP_CFG_SYSTEM_SNZREQ_VECT          -1
#define BSP_CFG_IWDT_NMIUNDF_VECT           31
#define BSP_CFG_WDT_NMIUNDF_VECT            16
#define BSP_CFG_RTC_ALM_OR_PRD_VECT         -1
#define BSP_CFG_IIC0_ENDI_IIC0_WUI_VECT     -1
#define BSP_CFG_IIC1_ENDI_IIC1_WUI_VECT     -1
#define BSP_CFG_KEY_INTKR_VECT              23
#define BSP_CFG_CAC_FEERI_VECT              -1
#define BSP_CFG_CAC_MENDI_VECT              -1
#define BSP_CFG_CAC_OVFI_VECT               -1
#define BSP_CFG_IOPORT_GROUP1_VECT          -1
#define BSP_CFG_IOPORT_GROUP2_VECT          -1
#define BSP_CFG_TRNG_RD_REQ_VECT            -1
#define BSP_CFG_ELC_SWEVT0_VECT             -1
#define BSP_CFG_ELC_SWEVT1_VECT             -1
#define BSP_CFG_SAU0_ENDI0_VECT             8
#define BSP_CFG_SAU0_ENDI1_VECT             9
#define BSP_CFG_SAU0_ENDI2_VECT             18
#define BSP_CFG_SAU0_ENDI3_VECT             19
#define BSP_CFG_SAU1_ENDI0_VECT             -1
#define BSP_CFG_SAU1_ENDI1_VECT             13
#define BSP_CFG_SAU0_INTSRE0_VECT           17
#define BSP_CFG_SAU0_INTSRE1_VECT           27
#define BSP_CFG_SAU1_INTSRE2_VECT           21
#define BSP_CFG_TAU0_ENDI0_VECT             0
#define BSP_CFG_TAU0_ENDI1_VECT             1
#define BSP_CFG_TAU0_ENDI2_VECT             2
#define BSP_CFG_TAU0_ENDI3_VECT             3
#define BSP_CFG_TAU0_ENDI4_VECT             4
#define BSP_CFG_TAU0_ENDI5_VECT             5
#define BSP_CFG_TAU0_ENDI6_VECT             6
#define BSP_CFG_TAU0_ENDI7_VECT             7
#define BSP_CFG_TAU0_MODE8_ENDI1_VECT       10
#define BSP_CFG_TAU0_MODE8_ENDI3_VECT       11
#define BSP_CFG_TML32_OUTI_VECT             20
#define BSP_CFG_REMC_OUTI_VECT              22
#define BSP_CFG_UARTA_TX_ENDI0_VECT         24
#define BSP_CFG_UARTA_RX_ENDI0_VECT         25
#define BSP_CFG_UARTA_RX_ERI0_VECT          26
#define BSP_CFG_UARTA_TX_ENDI1_VECT         28
#define BSP_CFG_UARTA_RX_ENDI1_VECT         29
#define BSP_CFG_UARTA_RX_ERI1_VECT          30
#define BSP_CFG_COMP_DET0_VECT              -1
#define BSP_CFG_COMP_DET1_VECT              -1
#define BSP_CFG_ADC_ENDI_VECT               15
#define BSP_CFG_DOC_DOPCI_VECT              -1

#endif
