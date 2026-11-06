/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

/* FreeRTOS port hooks of this board: tick timer and EIINT dispatch */

#include <stddef.h>
#include "FreeRTOS.h"
#include "board.h"
#include "rh850_intc.h"
#include "rh850_ostm.h"

static void tick_isr( void * arg )
{
    ( void ) arg;
    vPortTickHandler();
}

#if ( configUSE_TICKLESS_IDLE == 1 )
/* Tickless: OSTM0 free-run compare; the port sets each compare */
    const uint32_t ulPortTickTimerCyclesPerTick = BOARD_TIMER_CLK_HZ / configTICK_RATE_HZ;

    void vPortSetupTimerInterrupt( void )
    {
        rh850_intc_connect( BOARD_TICK_IRQ, tick_isr, NULL );
        rh850_intc_set_priority( BOARD_TICK_IRQ, configKERNEL_INTERRUPT_PRIORITY );
        rh850_intc_enable( BOARD_TICK_IRQ );
        rh850_ostm_start_freerun( BOARD_TICK_OSTM_BASE, true );
    }

    uint32_t ulPortTickTimerCount( void )
    {
        return rh850_ostm_count( BOARD_TICK_OSTM_BASE );
    }

/*
 * A compare the counter has already passed would wait for a whole wrap
 * (U2C HW UM Table 32.19 p4343), so raise the request in the INTC then.
 */
    void vPortTickTimerSetCompare( uint32_t ulCompare )
    {
        rh850_ostm_set_compare( BOARD_TICK_OSTM_BASE, ulCompare );

        if( ( int32_t ) ( rh850_ostm_count( BOARD_TICK_OSTM_BASE ) - ulCompare ) >= 0 )
        {
            rh850_intc_raise( BOARD_TICK_IRQ );
        }
    }

    void vPortTickTimerClearPending( void )
    {
        rh850_intc_clear( BOARD_TICK_IRQ );
    }
#else /* if ( configUSE_TICKLESS_IDLE == 1 ) */
/* Periodic tick: OSTM0 interval mode */
    void vPortSetupTimerInterrupt( void )
    {
        rh850_intc_connect( BOARD_TICK_IRQ, tick_isr, NULL );
        rh850_intc_set_priority( BOARD_TICK_IRQ, configKERNEL_INTERRUPT_PRIORITY );
        rh850_intc_enable( BOARD_TICK_IRQ );
        rh850_ostm_start_interval( BOARD_TICK_OSTM_BASE,
                                   BOARD_TIMER_CLK_HZ / configTICK_RATE_HZ - 1U, true );
    }
#endif /* if ( configUSE_TICKLESS_IDLE == 1 ) */

void vApplicationIRQHandler( uint32_t ulEIIC )
{
    rh850_intc_dispatch( ulEIIC );
}
