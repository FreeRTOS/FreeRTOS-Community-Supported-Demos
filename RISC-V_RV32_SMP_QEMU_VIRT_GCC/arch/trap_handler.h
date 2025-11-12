#ifndef ARCH_TRAP_HANDLER_H
#define ARCH_TRAP_HANDLER_H
typedef void (*arch_trap_handler_t)(void);
void arch_trap_handler_install(unsigned int irq_num, arch_trap_handler_t handler);
#endif
