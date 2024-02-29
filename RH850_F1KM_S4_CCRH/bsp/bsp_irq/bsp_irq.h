#ifndef BSP_IRQ_BSP_IRQ_H_
#define BSP_IRQ_BSP_IRQ_H_

#define BSP_FE_VECTOR_TABLE_ENTRIES     (32)
#define BSP_EIC_VECTOR_TABLE_ENTRIES    (377)
#define BSP_VECTOR_TABLE_MAX_ENTRIES    (409)

typedef void (* irq_vector_t)(void);

void bsp_common_interrupt_handler(uint32_t id);

#endif                                 /* BSP_IRQ_BSP_IRQ_H_ */
