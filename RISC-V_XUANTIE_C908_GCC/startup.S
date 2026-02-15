 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <csi_config.h>

#ifndef configNUMBER_OF_CORES
    #define configNUMBER_OF_CORES                       1
#endif

 .text
    .align  2
    j        Reset_Handler
    .align   2
    .long    0x594B5343 /* CSKY ASCII */
    .long    0x594B5343 /* CSKY ASCII */
    .align   2
    .rept    9
    .long    0
    .endr

/* Every core boots from here */
_start:
    .global Reset_Handler
    .type   Reset_Handler, %function
Reset_Handler:
.option push
.option norelax
    /* reset mie and mip */
    csrw    mie, zero
    csrw    mip, zero
    /* disable interrupts */
    csrc    mstatus, (1 << 3)
    /* initialize global pointer */
    la      gp, __global_pointer$
.option pop
    /* initialize vector table */
    la      a0, __Vectors
    li	    a1, 0x1
    or	    a0, a0,a1
    csrw    mtvec, a0
    /* get cpu id */
    csrr a0, mhartid
    /* check if hart is within range */
    /* tp: hart id */
    li	t0, configNUMBER_OF_CORES
    bge	a0, t0, hart_out_of_bounds_loop
    /* sp = (cpuid + 1) * CONFIG_ARCH_INTERRUPTSTACK + g_base_irqstack */
    la   sp, g_base_irqstack
    addi t1, a0, 1
    li   t2, CONFIG_ARCH_INTERRUPTSTACK
    mul  t1, t1, t2
    add  sp, sp, t1
    /*jump to cpu entry directly */
    la   a0, main
    jalr a0
.size   Reset_Handler, . - Reset_Handler
    /* never access here */
__exit:
    j      __exit

hart_out_of_bounds_loop:
    /* Harts in this loop are out of bounds, increase configNUMBER_OF_CORES. */
    wfi
    j	hart_out_of_bounds_loop


.section .stack, "aw", @nobits
    .align  4
    .global g_base_irqstack
    .global g_top_irqstack
g_base_irqstack:
    .space CONFIG_ARCH_INTERRUPTSTACK * configNUMBER_OF_CORES
g_top_irqstack:

.data
.global secondary_boot_flag
.align 3
secondary_boot_flag:
    .dword 0


