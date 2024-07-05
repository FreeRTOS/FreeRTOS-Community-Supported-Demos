#ifndef BSP_IRQ_VECTOR_DATA_H_
#define BSP_IRQ_VECTOR_DATA_H_


#define RTOS_VECTOR_TABLE_MAX_ENTRIES    ( 409 )


extern void vPortIPIHander( void );
extern void vPortTickISR( void );

extern void vDummyISR( void );


extern void TAUD0I1_Handler( void );
extern void TAUD0I3_Handler( void );

#endif /* BSP_IRQ_VECTOR_DATA_H_ */
