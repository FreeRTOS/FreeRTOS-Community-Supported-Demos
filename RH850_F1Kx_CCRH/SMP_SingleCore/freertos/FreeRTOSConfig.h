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
* Copyright (C) 2018 - 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/


#ifndef FREERTOSCONFIG_H_
#define FREERTOSCONFIG_H_

#include "FreeRTOSConfigSingleCore.h"
/*#include "FreeRTOSConfigMultiCore.h" */


#define configTASK_NOTIFICATION_ARRAY_ENTRIES    3
#ifdef configUSE_TICK_HOOK
    #undef configUSE_TICK_HOOK
#endif
#define configUSE_TICK_HOOK                          1
#define configPRINTF( X )    printf X

#define configSTART_TASK_NOTIFY_TESTS                1
#define configSTART_TASK_NOTIFY_ARRAY_TESTS          0
#define configSTART_BLOCKING_QUEUE_TESTS             0
#define configSTART_SEMAPHORE_TESTS                  0
#define configSTART_POLLED_QUEUE_TESTS               0
#define configSTART_GENERIC_QUEUE_TESTS              0
#define configSTART_PEEK_QUEUE_TESTS                 0
#define configSTART_INTEGER_MATH_TESTS               0
#define configSTART_MATH_TESTS                       0
#define configSTART_RECURSIVE_MUTEX_TESTS            0
#define configSTART_COUNTING_SEMAPHORE_TESTS         0
#define configSTART_QUEUE_SET_TESTS                  0
#define configSTART_QUEUE_OVERWRITE_TESTS            0
#define configSTART_EVENT_GROUP_TESTS                0
#define configSTART_INTERRUPT_SEMAPHORE_TESTS        0
#define configSTART_QUEUE_SET_POLLING_TESTS          0
#define configSTART_BLOCK_TIME_TESTS                 0
#define configSTART_ABORT_DELAY_TESTS                0
#define configSTART_MESSAGE_BUFFER_TESTS             0
#define configSTART_STREAM_BUFFER_TESTS              0
#define configSTART_STREAM_BUFFER_INTERRUPT_TESTS    0
#define configSTART_TIMER_TESTS                      0
#define configSTART_INTERRUPT_QUEUE_TESTS            0
#define configSTART_REGISTER_TESTS                   0
#define configSTART_DELETE_SELF_TESTS                0

#endif /* FREERTOSCONFIG_H_ */
