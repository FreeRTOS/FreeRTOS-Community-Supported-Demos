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
* File Name    : mcu_mapped_interrupts.c
* H/W Platform : GENERIC_R9A02G021
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 20.01.2024 1.00     First Release
*         : 10.06.2024 1.20     Change macro name BSP_CFG_RTC_ALM_VECT to BSP_CFG_RTC_ALM_OR_PRD_VECT
                                Change the macro name endwith "DISABLE" to "FUNCTIONS"
***********************************************************************************************************************/
/*************************************************
 * Includes  <System Includes> , "Project Includes"
 *************************************************/
#include "platform.h"  
#include "mcu_mapped_interrupts_private.h"
#include "r_bsp_interrupt_config.h"

/*************************************************
 * Function definition
 *************************************************/
#if BSP_CFG_INTERRUPT_SETTING_API_FUNCTIONS == 0
void bsp_mapped_interrupt_open(void)  
{  
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_PORT_IRQ0_VECT)
        IELSR_reg(BSP_CFG_PORT_IRQ0_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_PORT_IRQ0_VECT) |= ICU_EVENT_PORT_IRQ0;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_PORT_IRQ1_VECT)
        IELSR_reg(BSP_CFG_PORT_IRQ1_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_PORT_IRQ1_VECT) |= ICU_EVENT_PORT_IRQ1;
    #endif
    
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_PORT_IRQ2_VECT)
        IELSR_reg(BSP_CFG_PORT_IRQ2_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_PORT_IRQ2_VECT) |= ICU_EVENT_PORT_IRQ2;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_PORT_IRQ3_VECT)
        IELSR_reg(BSP_CFG_PORT_IRQ3_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_PORT_IRQ3_VECT) |= ICU_EVENT_PORT_IRQ3;
    #endif

    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_PORT_IRQ4_VECT)
        IELSR_reg(BSP_CFG_PORT_IRQ4_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_PORT_IRQ4_VECT) |= ICU_EVENT_PORT_IRQ4;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_PORT_IRQ5_VECT)
        IELSR_reg(BSP_CFG_PORT_IRQ5_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_PORT_IRQ5_VECT) |= ICU_EVENT_PORT_IRQ5;
    #endif

    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_PORT_IRQ6_VECT)
        IELSR_reg(BSP_CFG_PORT_IRQ6_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_PORT_IRQ6_VECT) |= ICU_EVENT_PORT_IRQ6;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_PORT_IRQ7_VECT)
        IELSR_reg(BSP_CFG_PORT_IRQ7_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_PORT_IRQ7_VECT) |= ICU_EVENT_PORT_IRQ7;
    #endif

    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_DTC_COMPLETE_VECT)
        IELSR_reg(BSP_CFG_DTC_COMPLETE_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_DTC_COMPLETE_VECT) |= ICU_EVENT_DTC_COMPLETE;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_ICU_SNZCANCEL_VECT)
        IELSR_reg(BSP_CFG_ICU_SNZCANCEL_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_ICU_SNZCANCEL_VECT) |= ICU_EVENT_ICU_SNZCANCEL;
    #endif

    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_FCU_FRDYI_VECT)
        IELSR_reg(BSP_CFG_FCU_FRDYI_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_FCU_FRDYI_VECT) |= ICU_EVENT_FCU_FRDYI;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_LVD_LVD1_VECT)
        IELSR_reg(BSP_CFG_LVD_LVD1_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_LVD_LVD1_VECT) |= ICU_EVENT_LVD_LVD1;
    #endif

    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_LVD_LVD2_VECT)
        IELSR_reg(BSP_CFG_LVD_LVD2_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_LVD_LVD2_VECT) |= ICU_EVENT_LVD_LVD2;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_SYSTEM_SNZREQ_VECT)
        IELSR_reg(BSP_CFG_SYSTEM_SNZREQ_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_SYSTEM_SNZREQ_VECT) |= ICU_EVENT_SYSTEM_SNZREQ;
    #endif

    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_IWDT_NMIUNDF_VECT)
        IELSR_reg(BSP_CFG_IWDT_NMIUNDF_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_IWDT_NMIUNDF_VECT) |= ICU_EVENT_IWDT_NMIUNDF;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_WDT_NMIUNDF_VECT)
        IELSR_reg(BSP_CFG_WDT_NMIUNDF_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_WDT_NMIUNDF_VECT) |= ICU_EVENT_WDT_NMIUNDF;
    #endif

    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_RTC_ALM_OR_PRD_VECT)
        IELSR_reg(BSP_CFG_RTC_ALM_OR_PRD_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_RTC_ALM_OR_PRD_VECT) |= ICU_EVENT_RTC_ALM_OR_PRD;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_IIC0_ENDI_IIC0_WUI_VECT)
        IELSR_reg(BSP_CFG_IIC0_ENDI_IIC0_WUI_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_IIC0_ENDI_IIC0_WUI_VECT) |= ICU_EVENT_IIC0_ENDI_IIC0_WUI;
    #endif

    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_IIC1_ENDI_IIC1_WUI_VECT)
        IELSR_reg(BSP_CFG_IIC1_ENDI_IIC1_WUI_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_IIC1_ENDI_IIC1_WUI_VECT) |= ICU_EVENT_IIC1_ENDI_IIC1_WUI;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_KEY_INTKR_VECT)
        IELSR_reg(BSP_CFG_KEY_INTKR_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_KEY_INTKR_VECT) |= ICU_EVENT_KEY_INTKR;
    #endif

    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_CAC_FEERI_VECT)
        IELSR_reg(BSP_CFG_CAC_FEERI_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_CAC_FEERI_VECT) |= ICU_EVENT_CAC_FEERI;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_CAC_MENDI_VECT)
        IELSR_reg(BSP_CFG_CAC_MENDI_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_CAC_MENDI_VECT) |= ICU_EVENT_CAC_MENDI;
    #endif

    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_CAC_OVFI_VECT)
        IELSR_reg(BSP_CFG_CAC_OVFI_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_CAC_OVFI_VECT) |= ICU_EVENT_CAC_OVFI;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_IOPORT_GROUP1_VECT)
        IELSR_reg(BSP_CFG_IOPORT_GROUP1_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_IOPORT_GROUP1_VECT) |= ICU_EVENT_IOPORT_GROUP1;
    #endif

    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_IOPORT_GROUP2_VECT)
        IELSR_reg(BSP_CFG_IOPORT_GROUP2_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_IOPORT_GROUP2_VECT) |= ICU_EVENT_IOPORT_GROUP2;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_TRNG_RD_REQ_VECT)
        IELSR_reg(BSP_CFG_TRNG_RD_REQ_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_TRNG_RD_REQ_VECT) |= ICU_EVENT_TRNG_RD_REQ;
    #endif
    
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_ELC_SWEVT0_VECT)
        IELSR_reg(BSP_CFG_ELC_SWEVT0_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_ELC_SWEVT0_VECT) |= ICU_EVENT_ELC_SWEVT0;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_ELC_SWEVT1_VECT)
        IELSR_reg(BSP_CFG_ELC_SWEVT1_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_ELC_SWEVT1_VECT) |= ICU_EVENT_ELC_SWEVT1;
    #endif
    
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_SAU0_ENDI0_VECT)
        IELSR_reg(BSP_CFG_SAU0_ENDI0_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        #if (0U == (BSP_CFG_SAU0_ENDI0_VECT % 8U))
            IELSR_reg(BSP_CFG_SAU0_ENDI0_VECT) |= ICU_EVENT_SAU0_ENDI0_0;
        #else
            IELSR_reg(BSP_CFG_SAU0_ENDI0_VECT) |= ICU_EVENT_SAU0_ENDI0_4;
        #endif
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_SAU0_ENDI1_VECT)
        IELSR_reg(BSP_CFG_SAU0_ENDI1_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        #if (1U == (BSP_CFG_SAU0_ENDI1_VECT % 8U))
            IELSR_reg(BSP_CFG_SAU0_ENDI1_VECT) |= ICU_EVENT_SAU0_ENDI1_1;
        #else
            IELSR_reg(BSP_CFG_SAU0_ENDI1_VECT) |= ICU_EVENT_SAU0_ENDI1_5;
        #endif
    #endif
    
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_SAU0_ENDI2_VECT)
        IELSR_reg(BSP_CFG_SAU0_ENDI2_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_SAU0_ENDI2_VECT) |= ICU_EVENT_SAU0_ENDI2;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_SAU0_ENDI3_VECT)
        IELSR_reg(BSP_CFG_SAU0_ENDI3_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_SAU0_ENDI3_VECT) |= ICU_EVENT_SAU0_ENDI3;
    #endif
    
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_SAU1_ENDI0_VECT)
        IELSR_reg(BSP_CFG_SAU1_ENDI0_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_SAU1_ENDI0_VECT) |= ICU_EVENT_SAU1_ENDI0;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_SAU1_ENDI1_VECT)
        IELSR_reg(BSP_CFG_SAU1_ENDI1_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_SAU1_ENDI1_VECT) |= ICU_EVENT_SAU1_ENDI1;
    #endif
    
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_SAU0_INTSRE0_VECT)
        IELSR_reg(BSP_CFG_SAU0_INTSRE0_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_SAU0_INTSRE0_VECT) |= ICU_EVENT_SAU0_INTSRE0;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_SAU0_INTSRE1_VECT)
        IELSR_reg(BSP_CFG_SAU0_INTSRE1_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_SAU0_INTSRE1_VECT) |= ICU_EVENT_SAU0_INTSRE1;
    #endif
    
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_SAU1_INTSRE2_VECT)
        IELSR_reg(BSP_CFG_SAU1_INTSRE2_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_SAU1_INTSRE2_VECT) |= ICU_EVENT_SAU1_INTSRE2;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_TAU0_ENDI0_VECT)
        IELSR_reg(BSP_CFG_TAU0_ENDI0_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_TAU0_ENDI0_VECT) |= ICU_EVENT_TAU0_ENDI0;
    #endif
    
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_TAU0_ENDI1_VECT)
        IELSR_reg(BSP_CFG_TAU0_ENDI1_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_TAU0_ENDI1_VECT) |= ICU_EVENT_TAU0_ENDI1;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_TAU0_ENDI2_VECT)
        IELSR_reg(BSP_CFG_TAU0_ENDI2_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_TAU0_ENDI2_VECT) |= ICU_EVENT_TAU0_ENDI2;
    #endif
    
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_TAU0_ENDI3_VECT)
        IELSR_reg(BSP_CFG_TAU0_ENDI3_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_TAU0_ENDI3_VECT) |= ICU_EVENT_TAU0_ENDI3;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_TAU0_ENDI4_VECT)
        IELSR_reg(BSP_CFG_TAU0_ENDI4_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_TAU0_ENDI4_VECT) |= ICU_EVENT_TAU0_ENDI4;
    #endif
    
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_TAU0_ENDI5_VECT)
        IELSR_reg(BSP_CFG_TAU0_ENDI5_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_TAU0_ENDI5_VECT) |= ICU_EVENT_TAU0_ENDI5;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_TAU0_ENDI6_VECT)
        IELSR_reg(BSP_CFG_TAU0_ENDI6_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_TAU0_ENDI6_VECT) |= ICU_EVENT_TAU0_ENDI6;
    #endif
    
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_TAU0_ENDI7_VECT)
        IELSR_reg(BSP_CFG_TAU0_ENDI7_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_TAU0_ENDI7_VECT) |= ICU_EVENT_TAU0_ENDI7;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_TAU0_MODE8_ENDI1_VECT)
        IELSR_reg(BSP_CFG_TAU0_MODE8_ENDI1_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_TAU0_MODE8_ENDI1_VECT) |= ICU_EVENT_TAU0_MODE8_ENDI1;
    #endif
    
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_TAU0_MODE8_ENDI3_VECT)
        IELSR_reg(BSP_CFG_TAU0_MODE8_ENDI3_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_TAU0_MODE8_ENDI3_VECT) |= ICU_EVENT_TAU0_MODE8_ENDI3;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_TML32_OUTI_VECT)
        IELSR_reg(BSP_CFG_TML32_OUTI_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        #if (0U == (BSP_CFG_TML32_OUTI_VECT % 8U))
            IELSR_reg(BSP_CFG_TML32_OUTI_VECT) |= ICU_EVENT_TML32_OUTI_0;
        #else
            IELSR_reg(BSP_CFG_TML32_OUTI_VECT) |= ICU_EVENT_TML32_OUTI_4;
        #endif
    #endif
    
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_REMC_OUTI_VECT)
        IELSR_reg(BSP_CFG_REMC_OUTI_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_REMC_OUTI_VECT) |= ICU_EVENT_REMC_OUTI;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_UARTA_TX_ENDI0_VECT)
        IELSR_reg(BSP_CFG_UARTA_TX_ENDI0_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_UARTA_TX_ENDI0_VECT) |= ICU_EVENT_UARTA_TX_ENDI0;
    #endif
    
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_UARTA_RX_ENDI0_VECT)
        IELSR_reg(BSP_CFG_UARTA_RX_ENDI0_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_UARTA_RX_ENDI0_VECT) |= ICU_EVENT_UARTA_RX_ENDI0;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_UARTA_RX_ERI0_VECT)
        IELSR_reg(BSP_CFG_UARTA_RX_ERI0_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_UARTA_RX_ERI0_VECT) |= ICU_EVENT_UARTA_RX_ERI0;
    #endif
        
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_UARTA_TX_ENDI1_VECT)
        IELSR_reg(BSP_CFG_UARTA_TX_ENDI1_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_UARTA_TX_ENDI1_VECT) |= ICU_EVENT_UARTA_TX_ENDI1;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_UARTA_RX_ENDI1_VECT)
        IELSR_reg(BSP_CFG_UARTA_RX_ENDI1_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_UARTA_RX_ENDI1_VECT) |= ICU_EVENT_UARTA_RX_ENDI1;
    #endif
        
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_UARTA_RX_ERI1_VECT)
        IELSR_reg(BSP_CFG_UARTA_RX_ERI1_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_UARTA_RX_ERI1_VECT) |= ICU_EVENT_UARTA_RX_ERI1;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_COMP_DET0_VECT)
        IELSR_reg(BSP_CFG_COMP_DET0_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_COMP_DET0_VECT) |= ICU_EVENT_COMP_DET0;
    #endif
        
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_COMP_DET1_VECT)
        IELSR_reg(BSP_CFG_COMP_DET1_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_COMP_DET1_VECT) |= ICU_EVENT_COMP_DET1;
    #endif
     
    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_ADC_ENDI_VECT)
        IELSR_reg(BSP_CFG_ADC_ENDI_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        #if (3U == (BSP_CFG_ADC_ENDI_VECT % 8U))
            IELSR_reg(BSP_CFG_ADC_ENDI_VECT) |= ICU_EVENT_ADC_ENDI_3;
        #else
            IELSR_reg(BSP_CFG_ADC_ENDI_VECT) |= ICU_EVENT_ADC_ENDI_7;
        #endif
    #endif

    #if BSP_PRV_VALID_MAP_INT(BSP_CFG_DOC_DOPCI_VECT)
        IELSR_reg(BSP_CFG_DOC_DOPCI_VECT) &= 0xFFFFFFE0U; //clear IELSR[4:0] bit
        IELSR_reg(BSP_CFG_DOC_DOPCI_VECT) |= ICU_EVENT_DOC_DOPCI;
    #endif
}  
#endif
