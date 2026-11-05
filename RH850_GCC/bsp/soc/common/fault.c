/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdint.h>
#include <stdio.h>
#include "rh850_board.h"
#include "rh850_fault.h"

void rh850_fault( uint32_t fe,
                  uint32_t cause,
                  uint32_t pc )
{
    printf( "FAULT %s cause 0x%08lx pc 0x%08lx\n", fe != 0U ? "FE" : "EI",
            ( unsigned long ) cause, ( unsigned long ) pc );
    board_exit( RH850_FAULT_EXIT_CODE );
}
