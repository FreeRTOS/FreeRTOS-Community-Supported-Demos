#ifndef COMMON_BSP_COMMON_H_
#define COMMON_COMMON_H_

#include <stdint.h>
#include "iodefine.h"
#include "bsp_compiler_support.h"
#include "bsp_macro.h"
#include "../bsp_clock/bsp_clock.h"
#include "../bsp_irq/bsp_irq.h"
#include "../bsp_irq/vector_data.h"


static inline int GetCoreID()
{
    return( ( __stsr_rh( 0, 2 ) >> 16 ) - 1 );
}
#endif /* COMMON_BSP_COMMON_H_ */
