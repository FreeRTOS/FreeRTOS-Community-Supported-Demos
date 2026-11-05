/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*
 * Board and port defaults. Each application has an app_config.h with its
 * own needs (heap, INCLUDE_ options, hooks, features); its values win.
 */
#include "app_config.h"

/* Exit codes of the failure hooks (config/freertos_hooks.c) */
#define configFAIL_ASSERT            10
#define configFAIL_STACK_OVERFLOW    11
#define configFAIL_MALLOC            12

/* Tasks use the FPU; set by CMake from RH850_FLOAT */
#ifndef configENABLE_FPU
    #define configENABLE_FPU    1
#endif

#ifndef configTICK_RATE_HZ
    #define configTICK_RATE_HZ                       1000
#endif
#ifndef configUSE_PREEMPTION
    #define configUSE_PREEMPTION                     1
#endif
#ifndef configUSE_TIME_SLICING
    #define configUSE_TIME_SLICING                   1
#endif
#ifndef configUSE_TICKLESS_IDLE
    #define configUSE_TICKLESS_IDLE                  0
#endif
#define configUSE_PORT_OPTIMISED_TASK_SELECTION      0
#ifndef configMAX_PRIORITIES
    #define configMAX_PRIORITIES                     8
#endif
#ifndef configMINIMAL_STACK_SIZE
    #define configMINIMAL_STACK_SIZE                 256
#endif
#define configMAX_TASK_NAME_LEN                      12
#define configTICK_TYPE_WIDTH_IN_BITS                TICK_TYPE_WIDTH_32_BITS
#define configIDLE_SHOULD_YIELD                      1
#ifndef configTASK_NOTIFICATION_ARRAY_ENTRIES
    #define configTASK_NOTIFICATION_ARRAY_ENTRIES    1
#endif

#define configUSE_MUTEXES                            1
#define configUSE_RECURSIVE_MUTEXES                  1
#define configUSE_COUNTING_SEMAPHORES                1
#ifndef configUSE_QUEUE_SETS
    #define configUSE_QUEUE_SETS                     0
#endif
#ifndef configQUEUE_REGISTRY_SIZE
    #define configQUEUE_REGISTRY_SIZE                0
#endif
#ifndef configUSE_TRACE_FACILITY
    #define configUSE_TRACE_FACILITY                 0
#endif

#define configSUPPORT_DYNAMIC_ALLOCATION             1
#define configSUPPORT_STATIC_ALLOCATION              1
#define configKERNEL_PROVIDED_STATIC_MEMORY          1
/* heap_4 array defined in config/freertos_hooks.c */
#define configAPPLICATION_ALLOCATED_HEAP             1
#ifndef configTOTAL_HEAP_SIZE
    #define configTOTAL_HEAP_SIZE                    ( 16 * 1024 )
#endif
/* 1: heap in RAM_LARGE (cluster RAM on U2C8), 0: local RAM */
#ifndef RH850_HEAP_IN_LARGE_RAM
    #define RH850_HEAP_IN_LARGE_RAM     0
#endif

#define configUSE_TIMERS                1
#define configTIMER_TASK_PRIORITY       ( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH        10
#define configTIMER_TASK_STACK_DEPTH    configMINIMAL_STACK_SIZE

/* Idle halts the CPU (freertos_hooks.c); the tick hook is weak there */
#ifndef configUSE_IDLE_HOOK
    #define configUSE_IDLE_HOOK            1
#endif
#ifndef configUSE_TICK_HOOK
    #define configUSE_TICK_HOOK            0
#endif
#define configUSE_MALLOC_FAILED_HOOK       1
#define configCHECK_FOR_STACK_OVERFLOW     2

/* Lowest INTC priority (EICn.EIP 15) for the tick */
#define configKERNEL_INTERRUPT_PRIORITY    15

/*
 * A PLM value: priorities 4-15 are masked in critical sections and may
 * call FromISR APIs; priorities 0-3 are never masked and must not.
 */
#ifndef configMAX_SYSCALL_INTERRUPT_PRIORITY
    #define configMAX_SYSCALL_INTERRUPT_PRIORITY    4
#endif
/* Interrupts run on their own stack */
#ifndef configISR_STACK_SIZE_WORDS
    #define configISR_STACK_SIZE_WORDS    192
#endif

/* Used by the port or the board glue in every application */
#define INCLUDE_vTaskDelay                   1
#define INCLUDE_xTaskGetSchedulerState       1
#define INCLUDE_xTaskGetCurrentTaskHandle    1
#ifndef INCLUDE_vTaskDelayUntil
    #define INCLUDE_vTaskDelayUntil          1
#endif
#ifndef INCLUDE_vTaskDelete
    #define INCLUDE_vTaskDelete              1
#endif
#ifndef INCLUDE_vTaskSuspend
    #define INCLUDE_vTaskSuspend             1
#endif

#ifndef __ASSEMBLER__
    void vAssertCalled( const char * file,
                        int line );
    #define configASSERT( x )                    \
    do {                                         \
        if( !( x ) ) {                           \
            vAssertCalled( __FILE__, __LINE__ ); \
        }                                        \
    } while( 0 )
#endif

#endif /* FREERTOS_CONFIG_H */
