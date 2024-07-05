#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "bsp_common.h"
#include "FreeRTOS.h"
#include "TestRunner.h"

/*
 * Generate Blinky Test only or run full test
 */
/*#define appRUN_BLINKY	1 */

int main( void );

static int gBarrierAddress[ 2 ] = { 0 };
int main( void )
{
    /* Inform completion to PE2 and wait for PE2 initialization complete */
    gBarrierAddress[ 0 ] = 1;

    while( gBarrierAddress[ 1 ] )
    {
    }

    gBarrierAddress[ 0 ] = 0;
    volatile uint32_t * pIPIRRegAddr;
    pIPIRRegAddr = ( volatile uint32_t * ) 0xFFFEEA00;
    *pIPIRRegAddr = 0x0f;

    #if appRUN_BLINKY
    {
        main_blinky();
    }
    #else
    {
        vStartTests();
    }
    #endif
    return 0;
}

#if ( configNUMBER_OF_CORES > 1 )
    int main_PE2( void )
    {
        /* Inform completion to PE1 and wait for PE1 initialization complete */
        gBarrierAddress[ 1 ] = 1;

        while( gBarrierAddress[ 0 ] )
        {
        }

        gBarrierAddress[ 1 ] = 0;
        volatile uint32_t * pIPIRRegAddr;

        bsp_clock_init();

        /* Configure interrupt for IPIR interrupt in secondary core to receive request from primary core
         * Primary core is the core which start scheduler.
         */
        pIPIRRegAddr = ( volatile uint32_t * ) 0xFFFEEA00;
        *pIPIRRegAddr = 0x0f;

/*	setup_TAUD_CH2_FOR_PE2(); */

        /* The interrupt may be disabled by default. Just enable it */
        EI();

        /* Do nothing. Loop to keep PE2 run */
        while( 1 )
        {
        }
    }
#endif /* (configNUMBER_OF_CORES > 1) */


void vTaskAssert( char file[],
                  uint32_t line )
{
    ( void ) file;
    ( void ) line;
    DI();

    while( 1 )
    {
        __nop();
    }
}

int printf( const char * format,
            ... )
{
    char tx_buff[ 100 ];
    va_list arg;

    va_start( arg, format );
    vsprintf( tx_buff, format, arg );
    va_end( arg );

    /* Put your transmit function here */
    NOP();

    memset( tx_buff, 0, 100 );
    return 0;
}


void vDummyISR( void )
{
    while( 1 )
    {
    }
}
