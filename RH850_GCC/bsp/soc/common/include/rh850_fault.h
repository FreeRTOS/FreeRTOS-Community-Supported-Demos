/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef RH850_FAULT_H
#define RH850_FAULT_H

#include <stdint.h>

/* Report an unexpected exception (fe: FE level) and exit; never returns */
void rh850_fault( uint32_t fe,
                  uint32_t cause,
                  uint32_t pc ) __attribute__( ( noreturn ) );

#endif /* RH850_FAULT_H */
