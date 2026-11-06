/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

/*
 * picolibc locks on FreeRTOS recursive mutexes. Skipped before the scheduler,
 * in ISRs and with interrupts masked, so fault and early output still print.
 */

#include <stdint.h>
#include <sys/lock.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#define LIBC_LOCKS    4

struct __lock
{
    StaticSemaphore_t buf;
    SemaphoreHandle_t mutex;
};

struct __lock __lock___libc_recursive_mutex;

static struct __lock lock_pool[ LIBC_LOCKS ];
static unsigned int lock_used;

static int lock_usable( void )
{
    return ( xTaskGetSchedulerState() == taskSCHEDULER_RUNNING ) &&
           ( xPortIsInsideInterrupt() == pdFALSE ) &&
           ( RH850_STSR( RH850_CORE_MASK_SR ) == RH850_CORE_MASK_NONE ) &&
           ( ( RH850_STSR( RH850_SR_PSW ) & RH850_PSW_ID ) == 0U );
}

static SemaphoreHandle_t lock_mutex( struct __lock * lock )
{
    if( lock->mutex == NULL )
    {
        taskENTER_CRITICAL();

        if( lock->mutex == NULL )
        {
            lock->mutex = xSemaphoreCreateRecursiveMutexStatic( &lock->buf );
        }

        taskEXIT_CRITICAL();
    }

    return lock->mutex;
}

void __retarget_lock_init_recursive( _LOCK_T * lock )
{
    taskENTER_CRITICAL();
    configASSERT( lock_used < LIBC_LOCKS );
    *lock = &lock_pool[ lock_used++ ];
    taskEXIT_CRITICAL();
}

void __retarget_lock_init( _LOCK_T * lock )
{
    __retarget_lock_init_recursive( lock );
}

void __retarget_lock_close_recursive( _LOCK_T lock )
{
    /* Pool entries are not reused */
    ( void ) lock;
}

void __retarget_lock_close( _LOCK_T lock )
{
    ( void ) lock;
}

void __retarget_lock_acquire_recursive( _LOCK_T lock )
{
    if( lock_usable() )
    {
        ( void ) xSemaphoreTakeRecursive( lock_mutex( lock ), portMAX_DELAY );
    }
}

void __retarget_lock_acquire( _LOCK_T lock )
{
    __retarget_lock_acquire_recursive( lock );
}

void __retarget_lock_release_recursive( _LOCK_T lock )
{
    if( lock_usable() )
    {
        ( void ) xSemaphoreGiveRecursive( lock_mutex( lock ) );
    }
}

void __retarget_lock_release( _LOCK_T lock )
{
    __retarget_lock_release_recursive( lock );
}
