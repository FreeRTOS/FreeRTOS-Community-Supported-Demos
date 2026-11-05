/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef RH850_OSTM_H
#define RH850_OSTM_H

#include <stdbool.h>
#include <stdint.h>

/*
 * Interval timer mode: CNT counts down from cmp, TINT every cmp + 1
 * clocks (U2C HW UM 32.4.2 p4337). No interrupt at count start.
 */
void rh850_ostm_start_interval( uintptr_t base,
                                uint32_t cmp,
                                bool irq );

/*
 * Free-run compare mode: CNT counts up from 0, TINT when CNT = CMP; a CMP
 * write takes effect at once (U2C HW UM 32.4.3 p4342-4343).
 */
void rh850_ostm_start_freerun( uintptr_t base,
                               bool irq );
void rh850_ostm_set_compare( uintptr_t base,
                             uint32_t cmp );
void rh850_ostm_stop( uintptr_t base );
uint32_t rh850_ostm_count( uintptr_t base );

#endif /* RH850_OSTM_H */
