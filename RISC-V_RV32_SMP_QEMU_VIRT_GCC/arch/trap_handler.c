#include "trap_handler.h"
#include "stdint.h"
#include "assert.h"

/* helpers to build J-type (jal) encoding: jal rd, imm */
static inline uint32_t build_jal(uint32_t rd, int32_t imm)
{
    /* 
     * imm must be multiple of 2 (LSB = 0). 
     * imm is signed 21-bit (bits 20..0, bit0 implicit 0)
     */
    uint32_t uimm = (uint32_t)imm;
    uint32_t imm20 = (uimm >> 20) & 0x1;            /* bit 20 */
    uint32_t imm10_1 = (uimm >> 1) & 0x3FF;         /* bits 10:1 */
    uint32_t imm11 = (uimm >> 11) & 0x1;            /* bit 11 */
    uint32_t imm19_12 = (uimm >> 12) & 0xFF;        /* bits 19:12 */

    uint32_t instr = 0;
    instr |= (imm20 << 31);
    instr |= (imm19_12 << 12);
    instr |= (imm11 << 20);
    instr |= (imm10_1 << 21);
    instr |= (rd << 7);
    instr |= 0x6F; /* opcode for JAL */
    return instr;
}

void arch_trap_handler_install(unsigned int irq_num, arch_trap_handler_t handler)
{
    uintptr_t mtvec;
    __asm__ volatile("csrr %0, mtvec" : "=r"(mtvec));

    uintptr_t base = mtvec & ~0x3UL;
    uint32_t *entry = (uint32_t *)(base + 4 * (uintptr_t)irq_num);
    intptr_t offset = (intptr_t)handler - (intptr_t)entry;
    if (offset < -(1 << 20) || offset >= (1 << 20))
    {
        /* offset exceed imm of jal instruction */
        /* XXX: add arch assert */
        arch_assert("trap handler offset exceeds imm", __FILE__, __LINE__);
        return;
    }
    *entry = build_jal(0, offset);
    __asm__ volatile("fence.i" ::: "memory");
}
