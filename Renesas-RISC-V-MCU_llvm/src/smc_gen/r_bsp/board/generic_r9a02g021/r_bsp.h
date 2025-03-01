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
 **********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_bsp.h
 * H/W Platform : GENERIC_R9A02G021
 * Description  :
 **********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 20.01.2024 1.00     First Release
*         : 29.03.2024 1.10     Add #include header files when using Segger toolchain
***********************************************************************************************************************/
/* Make sure that no other platforms have already been defined. Do not touch this! */
#ifdef PLATFORM_DEFINED
#error "Error - Multiple platforms defined in platform.h!"
#else
#define PLATFORM_DEFINED
#endif

/***********************************************************************************************************************
INCLUDE APPROPRIATE MCU AND BOARD FILES
***********************************************************************************************************************/
#include "r_bsp_config.h"
#include "mcu/all/r_bsp_machine_timer.h"
#include "mcu/all/r_bsp_riscv_mcu_compiler.h"
#include "mcu/all/r_bsp_common.h"

#if defined(__SEGGER_CC__)
#include "mcu/r9a02g021/register_access/segger/iodefine.h"
#elif defined(__llvm__)
#include "mcu/r9a02g021/register_access/llvm/iodefine.h"
#elif defined(__ICCRISCV__)
#include "mcu/r9a02g021/register_access/iccriscv/iodefine.h"
#endif /* defined(__SEGGER_CC__) */

#include "mcu/r9a02g021/mcu_clocks.h"
#include "mcu/r9a02g021/mcu_info.h"
#include "mcu/r9a02g021/mcu_mapped_interrupts.h"

#include "board/generic_r9a02g021/hdwinit.h"
