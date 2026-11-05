/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

/*
 * RH850/U2C8: code flash, local RAM of PE0 and cluster RAM 0 (CRAM00-02)
 * (U2C HW UM Section 4, Table 4.1 p480-481, U2C8 column)
 */
MEMORY
{
	FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 8M
	RAM   (rwx) : ORIGIN = 0xfdc00000, LENGTH = 128K
	CRAM  (rwx) : ORIGIN = 0xfe000000, LENGTH = 0x138000
}

/* Large zeroed data (an RTOS heap) goes to cluster RAM */
REGION_ALIAS("RAM_LARGE", CRAM);
