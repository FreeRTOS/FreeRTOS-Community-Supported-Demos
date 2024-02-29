#include "bsp_common.h"

extern irq_vector_t g_vector_table[BSP_VECTOR_TABLE_MAX_ENTRIES];

void bsp_common_interrupt_handler (uint32_t id)
{
    g_vector_table[id]();
}
