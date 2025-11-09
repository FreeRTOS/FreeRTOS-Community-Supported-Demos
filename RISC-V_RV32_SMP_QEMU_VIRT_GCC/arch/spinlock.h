#ifndef ARCH_SPINLOCK_H
#define ARCH_SPINLOCK_H

/* recursive lock */
struct arch_spinlock_t {
    volatile int cnt;
    volatile int owner;
};

extern struct arch_spinlock_t arch_task_lock;
extern struct arch_spinlock_t arch_isr_lock;
void arch_spinlock_lock(int cpuid, struct arch_spinlock_t *lock);
void arch_spinlock_unlock(int cpuid, struct arch_spinlock_t *lock);
#endif
