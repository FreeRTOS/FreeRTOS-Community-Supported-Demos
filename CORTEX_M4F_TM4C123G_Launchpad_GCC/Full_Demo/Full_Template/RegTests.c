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

		/* 1. Fill the registers stored as part of task context with known values.
		* 4. If all the register contain expected values, increment ulRegisterTest1Counter.
		*/
    
	__asm volatile
	(
		".extern ulRegisterTest1Counter \n"
		"/* Fill the core registers with known values. */		\n"
		"mov	r0, #100			\n"
		"mov	r1, #101			\n"
		"mov	r2, #102			\n"
		"mov	r3, #103			\n"
		"mov	r4, #104			\n"
		"mov	r5, #105			\n"
		"mov	r6, #106			\n"
		"mov	r7, #107			\n"
		"mov	r8, #108			\n"
		"mov	r9, #109			\n"
		"mov	r10, #110			\n"
		"mov	r11, #111			\n"
		"mov	r12, #112			\n"
    );
	/* 2. Force a context switch.*/
    //vTaskDelay(0); 
		
    /* 3. Verify that all the registers contain expected values.*/
    __asm volatile
	(
	"reg1_loop:						\n"
		"cmp	r0, #100			\n"
		"bne	reg1_error_loop		\n"
		"cmp	r1, #101			\n"
		"bne	reg1_error_loop		\n"
		"cmp	r2, #102			\n"
		"bne	reg1_error_loop		\n"
		"cmp 	r3, #103			\n"
		"bne	reg1_error_loop		\n"
		"cmp	r4, #104			\n"
		"bne	reg1_error_loop		\n"
		"cmp	r5, #105			\n"
		"bne	reg1_error_loop		\n"
		"cmp	r6, #106			\n"
		"bne	reg1_error_loop		\n"
		"cmp	r7, #107			\n"
		"bne	reg1_error_loop		\n"
		"cmp	r8, #108			\n"
		"bne	reg1_error_loop		\n"
		"cmp	r9, #109			\n"
		"bne	reg1_error_loop		\n"
		"cmp	r10, #110			\n"
		"bne	reg1_error_loop		\n"
		"cmp	r11, #111			\n"
		"bne	reg1_error_loop		\n"
		"cmp	r12, #112			\n"
		"bne	reg1_error_loop		\n"

		"/* Everything passed, increment the loop counter. */	\n"
		"push 	{ r0-r1 }			\n"
		"ldr	r0, =ulRegisterTest1Counter	\n"
		"ldr 	r1, [r0]			\n"
		"adds 	r1, r1, #1			\n"
		"str 	r1, [r0]			\n"
		"pop 	{ r0-r1 }			\n"

		"/* Start again. */			\n"
		"b 		reg1_loop			\n"

	"reg1_error_loop:				\n"
		"/* If this line is hit then there was an error in a core register value. \n"
		"The loop ensures the loop counter stops incrementing. */	\n"
		"b 	reg1_error_loop			\n"
		"nop						"
	); /* __asm volatile. */
}
/*-----------------------------------------------------------*/

static void prvRegisterTest2Task( void *pvParameters )
{
	( void ) pvParameters;
	
    __asm volatile
	(
		".extern ulRegisterTest2Counter \n"
		"/* Set all the core registers to known values. */	\n"
		"mov 	r0, #-1				\n"
		"mov 	r1, #1				\n"
		"mov 	r2, #2				\n"
		"mov 	r3, #3				\n"
		"mov	r4, #4				\n"
		"mov	r5, #5				\n"
		"mov	r6, #6				\n"
		"mov 	r7, #7				\n"
		"mov	r8, #8				\n"
		"mov	r9, #9				\n"
		"mov	r10, #10			\n"
		"mov	r11, #11			\n"
		"mov 	r12, #12			\n"
    );
    
    //vTaskDelay(0); 
    
    __asm volatile
	(
     "reg2_loop:						\n"
		"cmp	r0, #-1				\n"
		"bne	reg2_error_loop		\n"
		"cmp	r1, #1				\n"
		"bne	reg2_error_loop		\n"
		"cmp	r2, #2				\n"
		"bne	reg2_error_loop		\n"
		"cmp 	r3, #3				\n"
		"bne	reg2_error_loop		\n"
		"cmp	r4, #4				\n"
		"bne	reg2_error_loop		\n"
		"cmp	r5, #5				\n"
		"bne	reg2_error_loop		\n"
		"cmp	r6, #6				\n"
		"bne	reg2_error_loop		\n"
		"cmp	r7, #7				\n"
		"bne	reg2_error_loop		\n"
		"cmp	r8, #8				\n"
		"bne	reg2_error_loop		\n"
		"cmp	r9, #9				\n"
		"bne	reg2_error_loop		\n"
		"cmp	r10, #10			\n"
		"bne	reg2_error_loop		\n"
		"cmp	r11, #11			\n"
		"bne	reg2_error_loop		\n"
		"cmp	r12, #12			\n"
		"bne	reg2_error_loop		\n"

		"/* Increment the loop counter to indicate this test is still functioning	\n"
		"correctly. */				\n"
		"push	{ r0-r1 }			\n"
		"ldr	r0, =ulRegisterTest2Counter	\n"
		"ldr 	r1, [r0]			\n"
		"adds 	r1, r1, #1			\n"
		"str 	r1, [r0]			\n"

		"/* Yield to increase test coverage. */			\n"
		"movs 	r0, #0x01			\n"
		"ldr 	r1, =0xe000ed04 /*NVIC_INT_CTRL */		\n"
		"lsl 	r0, r0, #28 /* Shift to PendSV bit */	\n"
		"str 	r0, [r1]			\n"
		"dsb						\n"

		"pop { r0-r1 }				\n"

		"/* Start again. */			\n"
		"b reg2_loop				\n"

	"reg2_error_loop:				\n"
		"/* If this line is hit then there was an error in a core register value.	\n"
		"This loop ensures the loop counter variable stops incrementing. */			\n"
		"b reg2_error_loop			\n"
	); /* __asm volatile */
}

/*-----------------------------------------------------------*/

static void prvRegisterTest3Task( void *pvParameters )
{
	( void ) pvParameters;

	for( ; ; )
	{
		/* 1. Fill the registers stored as part of task context with known values.
		* 2. Force a context switch.
		* 3. Verify that all the registers contain expected values.
		* 4. If all the register contain expected values, increment ulRegisterTest3Counter.
		*/
	}
}
/*-----------------------------------------------------------*/

static void prvRegisterTest4Task( void *pvParameters )
{
	( void ) pvParameters;

	for( ; ; )
	{
		/* 1. Fill the registers stored as part of task context with known values.
		* 2. Force a context switch.
		* 3. Verify that all the registers contain expected values.
		* 4. If all the register contain expected values, increment ulRegisterTest4Counter.
		*/
	}
}
/*-----------------------------------------------------------*/

void vStartRegisterTasks( UBaseType_t uxPriority )
{
	BaseType_t ret;

	ret = xTaskCreate( prvRegisterTest1Task, "RegTest1", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
	configASSERT( ret == pdPASS );

	ret = xTaskCreate( prvRegisterTest2Task, "RegTest2", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
	configASSERT( ret == pdPASS );

    /*
	ret = xTaskCreate( prvRegisterTest3Task, "RegTest3", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
	configASSERT( ret == pdPASS );

	ret = xTaskCreate( prvRegisterTest4Task, "RegTest4", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
	configASSERT( ret == pdPASS );*/
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
    /*
	if( ulLastRegisterTest3Counter == ulRegisterTest3Counter )
	{
		xErrorDetected = pdTRUE;
	}

	if( ulLastRegisterTest4Counter == ulRegisterTest4Counter )
	{
		xErrorDetected = pdTRUE;
	}*/

	ulLastRegisterTest1Counter = ulRegisterTest1Counter;
	ulLastRegisterTest2Counter = ulRegisterTest2Counter;
	ulLastRegisterTest3Counter = ulRegisterTest3Counter;
	ulLastRegisterTest4Counter = ulRegisterTest4Counter;

	/* Errors detected in the task itself will have latched xErrorDetected
	 * to true. */
	return ( BaseType_t ) !xErrorDetected;
}
/*-----------------------------------------------------------*/
