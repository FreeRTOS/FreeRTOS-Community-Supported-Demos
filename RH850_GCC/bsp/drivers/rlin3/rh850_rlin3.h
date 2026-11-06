/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef RH850_RLIN3_H
#define RH850_RLIN3_H

#include <stdint.h>

/* UART 8N1, LSB first; clk_hz is the RLIN3 clock */
void rh850_rlin3_init( uintptr_t base,
                       uint32_t clk_hz,
                       uint32_t baud );
void rh850_rlin3_putc( uintptr_t base,
                       char c );

#endif /* RH850_RLIN3_H */
