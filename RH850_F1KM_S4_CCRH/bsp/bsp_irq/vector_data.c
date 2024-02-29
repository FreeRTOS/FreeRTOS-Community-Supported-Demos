#include "bsp_common.h"

const irq_vector_t g_vector_table[BSP_VECTOR_TABLE_MAX_ENTRIES] =
{
    [48] = TAUD0I1_Handler,
    [49] = TAUD0I3_Handler,
    [84] = vPortTickISR
};
