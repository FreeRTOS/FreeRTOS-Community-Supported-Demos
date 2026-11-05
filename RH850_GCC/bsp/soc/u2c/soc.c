/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdint.h>
#include "rh850_io.h"
#include "soc.h"

/* Clear the module standby bit once no software module reset is active */
static void u2c_module_release( uintptr_t swmress,
                                uintptr_t msr,
                                uint32_t bit )
{
    while( ( rh850_read32( swmress ) & bit ) != 0U )
    {
    }

    rh850_write32( SOC_MSRKCPROT, SOC_KCPROT_ENABLE );
    rh850_write32( msr, rh850_read32( msr ) & ~bit );

    while( ( rh850_read32( msr ) & bit ) != 0U )
    {
    }

    rh850_write32( SOC_MSRKCPROT, SOC_KCPROT_DISABLE );
}

/* PLL and CPU clocks keep their reset settings */
void soc_init( void )
{
    rh850_write32( SOC_CLKKCPROT1, SOC_KCPROT_ENABLE );
    rh850_write32( SOC_CKS_RLINC, SOC_CKS_RLIN_HSB );

    while( ( rh850_read32( SOC_CKS_RLINS ) & 0x7U ) != SOC_CKS_RLIN_HSB )
    {
    }

    rh850_write32( SOC_CLKKCPROT1, SOC_KCPROT_DISABLE );

    u2c_module_release( SOC_SWMRESS_RLIN3, SOC_MSR_RLIN3, SOC_MSR_RLIN311_BIT );
    u2c_module_release( SOC_SWMRESS_OSTM, SOC_MSR_OSTM, SOC_MSR_OSTM0_BIT );
    u2c_module_release( SOC_SWMRESS_OSTM, SOC_MSR_OSTM, SOC_MSR_OSTM1_BIT );
}
