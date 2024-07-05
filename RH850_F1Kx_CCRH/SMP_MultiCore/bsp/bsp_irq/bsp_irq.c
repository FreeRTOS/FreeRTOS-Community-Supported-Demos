#include "bsp_common.h"
#include "FreeRTOS.h"

extern irq_vector_t g_vector_table_PE1[ RTOS_VECTOR_TABLE_MAX_ENTRIES ];
extern irq_vector_t g_vector_table_PE2[ RTOS_VECTOR_TABLE_MAX_ENTRIES ];


void vCommonISRHandler( int irq )
{
    if( portGET_CORE_ID() == 0 )
    {
        g_vector_table_PE1[ irq ]();
    }
    else if( portGET_CORE_ID() == 1 )
    {
        g_vector_table_PE2[ irq ]();
    }
}
