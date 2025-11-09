#include "interrupt.h"

// XXX: inline for performance?

void arch_disable_interrupts(void)
{
    asm volatile (
        "csrc mstatus, 0x8\n"
        ::: "memory"
    );
}

void arch_enable_interrupts(void)
{
    asm volatile (
        "csrs mstatus, 0x8\n"
        ::: "memory"
    );
}

unsigned long arch_save_and_disable_interrupts(void)
{
    unsigned long status;
    asm volatile (
        "csrrci %0, mstatus, 0x8\n"
        : "=r" (status) :: "memory"
    );
    return 0UL;
}


void arch_restore_interrupts(unsigned long status) {
    asm volatile ("" ::: "memory" ); /* Compiler memory barrier */
    if (status & 0x8) {
        asm volatile ("csrsi mstatus, %0" : : "i" (0x8)); \
    } else {
        asm volatile ("csrci mstatus, %0" : : "i" (0x8)); \
    }
    asm volatile ("" ::: "memory" ); /* Compiler memory barrier */
}

unsigned long arch_set_interrupt_mask_from_isr(void) {
    // XXX: nested IRQ
    return 0UL;
}

void arch_clear_interrupt_mask_from_isr(unsigned long mask) {
    // XXX: nested IRQ
    return;
}
