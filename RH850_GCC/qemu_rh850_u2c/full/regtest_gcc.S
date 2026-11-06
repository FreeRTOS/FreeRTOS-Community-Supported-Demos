/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

/*
 * Register test tasks 1-4: fill r1, r2, r4-r31 and FPSR with a pattern per
 * task, then check, count and yield or wait; a mismatch calls vRegTestFail.
 */

#include "rh850_asm.h"
#include "rh850_sysreg.h"
#include "core.h"
#include "FreeRTOSConfig.h"
#include "portframe.h"

/* Pattern of register r in task t */
#define PAT(t, r) (((t) << 28) | ((r) << 20) | 0x5a5a0 | (t))
/* FPSR pattern: CC, IF (odd tasks), RM = t & 3, FS, XP; no enable bits, no PEM */
#define FPSR_PAT(t) ((((0x30 + (t)) & 0xff) << RH850_FPSR_CC_SHIFT) | \
		     (((t) & 1) * RH850_FPSR_IF) | \
		     (((t) & 3) << RH850_FPSR_RM_SHIFT) | RH850_FPSR_FS | \
		     ((t) & RH850_FPSR_XP_MASK))

	.macro	fill t
	.irp	r, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, \
		19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
	mov	hilo(PAT(\t, \r)), r\r
	.endr
	.endm

	/*
	 * Check r10 with r11 as temp; r11 is parked below a lowered sp, so an
	 * interrupt frame cannot overwrite it. movea keeps the flags of cmp.
	 */
	.macro	check t
	movea	-8, sp, sp
	st.w	r11, 0[sp]
	mov	hilo(PAT(\t, 10)), r11
	cmp	r11, r10
	ld.w	0[sp], r11
	movea	8, sp, sp
	bne	9f
	.irp	r, 1, 2, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, \
		19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
	mov	hilo(PAT(\t, \r)), r10
	cmp	r10, r\r
	bne	9f
	.endr
#if portUSE_FPU
	rh850_stsr	RH850_SR_FPSR, r10
	mov	hilo(FPSR_PAT(\t)), r11
	cmp	r10, r11
	bne	9f
#endif
	.endm

	.macro	regtest t, yield, name
	.section .text.regtest\t, "ax"
	.global	\name
\name:
#if portUSE_FPU
	mov	hilo(FPSR_PAT(\t)), r10
	ldsr	r10, RH850_SR_FPSR
#endif
	fill	\t
1:	check	\t
	/* Count the round, then refill the two scratch registers */
	mov	hilo(C_SYM(ulRegTestCounter) + 4 * (\t - 1)), r10
	ld.w	0[r10], r11
	add	1, r11
	st.w	r11, 0[r10]
	mov	hilo(PAT(\t, 10)), r10
	mov	hilo(PAT(\t, 11)), r11
	.if	\yield
#if portUSE_FPU && RH850_CORE_HAS_SYNCE
	synce
#endif
	trap	0
	.endif
	br	1b
9:	mov	\t, r6
	jarl	C_SYM(vRegTestFail), lp
	br	9b
	.endm

	regtest	1, 1, C_SYM(vRegTest1Task)
	regtest	2, 0, C_SYM(vRegTest2Task)
	regtest	3, 1, C_SYM(vRegTest3Task)
	regtest	4, 0, C_SYM(vRegTest4Task)
