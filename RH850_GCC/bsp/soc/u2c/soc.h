/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef SOC_U2C_H
#define SOC_U2C_H

/*
 * RH850/U2C values. HW = U2C HW UM R01UH1018EJ0100; IT and SCL are its
 * Interrupt_table.xlsx and Standby_Control_List.xlsx attachments.
 */

/* Core: G4KH (HW Table 3.2 p174), see arch/rh850/core/g4kh and soc.cmake */

/*
 * Memory: code flash 8 MB, local RAM of PE0 128 KB
 * (HW Section 4 address space p480)
 */
#define SOC_FLASH_BASE         0x00000000
#define SOC_FLASH_SIZE         0x00800000
#define SOC_LRAM0_BASE         0xfdc00000
#define SOC_LRAM0_SIZE         0x00020000

/*
 * INTC1 of PE0 for channels 0-31, INTC2 for 32-629
 * (HW Table 6.7 p535, p547; IT)
 */
#define SOC_INTC1_BASE         0xfffc4000
#define SOC_INTC2_BASE         0xfff80000
#define SOC_INTC1_CHANNELS     32
#define SOC_INTC_CHANNELS      630

/* OSTM (HW Table 32.3 p4317; interrupts HW Table 32.5 p4318, IT) */
#define SOC_OSTM0_BASE         0xffbf0000
#define SOC_OSTM1_BASE         0xff89a100
#define SOC_IRQ_OSTM0          63
#define SOC_IRQ_OSTM1          484

/* TAUJ0 channel 0 and 1, edge type (IT channels 133, 134) */
#define SOC_IRQ_TAUJ0_I0       133
#define SOC_IRQ_TAUJ0_I1       134

/* RLIN311 (HW Table 20.5 p1385; interrupts IT channels 493-496) */
#define SOC_RLIN311_BASE       0xff89bb00
#define SOC_IRQ_RLIN311        493
#define SOC_IRQ_RLIN311_UR0    494
#define SOC_IRQ_RLIN311_UR1    495
#define SOC_IRQ_RLIN311_UR2    496

/*
 * CLKC_HSB clocks OSTM (HW Table 32.4 p4318) and RLIN3. 20 MHz is the QEMU
 * value; the reset setting on silicon is not checked (HW Table 13.8 p919).
 */
#define SOC_CLK_HSB_HZ         20000000

/*
 * Clock controller
 * (HW p934, CKS_RLINC p971, CKS_RLINS p973, CLKKCPROT1 p1000)
 */
#define SOC_CKS_RLINC          0xff980140
#define SOC_CKS_RLINS          0xff980148
#define SOC_CLKKCPROT1         0xff980700
#define SOC_CKS_RLIN_HSB       1

/* Reset controller: software module reset status (HW p750-751, p760) */
#define SOC_SWMRESS_RLIN3      0xff980964
#define SOC_SWMRESS_OSTM       0xff980a84

/* Standby controller (HW p1062, p1067; MSRKCPROT p1070; bits from SCL) */
#define SOC_MSR_RLIN3          0xff981060
#define SOC_MSR_OSTM           0xff981180
#define SOC_MSRKCPROT          0xff981710
#define SOC_MSR_RLIN311_BIT    ( 1 << 11 )
#define SOC_MSR_OSTM0_BIT      ( 1 << 0 )
#define SOC_MSR_OSTM1_BIT      ( 1 << 1 )

/* Key code protection: write enable / disable values (HW p1000, p1070) */
#define SOC_KCPROT_ENABLE      0xa5a5a501
#define SOC_KCPROT_DISABLE     0xa5a5a500

#ifndef __ASSEMBLER__
    void soc_init( void );
#endif

#endif /* SOC_U2C_H */
