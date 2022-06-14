/*
 * FreeRTOS V202112.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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
 * https://www.FreeRTOS.org
 * https://aws.amazon.com/freertos
 *
 */

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/* Interface include files. */
#include "RegTests.h"

/* Tasks that implement register tests. */
static void prvRegisterTest1Task( void *pvParameters );
static void prvRegisterTest2Task( void *pvParameters );
static void prvRegisterTest3Task( void *pvParameters );
static void prvRegisterTest4Task( void *pvParameters );

/* Flag that will be latched to pdTRUE should any unexpected behaviour be
detected in any of the tasks. */
static volatile BaseType_t xErrorDetected = pdFALSE;

/* Counters that are incremented on each cycle of a test.  This is used to
detect a stalled task - a test that is no longer running. */
static volatile uint32_t ulRegisterTest1Counter = 0;
static volatile uint32_t ulRegisterTest2Counter = 0;
static volatile uint32_t ulRegisterTest3Counter = 0;
static volatile uint32_t ulRegisterTest4Counter = 0;
/*-----------------------------------------------------------*/

static void prvRegisterTest1Task( void *pvParameters )
{
    ( void ) pvParameters;

    /* 1. Fill the registers stored as part of task context with known values.*/
    __asm("reg1_loop:                    \n"                       \
          " movl xar2, #0xFFFF           \n"                       \
          " movl xar3, #0xF0F0           \n"                       \
          " movl xar4, #0x1010           \n"                       \
          " movl xar5, #0x0101           \n"                       \
          " movl xar6, #0x1111           \n"                       \
          " movl xar7, #0x2222           \n"                       \
         );

    /* 2. Force a context switch. */
    vTaskDelay(0);
    /* 3. Verify that all the registers contain expected values.*/
    /* 4. If all the register contain expected values, increment ulRegisterTest1Counter.*/
    __asm(" mov acc, #0xFFFF            \n"                        \
          " cmpl acc,@xar2              \n"                        \
          " sb reg1_error_loop,neq      \n"                        \
          " mov acc, #0xF0F0            \n"                        \
          " cmpl acc,@xar3              \n"                        \
          " sb reg1_error_loop,neq      \n"                        \
          " mov acc, #0x1010            \n"                        \
          " cmpl acc,@xar4              \n"                        \
          " sb reg1_error_loop,neq      \n"                        \
          " mov acc, #0x0101            \n"                        \
          " cmpl acc,@xar5              \n"                        \
          " sb reg1_error_loop,neq      \n"                        \
          " mov acc, #0x1111            \n"                        \
          " cmpl acc,@xar6              \n"                        \
          " sb reg1_error_loop,neq      \n"                        \
          " mov acc, #0x2222            \n"                        \
          " cmpl acc,@xar7              \n"                        \
          " sb reg1_error_loop,neq      \n"                        \
          "* Increment the loop counter to indicate this test is still functioning \n" \
          " .if __TI_EABI__             \n"                        \
          " movl xar0, #ulRegisterTest1Counter  \n"                \
          " .else                               \n"                \
          " movl xar0, #_ulRegisterTest1Counter \n"                \
          " .endif                              \n"                \
          " mov acc, *xar0                      \n"                \
          " add acc, #1                         \n"                \
          " movl *xar0,acc                      \n"                \
          " sb reg1_loop,unc                    \n"                \
          "reg1_error_loop:                     \n"                \
          "* If this line is hit then there was an error in a core register value.   \n" \
          "*This loop ensures the loop counter variable stops incrementing.          \n" \
          " sb reg1_error_loop,unc              \n"
         );
}
/*-----------------------------------------------------------*/

static void prvRegisterTest2Task( void *pvParameters )
{
    ( void ) pvParameters;

    /* 1. Fill the registers stored as part of task context with known values.*/
    __asm("reg2_loop:                    \n"                       \
          " movl xar2, #0x3333           \n"                       \
          " movl xar3, #0x4444           \n"                       \
          " movl xar4, #0x5555           \n"                       \
          " movl xar5, #0x6666           \n"                       \
          " movl xar6, #0x7777           \n"                       \
          " movl xar7, #0x8888           \n"                       \
         );

    /* 2. Force a context switch. */
    vTaskDelay(0);
    /* 3. Verify that all the registers contain expected values.*/
    /* 4. If all the register contain expected values, increment ulRegisterTest1Counter.*/
    __asm(" mov acc, #0x3333            \n"                        \
          " cmpl acc,@xar2              \n"                        \
          " sb reg2_error_loop,neq      \n"                        \
          " mov acc, #0x4444            \n"                        \
          " cmpl acc,@xar3              \n"                        \
          " sb reg2_error_loop,neq      \n"                        \
          " mov acc, #0x5555            \n"                        \
          " cmpl acc,@xar4              \n"                        \
          " sb reg2_error_loop,neq      \n"                        \
          " mov acc, #0x6666            \n"                        \
          " cmpl acc,@xar5              \n"                        \
          " sb reg2_error_loop,neq      \n"                        \
          " mov acc, #0x7777            \n"                        \
          " cmpl acc,@xar6              \n"                        \
          " sb reg2_error_loop,neq      \n"                        \
          " mov acc, #0x8888            \n"                        \
          " cmpl acc,@xar7              \n"                        \
          " sb reg2_error_loop,neq      \n"                        \
          "* Increment the loop counter to indicate this test is still functioning \n" \
          " .if __TI_EABI__             \n"                        \
          " movl xar0, #ulRegisterTest2Counter  \n"                \
          " .else                               \n"                \
          " movl xar0, #_ulRegisterTest2Counter \n"                \
          " .endif                              \n"                \
          " mov acc, *xar0                      \n"                \
          " add acc, #1                         \n"                \
          " movl *xar0,acc                      \n"                \
          " sb reg2_loop,unc                    \n"                \
          "reg2_error_loop:                     \n"                \
          "* If this line is hit then there was an error in a core register value.   \n" \
          "*This loop ensures the loop counter variable stops incrementing.          \n" \
          " sb reg2_error_loop,unc              \n"
         );
}
/*-----------------------------------------------------------*/

static void prvRegisterTest3Task( void *pvParameters )
{
    ( void ) pvParameters;

    /* 1. Fill the registers stored as part of task context with known values.*/
    __asm("reg3_loop:                    \n"                       \
          " movl xar2, #0x1111           \n"                       \
          " movl xar3, #0x2222           \n"                       \
          " movl xar4, #0x3333           \n"                       \
          " movl xar5, #0xAAAA           \n"                       \
          " movl xar6, #0xBBBB           \n"                       \
          " movl xar7, #0xCCCC           \n"                       \
         );

    /* 2. Force a context switch. */
    vTaskDelay(0);
    /* 3. Verify that all the registers contain expected values.*/
    /* 4. If all the register contain expected values, increment ulRegisterTest3Counter.*/
    __asm(" mov acc, #0x1111            \n"                        \
          " cmpl acc,@xar2              \n"                        \
          " sb reg3_error_loop,neq      \n"                        \
          " mov acc, #0x2222            \n"                        \
          " cmpl acc,@xar3              \n"                        \
          " sb reg3_error_loop,neq      \n"                        \
          " mov acc, #0x3333            \n"                        \
          " cmpl acc,@xar4              \n"                        \
          " sb reg3_error_loop,neq      \n"                        \
          " mov acc, #0xAAAA            \n"                        \
          " cmpl acc,@xar5              \n"                        \
          " sb reg3_error_loop,neq      \n"                        \
          " mov acc, #0xBBBB            \n"                        \
          " cmpl acc,@xar6              \n"                        \
          " sb reg3_error_loop,neq      \n"                        \
          " mov acc, #0xCCCC            \n"                        \
          " cmpl acc,@xar7              \n"                        \
          " sb reg3_error_loop,neq      \n"                        \
          "* Increment the loop counter to indicate this test is still functioning \n" \
          " .if __TI_EABI__              \n"                       \
          " movl xar0, #ulRegisterTest3Counter  \n"                \
          " .else                               \n"                \
          " movl xar0, #_ulRegisterTest3Counter \n"                \
          " .endif                              \n"                \
          " mov acc, *xar0                      \n"                \
          " add acc, #1                         \n"                \
          " movl *xar0,acc                      \n"                \
          " sb reg3_loop,unc                    \n"                \
          "reg3_error_loop:                     \n"                \
          "* If this line is hit then there was an error in a core register value.   \n" \
          "*This loop ensures the loop counter variable stops incrementing.          \n" \
          " sb reg3_error_loop,unc                   \n"
         );
}
/*-----------------------------------------------------------*/

static void prvRegisterTest4Task( void *pvParameters )
{
    ( void ) pvParameters;

    /* 1. Fill the registers stored as part of task context with known values.*/
    __asm("reg4_loop:                    \n"                       \
          " movl xar2, #0xDDDD           \n"                       \
          " movl xar3, #0xEEEE           \n"                       \
          " movl xar4, #0xFFFF           \n"                       \
          " movl xar5, #0x9999           \n"                       \
          " movl xar6, #0x8888           \n"                       \
          " movl xar7, #0x7777           \n"                       \
         );

    /* 2. Force a context switch. */
    vTaskDelay(0);
    /* 3. Verify that all the registers contain expected values.*/
    /* 4. If all the register contain expected values, increment ulRegisterTest1Counter.*/
    __asm(" mov acc, #0xDDDD            \n"                        \
          " cmpl acc,@xar2              \n"                        \
          " sb reg4_error_loop,neq      \n"                        \
          " mov acc, #0xEEEE            \n"                        \
          " cmpl acc,@xar3              \n"                        \
          " sb reg4_error_loop,neq      \n"                        \
          " mov acc, #0xFFFF            \n"                        \
          " cmpl acc,@xar4              \n"                        \
          " sb reg4_error_loop,neq      \n"                        \
          " mov acc, #0x9999            \n"                        \
          " cmpl acc,@xar5              \n"                        \
          " sb reg4_error_loop,neq      \n"                        \
          " mov acc, #0x8888            \n"                        \
          " cmpl acc,@xar6              \n"                        \
          " sb reg4_error_loop,neq      \n"                        \
          " mov acc, #0x7777            \n"                        \
          " cmpl acc,@xar7              \n"                        \
          " sb reg4_error_loop,neq      \n"                        \
          "* Increment the loop counter to indicate this test is still functioning \n" \
          " .if __TI_EABI__             \n"                        \
          " movl xar0, #ulRegisterTest4Counter  \n"                \
          " .else                               \n"                \
          " movl xar0, #_ulRegisterTest4Counter \n"                \
          " .endif                              \n"                \
          " mov acc, *xar0                      \n"                \
          " add acc, #1                         \n"                \
          " movl *xar0,acc                      \n"                \
          " sb reg4_loop,unc                    \n"                \
          "reg4_error_loop:                     \n"                \
          "* If this line is hit then there was an error in a core register value.   \n" \
          "*This loop ensures the loop counter variable stops incrementing.          \n" \
          " sb reg4_error_loop,unc                   \n"
         );
}
/*-----------------------------------------------------------*/

void vStartRegisterTasks( UBaseType_t uxPriority )
{
    BaseType_t ret;

    ret = xTaskCreate( prvRegisterTest1Task, "RegTest1", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
    configASSERT( ret == pdPASS );

    ret = xTaskCreate( prvRegisterTest2Task, "RegTest2", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
    configASSERT( ret == pdPASS );

    ret = xTaskCreate( prvRegisterTest3Task, "RegTest3", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
    configASSERT( ret == pdPASS );

    ret = xTaskCreate( prvRegisterTest4Task, "RegTest4", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
    configASSERT( ret == pdPASS );
}
/*-----------------------------------------------------------*/

BaseType_t xAreRegisterTasksStillRunning( void )
{
static uint32_t ulLastRegisterTest1Counter = 0, ulLastRegisterTest2Counter = 0;
static uint32_t ulLastRegisterTest3Counter = 0, ulLastRegisterTest4Counter = 0;

    /* If the register test task is still running then we expect the loop
     * counters to have incremented since this function was last called. */
    if( ulLastRegisterTest1Counter == ulRegisterTest1Counter )
    {
        xErrorDetected = pdTRUE;
    }

    if( ulLastRegisterTest2Counter == ulRegisterTest2Counter )
    {
        xErrorDetected = pdTRUE;
    }

    if( ulLastRegisterTest3Counter == ulRegisterTest3Counter )
    {
        xErrorDetected = pdTRUE;
    }

    if( ulLastRegisterTest4Counter == ulRegisterTest4Counter )
    {
        xErrorDetected = pdTRUE;
    }

    ulLastRegisterTest1Counter = ulRegisterTest1Counter;
    ulLastRegisterTest2Counter = ulRegisterTest2Counter;
    ulLastRegisterTest3Counter = ulRegisterTest3Counter;
    ulLastRegisterTest4Counter = ulRegisterTest4Counter;

    /* Errors detected in the task itself will have latched xErrorDetected
     * to true. */
    return ( BaseType_t ) !xErrorDetected;
}
/*-----------------------------------------------------------*/
