/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

/*
 * Template RegTests.h for RH850: the four tasks are regtest_gcc.S. They
 * count rounds in ulRegTestCounter and call vRegTestFail on corruption.
 */

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "RegTests.h"
#include "rh850_board.h"

#define REGTESTS             4
/* Exit code for corruption in register test task n: base + n */
#define REGTEST_FAIL_BASE    50

void vRegTest1Task( void * arg );
void vRegTest2Task( void * arg );
void vRegTest3Task( void * arg );
void vRegTest4Task( void * arg );
void vRegTestFail( uint32_t task );

volatile uint32_t ulRegTestCounter[ REGTESTS ];

void vRegTestFail( uint32_t task )
{
    portDISABLE_INTERRUPTS();
    printf( "RegTest%lu: register corrupted\n", ( unsigned long ) task );
    board_exit( REGTEST_FAIL_BASE + ( int ) task );
}

void vStartRegisterTasks( UBaseType_t uxPriority )
{
    static TaskFunction_t const tasks[ REGTESTS ] =
    {
        vRegTest1Task, vRegTest2Task, vRegTest3Task, vRegTest4Task
    };
    static const char * const names[ REGTESTS ] =
    {
        "RegTest1", "RegTest2", "RegTest3", "RegTest4"
    };

    for( int i = 0; i < REGTESTS; i++ )
    {
        BaseType_t ret = xTaskCreate( tasks[ i ], names[ i ], configMINIMAL_STACK_SIZE, NULL,
                                      uxPriority, NULL );

        configASSERT( ret == pdPASS );
    }
}

/* Every counter must have moved since the last call */
BaseType_t xAreRegisterTasksStillRunning( void )
{
    static uint32_t last[ REGTESTS ];
    BaseType_t ok = pdTRUE;

    for( int i = 0; i < REGTESTS; i++ )
    {
        uint32_t now = ulRegTestCounter[ i ];

        if( now == last[ i ] )
        {
            ok = pdFALSE;
        }

        last[ i ] = now;
    }

    return ok;
}
