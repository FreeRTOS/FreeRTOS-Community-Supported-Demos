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
* File Name        : r_cg_sau_common.c
* Version          : 1.0.30
* Device(s)        : R9A02G0214CNE
* Description      : None
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
#include "Config_UART0.h"
#include "r_cg_sau_common.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_SAU0_Create
* Description  : This function enables SAU0 input clock supply and initializes SAU0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Create(void)
{
    R_MSTP->MSTPCRB_b.MSTPB21 = 0U;    /* cancel the SAU0-stop state*/
    R_Config_UART0_Create();
}

/***********************************************************************************************************************
* Function Name: R_SAU1_Create
* Description  : This function enables SAU1 input clock supply and initializes SAU1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU1_Create(void)
{
    R_MSTP->MSTPCRB_b.MSTPB20 = 0U;    /* cancel the SAU1-stop state*/
}

/***********************************************************************************************************************
* Function Name: R_SAU0_Set_SnoozeOn
* Description  : This function enables SAU0 wakeup function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Set_SnoozeOn(void)
{
    R_SAU0->SSC0 |= _0001_SAU_SNOOZE_ON;
}

/***********************************************************************************************************************
* Function Name: R_SAU0_Set_SnoozeOff
* Description  : This function disables SAU0 wakeup function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Set_SnoozeOff(void)
{
    R_SAU0->SSC0 &= (uint16_t)~_0001_SAU_SNOOZE_ON;
}

/***********************************************************************************************************************
* Function Name: R_SAU1_Set_SnoozeOn
* Description  : This function enables SAU1 wakeup function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU1_Set_SnoozeOn(void)
{
    R_SAU1->SSC1 |= _0001_SAU_SNOOZE_ON;
}

/***********************************************************************************************************************
* Function Name: R_SAU1_Set_SnoozeOff
* Description  : This function disables SAU1 wakeup function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU1_Set_SnoozeOff(void)
{
    R_SAU1->SSC1 &= (uint16_t)~_0001_SAU_SNOOZE_ON;
}

/***********************************************************************************************************************
* Function Name: R_SAU0_Cancel_ModuleStop
* Description  : This function cancel SAU0 the module-stop state.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Cancel_ModuleStop(void)
{
    R_MSTP->MSTPCRB_b.MSTPB21 = 0U;    /* cancel the SAU0-stop state*/
}

/***********************************************************************************************************************
* Function Name: R_SAU0_Enter_ModuleStop
* Description  : This function enter SAU0 the module-stop state.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Enter_ModuleStop(void)
{
    R_MSTP->MSTPCRB_b.MSTPB21 = 1U;    /* enter the SAU0-stop state*/
}

/***********************************************************************************************************************
* Function Name: R_SAU1_Cancel_ModuleStop
* Description  : This function cancel SAU1 the module-stop state.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU1_Cancel_ModuleStop(void)
{
    R_MSTP->MSTPCRB_b.MSTPB20 = 0U;    /* cancel the SAU1-stop state*/
}

/***********************************************************************************************************************
* Function Name: R_SAU1_Enter_ModuleStop
* Description  : This function enter SAU1 the module-stop state.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU1_Enter_ModuleStop(void)
{
    R_MSTP->MSTPCRB_b.MSTPB20 = 1U;    /* enter the SAU1-stop state*/
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
