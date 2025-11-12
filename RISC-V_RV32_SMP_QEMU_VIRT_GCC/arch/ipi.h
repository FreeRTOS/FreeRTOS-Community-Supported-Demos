#ifndef ARCH_IPI_H
#define ARCH_IPI_H
void arch_ipi_send(int cpuid);
void arch_ipi_clear(void);
#endif
