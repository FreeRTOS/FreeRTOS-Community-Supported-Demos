/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef RH850_INTC_REGS_H
#define RH850_INTC_REGS_H

/*
 * EICn, 16-bit, 8-bit access allowed (U2C HW UM 6.3.2, Table 6.16
 * p547-548). EIC0-31 at INTC1 + 2n, EIC32 and up at INTC2 + 2n.
 */
#define RH850_EIC_STRIDE      2
#define RH850_EIC_EIP_MASK    0x0f
#define RH850_EIC_EIOV        ( 1 << 5 )
#define RH850_EIC_EITB        ( 1 << 6 )
#define RH850_EIC_EIMK        ( 1 << 7 )
/* EIRF is bit 12, bit 4 of the upper byte */
#define RH850_EIC_EIRF        ( 1 << 12 )

/* EIIC of EIINTn is 1000H + n (U2C HW UM Table 3.95 p288) */
#define RH850_EIIC_EIINT      0x1000

#endif /* RH850_INTC_REGS_H */
