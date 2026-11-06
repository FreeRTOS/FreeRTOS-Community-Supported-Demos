/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef RH850_TEST_EXIT_H
#define RH850_TEST_EXIT_H

#include <stdint.h>

/*
 * Test-exit device of QEMU rh850-u2c (test-exit=on), not a U2C peripheral:
 * QEMU exits with 0 on pass and with the code on fail.
 */
void test_exit_pass( uintptr_t base ) __attribute__( ( noreturn ) );
void test_exit_fail( uintptr_t base,
                     uint16_t code ) __attribute__( ( noreturn ) );

#endif /* RH850_TEST_EXIT_H */
