#include "spinlock.h"
#include "cpuid.h"
#include "assert.h"

struct arch_spinlock_t arch_task_lock = {
    .owner = -1,
    .cnt = 0,
};
struct arch_spinlock_t arch_isr_lock = {
    .owner = -1,
    .cnt = 0,
};

// XXX: maybe use C11 atomic?
static inline int compare_and_swap(volatile int *addr, int old, int new)
{
    int prev, res;
    asm volatile (
        "0: lr.w %[prev], (%[addr])       \n" /* load-reserved */
        "   bne  %[prev], %[old], 1f      \n" /* not equal -> fail */
        "   sc.w %[res], %[new], (%[addr]) \n" /* store-conditional */
        "   bnez %[res], 0b               \n" /* sc failed -> retry */
        "1:                               \n"
        : [prev] "=&r" (prev), [res] "=&r" (res)
        : [addr] "r" (addr), [old] "r" (old), [new] "r" (new)
        : "memory"
    );
    return prev == old;
}

void arch_spinlock_lock(int cpuid, struct arch_spinlock_t *lock)
{
    /* Fast path: if I'm already the owner, just increment depth */
    if (lock->owner == cpuid) {
        lock->cnt++;
        return;
    }

    /* Otherwise try to acquire: spin until CAS succeeds */
    while (1) {
        /* try set owner from 0 -> meid atomically */
        if (compare_and_swap(&lock->owner, -1, cpuid)) {
            /* acquired */
            /* full memory barrier to ensure subsequent accesses see consistent state */
            asm volatile("fence" ::: "memory");
            lock->cnt = 1;
            return;
        }

        /* optional: cpu relax hint (nop) */
        asm volatile("nop");
    }
}

void arch_spinlock_unlock(int cpuid, struct arch_spinlock_t *lock)
{
    if (lock->owner != cpuid) {
        arch_assert("unlocking spinlock while not owning it", __FILE__, __LINE__);
        return;
    }

    /* decrement depth; if still >0, keep owner */
    lock->cnt--;
    if (lock->cnt > 0) {
        return;
    }

    /* clear owner to 0 (unlock). a plain store is fine because owner only cleared by owner. */
    asm volatile ("" ::: "memory");
    lock->owner = -1;
    /* memory barrier to ensure stores committed before releasing lock */
    asm volatile("fence" ::: "memory");
    return;
}
