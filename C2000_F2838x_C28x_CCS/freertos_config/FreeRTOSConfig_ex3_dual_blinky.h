/*
 * Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

//--------------------------------------------------------------------------------------------------
// Application specific definitions.
//
// These definitions should be adjusted for your particular hardware and
// application requirements.
//
// THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
// FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
//
// See http://www.freertos.org/a00110.html.
//--------------------------------------------------------------------------------------------------

#define configUSE_PREEMPTION                1
#define configUSE_IDLE_HOOK                 0
#define configUSE_TICK_HOOK                 0
#define configCPU_CLOCK_HZ                  ( ( unsigned long ) 200000000 )
#define configTICK_RATE_HZ                  ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES                ( 5 )
#define configMINIMAL_STACK_SIZE            ( ( unsigned short ) 128 )
#define configTOTAL_HEAP_SIZE               ( ( size_t ) ( 8 * 1024 ) )
#define configMAX_TASK_NAME_LEN             ( 16 )
#define configUSE_TRACE_FACILITY            1
#define configUSE_16_BIT_TICKS              0
#define configIDLE_SHOULD_YIELD             0
#define configUSE_CO_ROUTINES               0
#define configUSE_MUTEXES                   1
#define configUSE_RECURSIVE_MUTEXES         1
#define configCHECK_FOR_STACK_OVERFLOW      2
#define configSUPPORT_STATIC_ALLOCATION     1
#define configSUPPORT_DYNAMIC_ALLOCATION    1

/* This option needs to be enabled to keep the heap memory in valid memory section
 * as the c28x stack memory can be allocated in the lower 64k RAM memory only.
 */
#define configAPPLICATION_ALLOCATED_HEAP        1

// Set the following definitions to 1 to include the API function, or zero
// to exclude the API function.

#define INCLUDE_vTaskPrioritySet            1
#define INCLUDE_uxTaskPriorityGet           1
#define INCLUDE_vTaskDelete                 1
#define INCLUDE_vTaskCleanUpResources       0
#define INCLUDE_vTaskSuspend                1
#define INCLUDE_vTaskDelayUntil             1
#define INCLUDE_vTaskDelay                  1
#define INCLUDE_uxTaskGetStackHighWaterMark 1

#endif /* FREERTOS_CONFIG_H */

