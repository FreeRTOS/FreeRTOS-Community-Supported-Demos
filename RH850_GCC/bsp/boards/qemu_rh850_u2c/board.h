/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BOARD_QEMU_RH850_U2C_H
#define BOARD_QEMU_RH850_U2C_H

#include "soc.h"

/* qemu-system-rh850 -M rh850-u2c: RLIN311 is the serial console */
#define BOARD_CONSOLE_BASE        SOC_RLIN311_BASE
#define BOARD_CONSOLE_CLK_HZ      SOC_CLK_HSB_HZ
#define BOARD_CONSOLE_BAUD        115200

/* Tick timer and a second timer for tests */
#define BOARD_TICK_OSTM_BASE      SOC_OSTM0_BASE
#define BOARD_TICK_IRQ            SOC_IRQ_OSTM0
#define BOARD_TIMER2_OSTM_BASE    SOC_OSTM1_BASE
#define BOARD_TIMER2_IRQ          SOC_IRQ_OSTM1
#define BOARD_TIMER_CLK_HZ        SOC_CLK_HSB_HZ

/* Edge channels with no device in this QEMU machine, raised by software */
#define BOARD_SWIRQ0              SOC_IRQ_TAUJ0_I0
#define BOARD_SWIRQ1              SOC_IRQ_TAUJ0_I1

/* Test-exit device of the QEMU machine (option test-exit=on) */
#define BOARD_TEST_EXIT_BASE      0x40000000

#endif /* BOARD_QEMU_RH850_U2C_H */
