/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef RH850_RLIN3_REGS_H
#define RH850_RLIN3_REGS_H

/* RLN3n registers in UART mode, 8-bit unless noted (U2C HW UM p1396-1397) */
#define RH850_RLIN3_LWBR          0x01
#define RH850_RLIN3_LBRP01        0x02 /* 16-bit (p1427) */
#define RH850_RLIN3_LMD           0x08
#define RH850_RLIN3_LBFC          0x09
#define RH850_RLIN3_LEDE          0x0d
#define RH850_RLIN3_LCUC          0x0e
#define RH850_RLIN3_LMST          0x11
#define RH850_RLIN3_LST           0x12
#define RH850_RLIN3_LUOER         0x20
#define RH850_RLIN3_LUOR1         0x21
#define RH850_RLIN3_LUTDR         0x24

/* LWBR = 0: 16 samples per bit, prescaler 1/1 (p1425) */
#define RH850_RLIN3_SAMPLES       16
/* LMD[1:0] = 01: UART mode (p1455) */
#define RH850_RLIN3_LMD_UART      0x01
/* LCUC.OM0 and LMST.OMM0: 0 = reset mode (p1462, p1464) */
#define RH850_RLIN3_LCUC_OM0      ( 1 << 0 )
#define RH850_RLIN3_LMST_OMM0     ( 1 << 0 )
/* LST.UTS: transmission in progress (p1465) */
#define RH850_RLIN3_LST_UTS       ( 1 << 4 )
/* LUOER: UTOE transmit, UROE receive enable (p1473) */
#define RH850_RLIN3_LUOER_UTOE    ( 1 << 0 )
#define RH850_RLIN3_LUOER_UROE    ( 1 << 1 )

#endif /* RH850_RLIN3_REGS_H */
