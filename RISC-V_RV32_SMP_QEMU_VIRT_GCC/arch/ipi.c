#include "ipi.h"
#include "cpuid.h"

#define CLINT_BASE   0x2000000UL
#define CLINT_MSIP(hartid) ((volatile unsigned long *)(CLINT_BASE + 4 * (hartid)))

void arch_ipi_send(int cpuid)
{
    *CLINT_MSIP(cpuid) = 1;
}

void arch_ipi_clear(void)
{
    *CLINT_MSIP(arch_cpuid()) = 0;
}
