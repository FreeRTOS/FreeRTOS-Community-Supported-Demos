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

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/
/* Constants related to the behaviour or the scheduler. */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION  0
#define configTICK_RATE_HZ                  ( ( portTickType ) 1000 )
#define configUSE_PREEMPTION                1
#define configUSE_TIME_SLICING              1
#define configMAX_PRIORITIES                16
#define configIDLE_SHOULD_YIELD             1
#define configUSE_16_BIT_TICKS              0 /* Only for 8 and 16-bit hardware. */

/* Constants used to specify if only static allocation is to be supported (in
which case a heap_n.c file is not required), only dynamic allocation is to be
supported, or if both static and dynamic allocation are supported. */
#define configSUPPORT_STATIC_ALLOCATION         1
#define configSUPPORT_DYNAMIC_ALLOCATION        1
//#define configAPPLICATION_ALLOCATED_HEAP        1

/* Constants that describe the hardware and memory usage. */
#define configCPU_CLOCK_HZ                  ( ( unsigned long ) 200000000 )
#define configMINIMAL_STACK_SIZE                ( ( uint16_t ) 256 )
#define configMAX_TASK_NAME_LEN                 ( 12 )

/* Note heap_5.c is used so this only defines the part of the heap that is in
the first block of RAM on the LPC device.  See the initialisation of the heap
in main.c. */
#define configTOTAL_HEAP_SIZE                   ( ( size_t ) ( 32000 ) )

/* Constants that build features in or out. */
#define configUSE_MUTEXES                       1
#define configUSE_TICKLESS_IDLE                 0
#define configUSE_APPLICATION_TASK_TAG          0
#define configUSE_NEWLIB_REENTRANT              0
#define configUSE_CO_ROUTINES                   0
#define configMAX_CO_ROUTINE_PRIORITIES     ( 2 )
#define configUSE_COUNTING_SEMAPHORES           1
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_QUEUE_SETS                    1
#define configUSE_TASK_NOTIFICATIONS            1

/* Constants that define which hook (callback) functions should be used. */
#define configUSE_IDLE_HOOK                     1
#define configUSE_TICK_HOOK                     1
#define configUSE_MALLOC_FAILED_HOOK            1

/* Constants provided for debugging and optimisation assistance. */
#define configCHECK_FOR_STACK_OVERFLOW          2
void vMainAssertCalled( const char *pcFileName, uint32_t ulLineNumber );
#define configASSERT( x ) if( ( x ) == 0 ) { vMainAssertCalled( __FILE__, __LINE__ ); }
#define configQUEUE_REGISTRY_SIZE               10

/* Software timer definitions. */
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               ( 3 )
#define configTIMER_QUEUE_LENGTH                5
#define configTIMER_TASK_STACK_DEPTH            ( configMINIMAL_STACK_SIZE  )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function.  NOTE:  Setting an INCLUDE_ parameter to 0 is only
necessary if the linker does not automatically remove functions that are not
referenced anyway. */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskCleanUpResources           0
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_uxTaskGetStackHighWaterMark     0
#define INCLUDE_xTaskGetIdleTaskHandle          0
#define INCLUDE_xTaskGetHandle                  1
#define INCLUDE_eTaskGetState                   1
#define INCLUDE_xTaskResumeFromISR              0
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_xTaskGetSchedulerState          0
#define INCLUDE_xSemaphoreGetMutexHolder        1
#define INCLUDE_xTimerPendFunctionCall          1

//
// Adding for test project
//
#define INCLUDE_xTaskAbortDelay                 1

/* This demo makes use of one or more example stats formatting functions.  These
format the raw data provided by the uxTaskGetSystemState() function in to human
readable ASCII form.  See the notes in the implementation of vTaskList() within
FreeRTOS/Source/tasks.c for limitations. */
#define configUSE_STATS_FORMATTING_FUNCTIONS    1

/* Dimensions a buffer that can be used by the FreeRTOS+CLI command
interpreter.  See the FreeRTOS+CLI documentation for more information:
http://www.FreeRTOS.org/FreeRTOS-Plus/FreeRTOS_Plus_CLI/ */
#define configCOMMAND_INT_MAX_OUTPUT_SIZE       2048

/* The trace facility is turned on to make some functions available for use in
CLI commands. */
#define configUSE_TRACE_FACILITY            1

/* Constants related to the generation of run time stats. */
#define configGENERATE_RUN_TIME_STATS           0
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()
#define portGET_RUN_TIME_COUNTER_VALUE()        0

/* The test that checks the trigger level on stream buffers requires an
allowable margin of error on slower processors (slower than the Win32
machine on which the test is developed). */
#define configSTREAM_BUFFER_TRIGGER_LEVEL_TEST_MARGIN   4

#define configTASK_NOTIFICATION_ARRAY_ENTRIES 3
#define configPRINTF( X ) printf( X )

// Minimal Test related configuration
#define TESTGROUP      2                     // Selects appropriate test group
#if(TESTGROUP == 1)
#define configSTART_TASK_NOTIFY_TESTS             1
#define configSTART_TASK_NOTIFY_ARRAY_TESTS       1
#define configSTART_BLOCKING_QUEUE_TESTS          1
#define configSTART_SEMAPHORE_TESTS               1
#define configSTART_POLLED_QUEUE_TESTS            1
#define configSTART_INTEGER_MATH_TESTS            1
#define configSTART_GENERIC_QUEUE_TESTS           1
#define configSTART_PEEK_QUEUE_TESTS              1
#define configSTART_MATH_TESTS                    1
#elif(TESTGROUP == 2)
#define configSTART_RECURSIVE_MUTEX_TESTS         1
#define configSTART_COUNTING_SEMAPHORE_TESTS      1
#define configSTART_QUEUE_SET_TESTS               1
#define configSTART_QUEUE_OVERWRITE_TESTS         1
#define configSTART_EVENT_GROUP_TESTS             1
#define configSTART_INTERRUPT_SEMAPHORE_TESTS     1
#define configSTART_QUEUE_SET_POLLING_TESTS       1
#define configSTART_BLOCK_TIME_TESTS              1
#define configSTART_ABORT_DELAY_TESTS             1
#define configSTART_MESSAGE_BUFFER_TESTS          1
#define configSTART_STREAM_BUFFER_TESTS           1
#define configSTART_STREAM_BUFFER_INTERRUPT_TESTS 1
#define configSTART_TIMER_TESTS                   1
#define configSTART_INTERRUPT_QUEUE_TESTS         0
#define configSTART_REGISTER_TESTS                1
#define configSTART_DELETE_SELF_TESTS             1
#endif
#endif /* FREERTOS_CONFIG_H */

