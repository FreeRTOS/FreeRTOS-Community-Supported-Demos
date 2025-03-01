/*
 * FreeRTOS V202212.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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
 * https://github.com/FreeRTOS
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
//static void prvRegisterTest3Task( void *pvParameters );
//static void prvRegisterTest4Task( void *pvParameters );

/* Flag that will be latched to pdTRUE should any unexpected behavior be
detected in any of the tasks. */
static volatile BaseType_t xErrorDetected = pdFALSE;

/* Counters that are incremented on each cycle of a test.  This is used to
detect a stalled task - a test that is no longer running. */
static volatile uint32_t ulRegisterTest1Counter = 0;
static volatile uint32_t ulRegisterTest2Counter = 0;
//static volatile uint32_t ulRegisterTest3Counter = 0;
//static volatile uint32_t ulRegisterTest4Counter = 0;
/*-----------------------------------------------------------*/

static void prvRegisterTest1Task( void *pvParameters )
{
	( void ) pvParameters;

	for( ; ; )
	{
		/* 1. Fill the registers stored as part of task context with known values.
		* 2. Force a context switch.
		* 3. Verify that all the registers contain expected values.
		* 4. If all the register contain expected values, increment ulRegisterTest1Counter.
		*/

		// note that a0 is used for the return value

		// 1.
		asm volatile (
				"li a1, 431\n"
				"li a2, 432\n"
				"li a3, 433\n"
				"li a4, 434\n"
				"li a5, 435\n"
				"li a6, 436\n"
				"li a7, 437\n"
		);

		// 2.
		vTaskDelay(0);

		// 3.
		asm volatile (
				"li t0, 431\n"
				"bne a1, t0, reg1_err\n"
				"li t0, 432\n"
				"bne a2, t0, reg1_err\n"
				"li t0, 433\n"
				"bne a3, t0, reg1_err\n"
				"li t0, 434\n"
				"bne a4, t0, reg1_err\n"
				"li t0, 435\n"
				"bne a5, t0, reg1_err\n"
				"li t0, 436\n"
				"bne a6, t0, reg1_err\n"
				"li t0, 437\n"
				"bne a7, t0, reg1_err\n"
				"j reg1_passed\n"
		);

		asm volatile (
				"reg1_err:\n"
				"j reg1_err\n"
		);

		// 4.
		asm volatile (
				"reg1_passed:\n"
				"la t0, ulRegisterTest1Counter  # Load address of ulRegisterTest1Counter into t0\n"
				"lw t1, 0(t0)                   # Load the value of ulRegisterTest1Counter into t1\n"
				"addi t1, t1, 1                 # Increment t1 by 1\n"
				"sw t1, 0(t0)                   # Store the updated value back to ulRegisterTest1Counter\n"
		);
	}
}
/*-----------------------------------------------------------*/

static void prvRegisterTest2Task( void *pvParameters )
{
	( void ) pvParameters;

	for( ; ; )
	{
		/* 1. Fill the registers stored as part of task context with known values.
		* 2. Force a context switch.
		* 3. Verify that all the registers contain expected values.
		* 4. If all the register contain expected values, increment ulRegisterTest2Counter.
		*/

		// 1.
		asm volatile (
				"li a1, 681\n"
				"li a2, 682\n"
				"li a3, 683\n"
				"li a4, 684\n"
				"li a5, 685\n"
				"li a6, 686\n"
				"li a7, 687\n"
		);

		// 2.
		vTaskDelay(0);

		// 3.
		asm volatile (
				"li t0, 681\n"
				"bne a1, t0, reg2_err\n"
				"li t0, 682\n"
				"bne a2, t0, reg2_err\n"
				"li t0, 683\n"
				"bne a3, t0, reg2_err\n"
				"li t0, 684\n"
				"bne a4, t0, reg2_err\n"
				"li t0, 685\n"
				"bne a5, t0, reg2_err\n"
				"li t0, 686\n"
				"bne a6, t0, reg2_err\n"
				"li t0, 687\n"
				"bne a7, t0, reg2_err\n"
				"j reg2_passed\n"
		);

		asm volatile (
				"reg2_err:\n"
				"j reg2_err\n"
		);

		// 4.
		asm volatile (
				"reg2_passed:\n"
				"la t0, ulRegisterTest2Counter  # Load address of ulRegisterTest2Counter into t0\n"
				"lw t1, 0(t0)                   # Load the value of ulRegisterTest2Counter into t1\n"
				"addi t1, t1, 1                 # Increment t1 by 1\n"
				"sw t1, 0(t0)                   # Store the updated value back to ulRegisterTest2Counter\n"
		);
	}
}
/*-----------------------------------------------------------*/

//static void prvRegisterTest3Task( void *pvParameters )
//{
//	( void ) pvParameters;
//
//	for( ; ; )
//	{
//		/* 1. Fill the registers stored as part of task context with known values.
//		* 2. Force a context switch.
//		* 3. Verify that all the registers contain expected values.
//		* 4. If all the register contain expected values, increment ulRegisterTest3Counter.
//		*/
//
//		// 1.
//		asm volatile (
//				"li a1, 991\n"
//				"li a2, 992\n"
//				"li a3, 993\n"
//				"li a4, 994\n"
//				"li a5, 995\n"
//				"li a6, 996\n"
//				"li a7, 997\n"
//		);
//
//		// 2.
//		vTaskDelay(0);
//
//		// 3.
//		asm volatile (
//				"li t0, 991\n"
//				"bne a1, t0, reg3_err\n"
//				"li t0, 992\n"
//				"bne a2, t0, reg3_err\n"
//				"li t0, 993\n"
//				"bne a3, t0, reg3_err\n"
//				"li t0, 994\n"
//				"bne a4, t0, reg3_err\n"
//				"li t0, 995\n"
//				"bne a5, t0, reg3_err\n"
//				"li t0, 996\n"
//				"bne a6, t0, reg3_err\n"
//				"li t0, 997\n"
//				"bne a7, t0, reg3_err\n"
//				"j reg3_passed\n"
//
//				"reg3_err:\n"
//				"j reg3_err\n"
//		// 4.
//				"reg3_passed:\n"
//				"la t0, ulRegisterTest3Counter  # Load address of ulRegisterTest3Counter into t0\n"
//				"lw t1, 0(t0)                   # Load the value of ulRegisterTest3Counter into t1\n"
//				"addi t1, t1, 1                 # Increment t1 by 1\n"
//				"sw t1, 0(t0)                   # Store the updated value back to ulRegisterTest3Counter\n"
//		);
//	}
//}
/*-----------------------------------------------------------*/

//static void prvRegisterTest4Task( void *pvParameters )
//{
//	( void ) pvParameters;
//
//	for( ; ; )
//	{
//		/* 1. Fill the registers stored as part of task context with known values.
//		* 2. Force a context switch.
//		* 3. Verify that all the registers contain expected values.
//		* 4. If all the register contain expected values, increment ulRegisterTest3Counter.
//		*/
//
//		// 1.
//		asm volatile (
//				"li a1, 111\n"
//				"li a2, 112\n"
//				"li a3, 113\n"
//				"li a4, 114\n"
//				"li a5, 115\n"
//				"li a6, 116\n"
//				"li a7, 117\n"
//		);
//
//		// 2.
//		vTaskDelay(0);
//
//		// 3.
//		asm volatile (
//				"li t0, 111\n"
//				"bne a1, t0, reg4_err\n"
//				"li t0, 112\n"
//				"bne a2, t0, reg4_err\n"
//				"li t0, 113\n"
//				"bne a3, t0, reg4_err\n"
//				"li t0, 114\n"
//				"bne a4, t0, reg4_err\n"
//				"li t0, 115\n"
//				"bne a5, t0, reg4_err\n"
//				"li t0, 116\n"
//				"bne a6, t0, reg4_err\n"
//				"li t0, 117\n"
//				"bne a7, t0, reg4_err\n"
//				"j reg4_passed\n"
//
//				"reg4_err:\n"
//				"j reg4_err\n"
//		// 4.
//				"reg4_passed:\n"
//				"la t0, ulRegisterTest4Counter  # Load address of ulRegisterTest4Counter into t0\n"
//				"lw t1, 0(t0)                   # Load the value of ulRegisterTest4Counter into t1\n"
//				"addi t1, t1, 1                 # Increment t1 by 1\n"
//				"sw t1, 0(t0)                   # Store the updated value back to ulRegisterTest4Counter\n"
//		);
//	}
//}
/*-----------------------------------------------------------*/

void vStartRegisterTasks( UBaseType_t uxPriority )
{
	BaseType_t ret;

	ret = xTaskCreate( prvRegisterTest1Task, "RegTest1", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
	configASSERT( ret == pdPASS );

	ret = xTaskCreate( prvRegisterTest2Task, "RegTest2", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
	configASSERT( ret == pdPASS );

//	ret = xTaskCreate( prvRegisterTest3Task, "RegTest3", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
//	configASSERT( ret == pdPASS );
//
//	ret = xTaskCreate( prvRegisterTest4Task, "RegTest4", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
//	configASSERT( ret == pdPASS );
}
/*-----------------------------------------------------------*/

BaseType_t xAreRegisterTasksStillRunning( void )
{
static uint32_t ulLastRegisterTest1Counter = 0, ulLastRegisterTest2Counter = 0;
//static uint32_t ulLastRegisterTest3Counter = 0, ulLastRegisterTest4Counter = 0;

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

//	if( ulLastRegisterTest3Counter == ulRegisterTest3Counter )
//	{
//		xErrorDetected = pdTRUE;
//	}
//
//	if( ulLastRegisterTest4Counter == ulRegisterTest4Counter )
//	{
//		xErrorDetected = pdTRUE;
//	}

	ulLastRegisterTest1Counter = ulRegisterTest1Counter;
	ulLastRegisterTest2Counter = ulRegisterTest2Counter;
//	ulLastRegisterTest3Counter = ulRegisterTest3Counter;
//	ulLastRegisterTest4Counter = ulRegisterTest4Counter;

	/* Errors detected in the task itself will have latched xErrorDetected
	 * to true. */
	return ( BaseType_t ) !xErrorDetected;
}
/*-----------------------------------------------------------*/
