#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bsp_common.h"
#include "FreeRTOS.h"
#include "TestRunner.h"


int main( void );


int main( void )
{
    bsp_clock_init();
    printf( "Start of program\r\n" );
    vStartTests();

    return 0;
}

#if ( configNUMBER_OF_CORES > 1 )
    int main_PE2( void )
    {
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
