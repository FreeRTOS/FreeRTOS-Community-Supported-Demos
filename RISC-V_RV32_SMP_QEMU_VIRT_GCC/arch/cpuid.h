#ifndef ARCH_CPUID_H
#define ARCH_CPUID_H

#ifdef __ASSEMBLER__
.macro arch_cpuid out_reg
    csrr \out_reg, mhartid
.endm
#else /* ifdef __ASSEMBLER__ */
static inline int arch_cpuid(void)
{
    unsigned long hartid;
    asm volatile ("csrr %0, mhartid" : "=r"(hartid));
    return hartid;
}
#endif /* ifdef __ASSEMBLER__ */

#endif
