#include "portContext.h"

.global freertos_renesas_risc_v_trap_handler

.extern vTaskSwitchContext
.extern xTaskIncrementTick
.extern pullMachineTimerCompareRegister
.extern pullNextTime
.extern uxTimerIncrementsForOneTick

.weak freertos_renesas_risc_v_application_exception_handler
.weak freertos_renesas_risc_v_application_interrupt_handler
/*-----------------------------------------------------------*/

.macro portUPDATE_MTIMER_COMPARE_REGISTER
    load_x a0, pullMachineTimerCompareRegister  /* Load address of compare register into a0. */
    load_x a1, pullNextTime                     /* Load the address of ullNextTime into a1. */

    #if( __riscv_xlen == 32 )

        /* Update the 64-bit mtimer compare match value in two 32-bit writes. */
        li a4, -1
        lw a2, 0(a1)                /* Load the low word of ullNextTime into a2. */
        lw a3, 4(a1)                /* Load the high word of ullNextTime into a3. */
        sw a4, 0(a0)                /* Low word no smaller than old value to start with - will be overwritten below. */
        sw a3, 4(a0)                /* Store high word of ullNextTime into compare register.  No smaller than new value. */
        sw a2, 0(a0)                /* Store low word of ullNextTime into compare register. */
        lw t0, uxTimerIncrementsForOneTick  /* Load the value of ullTimerIncrementForOneTick into t0 (could this be optimized by storing in an array next to pullNextTime?). */
        add a4, t0, a2              /* Add the low word of ullNextTime to the timer increments for one tick (assumes timer increment for one tick fits in 32-bits). */
        sltu t1, a4, a2             /* See if the sum of low words overflowed (what about the zero case?). */
        add t2, a3, t1              /* Add overflow to high word of ullNextTime. */
        sw a4, 0(a1)                /* Store new low word of ullNextTime. */
        sw t2, 4(a1)                /* Store new high word of ullNextTime. */

    #endif /* __riscv_xlen == 32 */

    #if( __riscv_xlen == 64 )

        /* Update the 64-bit mtimer compare match value. */
        ld t2, 0(a1)                /* Load ullNextTime into t2. */
        sd t2, 0(a0)                /* Store ullNextTime into compare register. */
        ld t0, uxTimerIncrementsForOneTick  /* Load the value of ullTimerIncrementForOneTick into t0 (could this be optimized by storing in an array next to pullNextTime?). */
        add t4, t0, t2              /* Add ullNextTime to the timer increments for one tick. */
        sd t4, 0(a1)                /* Store ullNextTime. */

    #endif /* __riscv_xlen == 64 */
    .endm
/*-----------------------------------------------------------*/

freertos_renesas_risc_v_application_exception_handler:
    csrr t0, mcause     /* For viewing in the debugger only. */
    csrr t1, mepc       /* For viewing in the debugger only */
    csrr t2, mstatus    /* For viewing in the debugger only */
    j .
/*-----------------------------------------------------------*/

freertos_renesas_risc_v_application_interrupt_handler:
    csrr t0, mcause     /* For viewing in the debugger only. */
    csrr t1, mepc       /* For viewing in the debugger only */
    csrr t2, mstatus    /* For viewing in the debugger only */
    j .
/*-----------------------------------------------------------*/

.section .text.freertos_renesas_risc_v_trap_handler
.align 8
freertos_renesas_risc_v_trap_handler:
    portcontextSAVE_CONTEXT_INTERNAL

    csrr a0, mcause
    csrr a1, mepc

    bge a0, x0, synchronous_exception

asynchronous_interrupt:
    store_x a1, 0( sp )                 /* Asynchronous interrupt so save unmodified exception return address. */
    load_x sp, xISRStackTop             /* Switch to ISR stack. */
    j handle_interrupt

synchronous_exception:
    addi a1, a1, 4                      /* Synchronous so update exception return address to the instruction after the instruction that generated the exeption. */
    store_x a1, 0( sp )                 /* Save updated exception return address. */
    load_x sp, xISRStackTop             /* Switch to ISR stack. */
    j handle_exception

handle_interrupt:
    test_if_mtimer:                     /* If there is a CLINT then the mtimer is used to generate the tick interrupt. */
        addi t0, x0, 1
        slli t0, t0, __riscv_xlen - 1   /* LSB is already set, shift into MSB.  Shift 31 on 32-bit or 63 on 64-bit cores. */
        addi t1, t0, 7                  /* 0x8000[]0007 == machine timer interrupt. */
        bne a0, t1, application_interrupt_handler

        portUPDATE_MTIMER_COMPARE_REGISTER
        call xTaskIncrementTick
        beqz a0, processed_source       /* Don't switch context if incrementing tick didn't unblock a task. */
        call vTaskSwitchContext
        j processed_source

application_interrupt_handler:
    call freertos_renesas_risc_v_application_interrupt_handler
    j processed_source

handle_exception:
    /* Lower 16 bits of a0 contains exception code. */
    li t0, 0xffff
    and a0, a0, t0
    li t0, 11                                   /* 11 == environment call. */
    bne a0, t0, application_exception_handler   /* Not an M environment call, so some other exception. */
    call vTaskSwitchContext
    j processed_source

application_exception_handler:
    call freertos_renesas_risc_v_application_exception_handler
    j processed_source                  /* No other exceptions handled yet. */

processed_source:
    portcontextRESTORE_CONTEXT
/*-----------------------------------------------------------*/
