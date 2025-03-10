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
* File Name        : Config_ICU.c
* Component Version: 1.0.0
* Device(s)        : R9A02G0214CNE
* Description      : This file implements device driver for Config_ICU.
* Creation Date    : 
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "Config_ICU.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_ICU_Create
* Description  : This function initializes the ICU module
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ICU_Create(void)
{
    R_CLIC->clicintie23_b.IE = 0U;    /* disable IRQ4 interrupt */
    R_ICU->IELSR4 &= 0xFFFEFFFFU;    /* clear IRQ4 interrupt flag */

    /* Set IRQ4 pin */
    R_PFS->P108PFS_b.ISEL = 1U;
    R_PFS->P108PFS_b.PDR = 0U;

    /* IRQ4 settings */
    R_ICU->IRQCR4_b.FLTEN = 0U;
    R_ICU->IRQCR4 = _00_ICU_IRQ_FILTER_DISABLE | _00_ICU_IRQ_EDGE_FALLING;

    /* Set IRQ4 Interrupt */
    R_CLIC->clicintctl23 = _0F_INT_PRIORITY_15;    /* set PORT_IRQ4 interrupt level 15 priority */
    R_CLIC->clicintattr23 = _C3_INT_VECTOR_MODE;    /* set PORT_IRQ4 interrupt to vector mode */
    R_ICU->IELSR4 &= 0xFFFFFFE0U;
    R_ICU->IELSR4 |= 0x16U;    /* set value of PORT_IRQ4 interrupt event selection */

    R_Config_ICU_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_ICU_IRQ4_Start
* Description  : This function enables IRQ4 interrupt
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ICU_IRQ4_Start(void)
{
    R_ICU->IELSR4 &= 0xFFFEFFFFU;    /* clear IRQ4 interrupt flag */
    R_CLIC->clicintie23_b.IE = 1U;    /* enable IRQ4 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_ICU_IRQ4_Stop
* Description  : This function disables IRQ4 interrupt
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ICU_IRQ4_Stop(void)
{
    R_CLIC->clicintie23_b.IE = 0U;    /* disable IRQ4 interrupt */
    R_ICU->IELSR4 &= 0xFFFEFFFFU;    /* clear IRQ4 interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
