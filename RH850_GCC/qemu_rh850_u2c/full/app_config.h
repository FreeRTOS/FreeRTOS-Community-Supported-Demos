/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef APP_CONFIG_H
#define APP_CONFIG_H

/*
 * Full demo: every Template test. The check task output goes through
 * vFullDemoPrintf (main.c), which ends the run.
 */

/* Heap: 110936 bytes at peak + 25 %, too big for local RAM */
#define configTOTAL_HEAP_SIZE                    ( 136 * 1024 )
#define RH850_HEAP_IN_LARGE_RAM                  1

#define configUSE_TICK_HOOK                      1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES    3
#define configUSE_QUEUE_SETS                     1
#define configQUEUE_REGISTRY_SIZE                8
/* uxTaskGetSystemState and stack bounds for the stack report */
#define configUSE_TRACE_FACILITY                 1
#define configRECORD_STACK_HIGH_ADDRESS          1

#define INCLUDE_uxTaskPriorityGet                1
#define INCLUDE_uxTaskGetStackHighWaterMark      1
#define INCLUDE_vTaskPrioritySet                 1
#define INCLUDE_eTaskGetState                    1
#define INCLUDE_xTaskAbortDelay                  1
#define INCLUDE_xTaskGetHandle                   1
#define INCLUDE_xTaskGetIdleTaskHandle           1
#define INCLUDE_xTaskResumeFromISR               1
#define INCLUDE_xTimerPendFunctionCall           1
#define INCLUDE_xSemaphoreGetMutexHolder         1

#ifndef __ASSEMBLER__
    void vFullDemoPrintf( const char * fmt,
                          ... );
#endif
#define configPRINTF( X )    vFullDemoPrintf X

#define configSTART_TASK_NOTIFY_TESTS                1
#define configSTART_TASK_NOTIFY_ARRAY_TESTS          1
#define configSTART_BLOCKING_QUEUE_TESTS             1
#define configSTART_SEMAPHORE_TESTS                  1
#define configSTART_POLLED_QUEUE_TESTS               1
#define configSTART_INTEGER_MATH_TESTS               1
#define configSTART_GENERIC_QUEUE_TESTS              1
#define configSTART_PEEK_QUEUE_TESTS                 1
#define configSTART_MATH_TESTS                       1
#define configSTART_RECURSIVE_MUTEX_TESTS            1
#define configSTART_COUNTING_SEMAPHORE_TESTS         1
#define configSTART_QUEUE_SET_TESTS                  1
#define configSTART_QUEUE_OVERWRITE_TESTS            1
#define configSTART_EVENT_GROUP_TESTS                1
#define configSTART_INTERRUPT_SEMAPHORE_TESTS        1
#define configSTART_QUEUE_SET_POLLING_TESTS          1
#define configSTART_BLOCK_TIME_TESTS                 1
#define configSTART_ABORT_DELAY_TESTS                1
#define configSTART_MESSAGE_BUFFER_TESTS             1
#define configSTART_STREAM_BUFFER_TESTS              1
#define configSTART_STREAM_BUFFER_INTERRUPT_TESTS    1
#define configSTART_TIMER_TESTS                      1
#define configSTART_INTERRUPT_QUEUE_TESTS            1
#define configSTART_REGISTER_TESTS                   1
#define configSTART_DELETE_SELF_TESTS                1

#endif /* APP_CONFIG_H */
