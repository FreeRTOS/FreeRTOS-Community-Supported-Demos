/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef RH850_BOARD_H
#define RH850_BOARD_H

#include <stdint.h>

/* Implemented by each board */
void board_init( void );
/* stdout and stderr of picolibc end up here (soc/common/libc_glue.c) */
void board_putc( char c );
/* 0 reports pass, any other value fail with that code; never returns */
void board_exit( int code ) __attribute__( ( noreturn ) );

/* Place a large zeroed object in RAM_LARGE (rh850.ld) */
#define RH850_LARGE_BSS          __attribute__( ( section( ".bss.rh850_large" ) ) )

/* Exit code used for an unexpected exception */
#define RH850_FAULT_EXIT_CODE    99

#endif /* RH850_BOARD_H */
