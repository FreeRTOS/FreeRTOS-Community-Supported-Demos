/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

/*
 * IntQueue needs two API-safe interrupts, one nesting the other: the tick
 * (prio 15) and OSTM1 at prio 8, above it (ISPR, U2C HW UM Table 3.44 p237).
 */

#include <stddef.h>
#include "FreeRTOS.h"
#include "task.h"
#include "IntQueueTimer.h"
#include "IntQueue.h"
#include "board.h"
#include "rh850_intc.h"
#include "rh850_ostm.h"

#define tmrINTQ_PRIORITY     8
/* 2 kHz with one clock more per period, so it drifts against the tick */
#define tmrINTQ_FREQUENCY    2000U

_Static_assert( tmrINTQ_PRIORITY >= configMAX_SYSCALL_INTERRUPT_PRIORITY,
                "the IntQueue timer calls the API" );
_Static_assert( tmrINTQ_PRIORITY < configKERNEL_INTERRUPT_PRIORITY,
                "the IntQueue timer must nest the tick" );

static void prvTimerIsr( void * arg )
{
    ( void ) arg;
    IntQueueTestTimerHandler();
}

void vInitialiseTimerForIntQueueTest( void )
{
    rh850_intc_connect( BOARD_TIMER2_IRQ, prvTimerIsr, NULL );
    rh850_intc_set_priority( BOARD_TIMER2_IRQ, tmrINTQ_PRIORITY );
    rh850_intc_enable( BOARD_TIMER2_IRQ );
    /* Interval mode: period CMP + 1 clocks (U2C HW UM 32.4.2 p4337) */
    rh850_ostm_start_interval( BOARD_TIMER2_OSTM_BASE, BOARD_TIMER_CLK_HZ / tmrINTQ_FREQUENCY,
                               true );
}

void IntQueueTestTimerHandler( void )
{
    portYIELD_FROM_ISR( xSecondTimerHandler() );
}
