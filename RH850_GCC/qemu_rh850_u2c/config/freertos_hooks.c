/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

/* Idle and tick hooks; failure hooks report and end with a distinct code */

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "rh850_board.h"

/* heap_4 memory (configAPPLICATION_ALLOCATED_HEAP), local or large RAM */
#if RH850_HEAP_IN_LARGE_RAM
    uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] RH850_LARGE_BSS __attribute__( ( aligned( 8 ) ) );
#else
    uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] __attribute__( ( aligned( 8 ) ) );
#endif

void vAssertCalled( const char * file,
                    int line )
{
    portDISABLE_INTERRUPTS();
    printf( "ASSERT %s:%d\n", file, line );
    board_exit( configFAIL_ASSERT );
}

void vApplicationStackOverflowHook( TaskHandle_t task,
                                    char * name )
{
    ( void ) task;
    portDISABLE_INTERRUPTS();
    printf( "STACK OVERFLOW %s\n", name );
    board_exit( configFAIL_STACK_OVERFLOW );
}

void vApplicationMallocFailedHook( void )
{
    portDISABLE_INTERRUPTS();
    printf( "MALLOC FAILED\n" );
    board_exit( configFAIL_MALLOC );
}

/*
 * Halt until the next interrupt, so the host is idle too. With tickless
 * idle the port halts in vPortSuppressTicksAndSleep instead.
 */
void vApplicationIdleHook( void )
{
    #if ( configUSE_TICKLESS_IDLE == 0 )
        rh850_halt();
    #endif
}

/* Tests that need the tick hook provide their own */
__attribute__( ( weak ) ) void vApplicationTickHook( void )
{
}
