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
* File Name    : mcu_option_settings.c
* Device(s)    : R9A02G021
* Description  : Definition of the Option-Settings Memory of MCU.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version   Description
*         : 20.01.2024 1.00      First Release
*         : 29.03.2024 1.10      Add Option memory setting for Segger toolchain
*         : 10.06.2024 1.20      Change the macro name endwith "DISABLE" to "FUNCTIONS"
                                 Change file name vecttbl.c to mcu_option_settings.c and description
                                 Remove BSP_CFG_STARTUP_DISABLE
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* BSP configuration. */
#include "platform.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/


/***********************************************************************************************************************
* The following array fills in the option function select registers and the ID code protection bytes.
***********************************************************************************************************************/
#define BSP_PRV_AWS_VALUE           (0xF800F800 | (BSP_CFG_ACCESS_WINDOW_END_BLOCK_ADDRESS << 16 | \
                                    BSP_CFG_ACCESS_WINDOW_START_BLOCK_ADDRESS))
#define BSP_PRV_SECS_VALUE          (0xFFFF9FFF| ((BSP_CFG_OCD_PROTECTION << 13) | (BSP_CFG_AWF_PROTECTION << 14)))
#define BSP_PRV_FLRPROTAC_REG_VALUE (0xFFFFFFFE | BSP_CFG_FLRPROTAC_REG_FUNCTIONS)
#if defined(__SEGGER_CC__)
const uint32_t __UIDS3reg    __attribute ((section(".option_uids3"))) = BSP_CFG_USER_ID_SETTING_3;
const uint32_t __UIDS2reg    __attribute ((section(".option_uids2"))) = BSP_CFG_USER_ID_SETTING_2;
const uint32_t __UIDS1reg    __attribute ((section(".option_uids1"))) = BSP_CFG_USER_ID_SETTING_1;
const uint32_t __UIDS0reg    __attribute ((section(".option_uids0"))) = BSP_CFG_USER_ID_SETTING_0;
const uint32_t __AWSreg    __attribute ((section(".option_aws"))) = BSP_PRV_AWS_VALUE;
const uint32_t __SECSreg   __attribute ((section(".option_secs"))) = BSP_PRV_SECS_VALUE;
const uint32_t Option_OSIS[]   __attribute ((section(".option_osis"))) = {
    BSP_CFG_OCD_SERIAL_ID_VALUE_0, /* __OSIS0reg */
    BSP_CFG_OCD_SERIAL_ID_VALUE_1, /* __OSIS1reg */
    BSP_CFG_OCD_SERIAL_ID_VALUE_2, /* __OSIS2reg */
    BSP_CFG_OCD_SERIAL_ID_VALUE_3  /* __OSIS3reg */
};
const uint32_t Option_FPR[]  __attribute ((section (".option_frp"))) = {
    // Address 0x408 - 0x43b
    0xffffffff, // 0x408
    0xffffffff, // 0x40c
    0xffffffff, // 0x410
    0xffffffff, // 0x414
    BSP_CFG_FLRPROTS_REG_VALUE, // 0x418
    BSP_CFG_FLRPROTE_REG_VALUE, // 0x41c
    0xffffffff, // 0x420
    0xffffffff, // 0x424
    0xffffffff, // 0x428
    0xffffffff, // 0x42c
    0xffffffff, // 0x430
    0xffffffff, // 0x434
    BSP_PRV_FLRPROTAC_REG_VALUE  // 0x438
};
const uint32_t __OFS1reg    __attribute ((section(".option_ofs1"))) = BSP_CFG_OFS1_REG_VALUE;
const uint32_t __OFS0reg    __attribute ((section(".option_ofs0"))) = BSP_CFG_OFS0_REG_VALUE;

#elif defined(__llvm__)
const uint32_t __UIDS3reg    __attribute__ ((section(".option_uids3"))) = BSP_CFG_USER_ID_SETTING_3;
const uint32_t __UIDS2reg    __attribute__ ((section(".option_uids2"))) = BSP_CFG_USER_ID_SETTING_2;
const uint32_t __UIDS1reg    __attribute__ ((section(".option_uids1"))) = BSP_CFG_USER_ID_SETTING_1;
const uint32_t __UIDS0reg    __attribute__ ((section(".option_uids0"))) = BSP_CFG_USER_ID_SETTING_0;
const uint32_t __AWSreg    __attribute__ ((section(".option_aws"))) = BSP_PRV_AWS_VALUE;
const uint32_t __SECSreg   __attribute__ ((section(".option_secs"))) = BSP_PRV_SECS_VALUE;
const uint32_t Option_OSIS[]   __attribute__ ((section(".option_osis"))) = {
    BSP_CFG_OCD_SERIAL_ID_VALUE_0, /* __OSIS0reg */
    BSP_CFG_OCD_SERIAL_ID_VALUE_1, /* __OSIS1reg */
    BSP_CFG_OCD_SERIAL_ID_VALUE_2, /* __OSIS2reg */
    BSP_CFG_OCD_SERIAL_ID_VALUE_3  /* __OSIS3reg */
};
const uint32_t Option_FPR[]  __attribute__ ((section (".option_frp"))) = {
    // Address 0x408 - 0x43b
    0xffffffff, // 0x408
    0xffffffff, // 0x40c
    0xffffffff, // 0x410
    0xffffffff, // 0x414
    BSP_CFG_FLRPROTS_REG_VALUE, // 0x418
    BSP_CFG_FLRPROTE_REG_VALUE, // 0x41c
    0xffffffff, // 0x420
    0xffffffff, // 0x424
    0xffffffff, // 0x428
    0xffffffff, // 0x42c
    0xffffffff, // 0x430
    0xffffffff, // 0x434
    BSP_PRV_FLRPROTAC_REG_VALUE  // 0x438
};
const uint32_t __OFS1reg    __attribute__ ((section(".option_ofs1"))) = BSP_CFG_OFS1_REG_VALUE;
const uint32_t __OFS0reg    __attribute__ ((section(".option_ofs0"))) = BSP_CFG_OFS0_REG_VALUE;

#elif defined(__ICCRISCV__)
#pragma location = 0x1010030
__root const uint32_t __UIDS3reg = BSP_CFG_USER_ID_SETTING_3;
#pragma location = 0x1010028
__root const uint32_t __UIDS2reg = BSP_CFG_USER_ID_SETTING_2;
#pragma location = 0x1010020
__root const uint32_t __UIDS1reg = BSP_CFG_USER_ID_SETTING_1;
#pragma location = 0x1010018
__root const uint32_t __UIDS0reg = BSP_CFG_USER_ID_SETTING_0;
#pragma location = 0x1010010
__root const uint32_t __AWSreg = BSP_PRV_AWS_VALUE;
#pragma location = 0x1010008
__root const uint32_t __SECSreg = BSP_PRV_SECS_VALUE;
#pragma location = 0x800
__root const uint32_t Option_OSIS[] = {
    BSP_CFG_OCD_SERIAL_ID_VALUE_0, /* __OSIS0reg */
    BSP_CFG_OCD_SERIAL_ID_VALUE_1, /* __OSIS1reg */
    BSP_CFG_OCD_SERIAL_ID_VALUE_2, /* __OSIS2reg */
    BSP_CFG_OCD_SERIAL_ID_VALUE_3  /* __OSIS3reg */
};
#pragma location = 0x408
__root const uint32_t Option_FPR[] = {
    // Address 0x408 - 0x43b
    0xffffffff, // 0x408
    0xffffffff, // 0x40c
    0xffffffff, // 0x410
    0xffffffff, // 0x414
    BSP_CFG_FLRPROTS_REG_VALUE, // 0x418
    BSP_CFG_FLRPROTE_REG_VALUE, // 0x41c
    0xffffffff, // 0x420
    0xffffffff, // 0x424
    0xffffffff, // 0x428
    0xffffffff, // 0x42c
    0xffffffff, // 0x430
    0xffffffff, // 0x434
    BSP_PRV_FLRPROTAC_REG_VALUE  // 0x438
};
#pragma location = 0x404
__root const uint32_t __OFS1reg = BSP_CFG_OFS1_REG_VALUE;
#pragma location = 0x400
__root const uint32_t __OFS0reg = BSP_CFG_OFS0_REG_VALUE;
#endif /* defined(__SEGGER_CC__) */

