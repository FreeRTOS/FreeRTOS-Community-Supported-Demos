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
* File Name    : r_bsp_machine_timer.h
* Description  : Implements functions that generate interrupt support.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 10.06.2024 1.20     Support machine timer setting
*         : 26.07.2024 1.21     Add machine_timer_refresh() and get_interval_value().
***********************************************************************************************************************/
#include <stdint.h>
/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void machine_timer_create(void);
#if BSP_CFG_MACHINE_TIMER == 1
void machine_timer_start(void);
void machine_timer_stop(void);
void machine_timer_refresh(void);
uint64_t get_interval_value(void);
#endif
#if BSP_CFG_SOFTWARE_INTERRUPT == 1
void trigger_software_interrupt(void);
void clear_software_interrupt(void);
#endif
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
