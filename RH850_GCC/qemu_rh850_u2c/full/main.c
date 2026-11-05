/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

/*
 * Every Template TestRunner test. The check task reports every 5 s through
 * vFullDemoPrintf: six "No errors" in a row pass, any error fails.
 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "TestRunner.h"
#include "rh850_board.h"

#define GOOD_CHECKS        6
#define MAX_TASKS          128
/* Exit code of an error string: base + its index; unknown strings: base + 30 */
#define FAIL_ERROR_BASE    70

/* The error strings of TestRunner.c, in its order */
static const char * const errors[] =
{
    "Error:  Notification",     "Error:  Notification Array", "Error: BlockQueue",
    "Error: SemTest",           "Error: PollQueue",           "Error: IntMath",                "Error: GenQueue",
    "Error: QueuePeek",         "Error: Flop",                "Error: RecMutex",               "Error: CountSem",
    "Error: Queue set",         "Error: Queue overwrite",     "Error: EventGroup",             "Error: IntSem",
    "Error: Queue set polling", "Error: Block time",          "Error: Abort delay",
    "Error:  MessageBuffer",    "Error:  StreamBuffer",       "Error: Stream buffer interrupt",
    "Error: TimerDemo",         "Error: IntQueue",            "Error: RegTests",               "Error: Death",
};

static TaskStatus_t status[ MAX_TASKS ];

/* Every task and the ISR stack must keep this share of its stack free */
#define MIN_FREE_PERCENT     25
#define FAIL_STACK_MARGIN    69

static int enough( uint32_t free_words,
                   uint32_t size_words )
{
    return free_words * 100U >= size_words * MIN_FREE_PERCENT;
}

static void stack_report( void )
{
    UBaseType_t n = uxTaskGetSystemState( status, MAX_TASKS, NULL );
    int ok = 1;

    printf( "full: %lu tasks, stack free/size (words) at the end:\n", ( unsigned long ) n );

    for( UBaseType_t i = 0; i < n; i++ )
    {
        uint32_t size = ( uint32_t ) ( status[ i ].pxEndOfStack - status[ i ].pxStackBase ) + 1U;
        uint32_t free_words = status[ i ].usStackHighWaterMark;

        printf( "  %-12s prio %lu free %lu/%lu (%lu %%)\n", status[ i ].pcTaskName,
                ( unsigned long ) status[ i ].uxCurrentPriority, ( unsigned long ) free_words,
                ( unsigned long ) size, ( unsigned long ) ( free_words * 100U / size ) );
        ok &= enough( free_words, size );
    }

    uint32_t isr_free = uxPortGetISRStackHighWaterMark();

    printf( "full: ISR stack free %lu/%u (%lu %%), heap free now %u min %u of %u bytes\n",
            ( unsigned long ) isr_free, ( unsigned int ) configISR_STACK_SIZE_WORDS,
            ( unsigned long ) ( isr_free * 100U / configISR_STACK_SIZE_WORDS ),
            ( unsigned int ) xPortGetFreeHeapSize(), ( unsigned int ) xPortGetMinimumEverFreeHeapSize(),
            ( unsigned int ) configTOTAL_HEAP_SIZE );
    ok &= enough( isr_free, configISR_STACK_SIZE_WORDS );

    if( !ok )
    {
        printf( "full FAIL: a stack has less than %d %% free\n", MIN_FREE_PERCENT );
        board_exit( FAIL_STACK_MARGIN );
    }
}

void vFullDemoPrintf( const char * fmt,
                      ... )
{
    static int good;
    va_list ap;

    va_start( ap, fmt );
    vprintf( fmt, ap );
    va_end( ap );

    /* Only the check task status line: "%s \r\n" with the status string */
    if( strcmp( fmt, "%s \r\n" ) != 0 )
    {
        return;
    }

    va_start( ap, fmt );
    const char * msg = va_arg( ap, const char * );
    va_end( ap );

    if( strcmp( msg, "No errors" ) == 0 )
    {
        if( ++good == GOOD_CHECKS )
        {
            stack_report();
            printf( "full pass\n" );
            board_exit( 0 );
        }

        return;
    }

    for( unsigned int i = 0; i < sizeof( errors ) / sizeof( errors[ 0 ] ); i++ )
    {
        if( strcmp( msg, errors[ i ] ) == 0 )
        {
            printf( "full FAIL: %s\n", msg );
            board_exit( FAIL_ERROR_BASE + ( int ) i );
        }
    }

    printf( "full FAIL: unknown status\n" );
    board_exit( FAIL_ERROR_BASE + 30 );
}

int main( void )
{
    board_init();
    printf( "full demo start (FPU %s)\n", configENABLE_FPU ? "on" : "off" );
    vStartTests();
    return 1;
}
