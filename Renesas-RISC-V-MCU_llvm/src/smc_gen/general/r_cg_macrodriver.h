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
* File Name        : r_cg_macrodriver.h
* Version          : 1.0.30
* Device(s)        : R9A02G0214CNE
* Description      : Macro header file for code generation.
* Creation Date    : 
***********************************************************************************************************************/


/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "platform.h"
#include "r_cg_interrupt_handlers.h"

#ifndef MODULEID_H
#define MODULEID_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#ifndef __TYPEDEF__
#endif
/* Interrupt modes */
#define _C2_INT_NONVECTORED_MODE (0xC2U)    /* interrupt non-vector  mode */
#define _C3_INT_VECTOR_MODE      (0xC3U)    /* interrupt vector  mode */
/* Interrupt priority levels */
#define _0F_INT_PRIORITY_15 (0x0FU)    /* low priority */
#define _1F_INT_PRIORITY_14 (0x1FU)    /* level 14 */
#define _2F_INT_PRIORITY_13 (0x2FU)    /* level 13 */
#define _3F_INT_PRIORITY_12 (0x3FU)    /* level 12 */
#define _4F_INT_PRIORITY_11 (0x4FU)    /* level 11 */
#define _5F_INT_PRIORITY_10 (0x5FU)    /* level 10 */
#define _6F_INT_PRIORITY_9  (0x6FU)    /* level 9 */
#define _7F_INT_PRIORITY_8  (0x7FU)    /* level 8 */
#define _8F_INT_PRIORITY_7  (0x8FU)    /* level 7 */
#define _9F_INT_PRIORITY_6  (0x9FU)    /* level 6 */
#define _AF_INT_PRIORITY_5  (0xAFU)    /* level 5 */
#define _BF_INT_PRIORITY_4  (0xBFU)    /* level 4 */
#define _CF_INT_PRIORITY_3  (0xCFU)    /* level 3 */
#define _DF_INT_PRIORITY_2  (0xDFU)    /* level 2 */
#define _EF_INT_PRIORITY_1  (0xEFU)    /* level 1 */
#define _FF_INT_PRIORITY_0  (0xFFU)    /* high priority */
/* Status list definition */
#define MD_STATUSBASE        (0x00U)
#define MD_OK                (MD_STATUSBASE + 0x00U)    /* register setting OK */
#define MD_SPT               (MD_STATUSBASE + 0x01U)    /* IIC stop */
#define MD_NACK              (MD_STATUSBASE + 0x02U)    /* IIC no ACK */
#define MD_BUSY1             (MD_STATUSBASE + 0x03U)    /* busy 1 */
#define MD_BUSY2             (MD_STATUSBASE + 0x04U)    /* busy 2 */
#define MD_OVERRUN           (MD_STATUSBASE + 0x05U)    /* IIC OVERRUN occur */
/* Error list definition */
#define MD_ERRORBASE         (0x80U)
#define MD_ERROR             (MD_ERRORBASE + 0x00U)    /* error */
#define MD_ARGERROR          (MD_ERRORBASE + 0x01U)    /* error argument input error */
#define MD_ERROR1            (MD_ERRORBASE + 0x02U)    /* error 1 */
#define MD_ERROR2            (MD_ERRORBASE + 0x03U)    /* error 2 */
#define MD_ERROR3            (MD_ERRORBASE + 0x04U)    /* error 3 */
#define MD_ERROR4            (MD_ERRORBASE + 0x05U)    /* error 4 */
#define MD_ERROR5            (MD_ERRORBASE + 0x06U)    /* error 5 */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
#ifndef __TYPEDEF__
#define __TYPEDEF__
typedef unsigned short       MD_STATUS;
#endif

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_Systeminit (void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
