/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef RH850_OSTM_REGS_H
#define RH850_OSTM_REGS_H

/*
 * OSTMn registers, offsets from the instance base
 * (U2C HW UM Table 32.9 p4325)
 */
#define RH850_OSTM_CMP        0x00 /* 32-bit */
#define RH850_OSTM_CNT        0x04 /* 32-bit */
#define RH850_OSTM_TE         0x10 /* 8-bit, bit 0: counter running */
#define RH850_OSTM_TS         0x14 /* 8-bit, write 1: start */
#define RH850_OSTM_TT         0x18 /* 8-bit, write 1: stop */
#define RH850_OSTM_CTL        0x20 /* 8-bit */

/* OSTMnCTL (U2C HW UM p4333) */
#define RH850_OSTM_CTL_MD0    ( 1 << 0 ) /* interrupt at count start */
/* MD1 0: interval timer, 1: free-run compare */
#define RH850_OSTM_CTL_MD1    ( 1 << 1 )
#define RH850_OSTM_CTL_MD2    ( 1 << 2 ) /* 1: CNT not loaded at count start */
#define RH850_OSTM_CTL_IE     ( 1 << 7 ) /* OSTMnTINT enable */

#endif /* RH850_OSTM_REGS_H */
