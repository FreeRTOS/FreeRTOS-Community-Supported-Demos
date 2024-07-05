#include "bsp_common.h"
#include "FreeRTOSConfig.h"

typedef void (* int_vector_t)( void );

const irq_vector_t g_vector_table_PE1[ RTOS_VECTOR_TABLE_MAX_ENTRIES ] =
{
    #if ( configNUMBER_OF_CORES > 1 )
        [ 0 ] = vPortIPIHander, /* Internal processor interrupt 0 */
/*	[8]  = vCH0_TAUD0_Handler0, */
    #endif
/*    [48] = TAUD0I1_Handler, */
/*    [49] = TAUD0I3_Handler, */
    [ 84 ] = vPortTickISR, /* ICOSTM0 (OSTM0 interrupt) */
};

/* Vector table allocations */
const irq_vector_t g_vector_table_PE2[ RTOS_VECTOR_TABLE_MAX_ENTRIES ] =
{
    #if ( configNUMBER_OF_CORES > 1 )
        [ 0 ] = vPortIPIHander, /* Internal processor interrupt 0 */
/*	[9]  = vCH2_TAUD0_Handler2 */
    #else
        [ 0 ] = vDummyISR,
    #endif
};
