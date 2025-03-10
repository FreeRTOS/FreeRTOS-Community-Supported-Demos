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
* File Name    : mcu_mapped_interrupts_private.h
* H/W Platform : GENERIC_R9A02G021
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 20.01.2024 1.00     First Release
***********************************************************************************************************************/

#ifndef MCU_MAPPED_INTERRUPTS_PRIVATE_H
#define MCU_MAPPED_INTERRUPTS_PRIVATE_H
 
/* Start and end of Interrupt vectors. */
#define BSP_PRV_INT_VECTOR_START    (0)
#define BSP_PRV_INT_VECTOR_END      (31)
 
/* Test to see if chosen vector is valid for a mapped interrupt. */
#define BSP_PRV_VALID_MAP_INT(y)    (((y + 0) >= BSP_PRV_INT_VECTOR_START) && \
                                    ((y + 0) <= BSP_PRV_INT_VECTOR_END))  
 
/* This definition is used to set for IELSRn register */
#define IELSR_reg(x)    _IELSR_reg(x)
#define _IELSR_reg(x)   R_ICU->IELSR##x

#endif
