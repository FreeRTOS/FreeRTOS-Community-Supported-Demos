#ifndef ARCH_INTERRUPT_H
#define ARCH_INTERRUPT_H
void arch_disable_interrupts(void);
void arch_enable_interrupts(void);
unsigned long arch_save_and_disable_interrupts(void);
void arch_restore_interrupts(unsigned long status);
unsigned long arch_set_interrupt_mask_from_isr(void);
void arch_clear_interrupt_mask_from_isr(unsigned long mask);
#endif
