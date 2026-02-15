#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <board.h>
#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>
#include <riscv_csr.h>

extern void Reset_Handler(void);

static void vAppTask(void *arg)
{
    /* test here */
    while(1) {
        printf("hello\r\n");
        vTaskDelay(10);
    }
}

void prvBoardInit(void)
{
    board_uart_init();
}

static struct c9xx_regs_struct {
    uint64_t pmpaddr0;
    uint64_t pmpaddr1;
    uint64_t pmpaddr2;
    uint64_t pmpaddr3;
    uint64_t pmpaddr4;
    uint64_t pmpaddr5;
    uint64_t pmpaddr6;
    uint64_t pmpaddr7;
    uint64_t pmpcfg0;
    uint64_t mcor;
    uint64_t mhcr;
    uint64_t mccr2;
    uint64_t mhint;
    uint64_t msmpr;
    uint64_t mie;
    uint64_t mxstatus;
    uint64_t mtvec;
    uint64_t plic_base_addr;
    uint64_t clint_base_addr;
} c9xx_regs;

#define C9xx_PLIC_CLINT_OFFSET     0x04000000  /* 64M */
#define C9xx_PLIC_DELEG_OFFSET     0x001ffffc
#define C9xx_PLIC_DELEG_ENABLE     0x1

#define XIAOHUI_SRESET_BASE              0x18030000
#define XIAOHUI_SRESET_ADDR_OFFSET       0x10
#define PRIMARY_STARTUP_CORE_ID		0

static void c9xx_csr_copy( void )
{
    if (PRIMARY_STARTUP_CORE_ID == csi_get_cpu_id()) {
        /* Load from boot core */
        c9xx_regs.pmpaddr0 = rv_csr_read(CSR_PMPADDR0);
        c9xx_regs.pmpaddr1 = rv_csr_read(CSR_PMPADDR1);
        c9xx_regs.pmpaddr2 = rv_csr_read(CSR_PMPADDR2);
        c9xx_regs.pmpaddr3 = rv_csr_read(CSR_PMPADDR3);
        c9xx_regs.pmpaddr4 = rv_csr_read(CSR_PMPADDR4);
        c9xx_regs.pmpaddr5 = rv_csr_read(CSR_PMPADDR5);
        c9xx_regs.pmpaddr6 = rv_csr_read(CSR_PMPADDR6);
        c9xx_regs.pmpaddr7 = rv_csr_read(CSR_PMPADDR7);
        c9xx_regs.pmpcfg0  = rv_csr_read(CSR_PMPCFG0);
        c9xx_regs.mcor     = rv_csr_read(CSR_MCOR);
        c9xx_regs.msmpr    = rv_csr_read(CSR_MSMPR);
        c9xx_regs.mhcr     = rv_csr_read(CSR_MHCR);
        c9xx_regs.mccr2    = rv_csr_read(CSR_MCCR2);
        c9xx_regs.mhint    = rv_csr_read(CSR_MHINT);
        c9xx_regs.mtvec    = rv_csr_read(CSR_MTVEC);
        c9xx_regs.mie      = rv_csr_read(CSR_MIE);
        c9xx_regs.mxstatus = rv_csr_read(CSR_MXSTATUS);

        c9xx_regs.plic_base_addr = rv_csr_read(CSR_MAPBADDR);
        c9xx_regs.clint_base_addr = c9xx_regs.plic_base_addr + C9xx_PLIC_CLINT_OFFSET;
    } else {
        /* Store to other core */
        // rv_csr_write(CSR_PMPADDR0, c9xx_regs.pmpaddr0);
        // rv_csr_write(CSR_PMPADDR1, c9xx_regs.pmpaddr1);
        // rv_csr_write(CSR_PMPADDR2, c9xx_regs.pmpaddr2);
        // rv_csr_write(CSR_PMPADDR3, c9xx_regs.pmpaddr3);
        // rv_csr_write(CSR_PMPADDR4, c9xx_regs.pmpaddr4);
        // rv_csr_write(CSR_PMPADDR5, c9xx_regs.pmpaddr5);
        // rv_csr_write(CSR_PMPADDR6, c9xx_regs.pmpaddr6);
        // rv_csr_write(CSR_PMPADDR7, c9xx_regs.pmpaddr7);
        // rv_csr_write(CSR_PMPCFG0,  c9xx_regs.pmpcfg0);
        rv_csr_write(CSR_MCOR,     c9xx_regs.mcor);
        rv_csr_write(CSR_MSMPR,    c9xx_regs.msmpr);
        rv_csr_write(CSR_MHCR,     c9xx_regs.mhcr);
        rv_csr_write(CSR_MHINT,    c9xx_regs.mhint);
        // rv_csr_write(CSR_MTVEC,    c9xx_regs.mtvec);
        // rv_csr_write(CSR_MIE,      c9xx_regs.mie);
        rv_csr_write(CSR_MXSTATUS, c9xx_regs.mxstatus);
    }
}

void riscv_soc_init_cpu( void )
{
	c9xx_csr_copy();
}

void riscv_soc_start_cpu( int cpu_num )
{
	uint32_t mrmr;

	c9xx_csr_copy();
	*(unsigned long *)((unsigned long)XIAOHUI_SRESET_BASE + XIAOHUI_SRESET_ADDR_OFFSET + ((cpu_num - 1) << 3)) = (unsigned long)Reset_Handler;
#if __riscv_xtheadsync
	__ASM("sync");
#endif
	mrmr = *(uint32_t *)(XIAOHUI_SRESET_BASE);
	*(uint32_t *)(XIAOHUI_SRESET_BASE) = mrmr | (0x1 << (cpu_num - 1));
#if __riscv_xtheadsync
	__ASM("sync");
#endif
}

static void interrupt_init( void )
{
    UBaseType_t xCoreID = portGET_CORE_ID();
    UBaseType_t mie = __get_MIE();;
    if (xCoreID == PRIMARY_STARTUP_CORE_ID)
    {
        /* enable tick interrupt and software interrupt */
        mie |= (1 << 7 | 1 << 3);
    }
    else
    {
        /* nable ticksoftware interrupt */
        mie |= (1 << 3);
    }
    __set_MIE(mie);
}

void prvCPUInit( UBaseType_t xCoreID )
{
    unsigned long status = 0;
#if CONFIG_RISCV_FPU_ENABLED
    /* enable float ISA */
    status = __get_MSTATUS();
    status |= (1 << MSTATUS_FS_SHIFT);
    __set_MSTATUS(status);
#endif
#ifdef CONFIG_RISCV_VECTOR_ENABLED
    /* enable vector ISA */
    status = __get_MSTATUS();
    status |= (1 << MSTATUS_VS_SHIFT);
    __set_MSTATUS(status);
#endif

    interrupt_init();

    if (xCoreID == 0)
    {
        soc_set_sys_freq(20000000);
        csi_tick_init();
    }

}

// int main(void)
// {
//     UBaseType_t xCoreID = portGET_CORE_ID();
//     prvCPUInit(xCoreID);
//     if (xCoreID == configPrimaryCoreID)
//     {
        
//         #if (configNUMBER_OF_CORES > 1)
//         {
//             SecondaryCoresUp();
//         }
//         #endif
//         prvBoardInit();
//         printf("welcome to FreeRTOS\r\n");
//         TaskHandle_t xHandle;
//         int prio = configMAX_PRIORITIES / 2;
//         BaseType_t ret = xTaskCreate(vAppTask, "app_task", CONFIG_INIT_TASK_STACK_SIZE / sizeof( StackType_t ), NULL, prio, &xHandle);
//         configASSERT(ret == pdPASS);
//         /* kernel start */
//         extern void vStartTests( void );
//         vStartTests();
//         // vTaskStartScheduler();
//     }
//     else
//     {
//         // xPortStartScheduler();
//         configASSERT(pdFALSE)
//     }
//     /* should never reach here */
//     configASSERT(pdFALSE);
//     return 0;
// }

int main(void)
{
    UBaseType_t xCoreID = portGET_CORE_ID();
    prvCPUInit(xCoreID);
    if (xCoreID == configPrimaryCoreID)
    {
        
        #if (configNUMBER_OF_CORES > 1)
        {
            SecondaryCoresUp();
        }
        #endif
        prvBoardInit();
        printf("welcome to FreeRTOS\r\n");
        int prio = configMAX_PRIORITIES / 2;
        // BaseType_t ret = xTaskCreate(vAppTask, "app_task", CONFIG_INIT_TASK_STACK_SIZE / sizeof( StackType_t ), NULL, prio, NULL);
        // configASSERT(ret == pdPASS);
        TaskHandle_t xHandle;
        /* kernel start */
        extern void vStartTests( void );
        vStartTests();
        // vTaskStartScheduler();
    }
    else
    {
        // xPortStartScheduler();
        configASSERT(pdFALSE)
    }
    /* should never reach here */
    configASSERT(pdFALSE);
    return 0;
}

void (*trap_c_callback)( void );

void trap_c(uintptr_t *regs)
{
    int i;
    unsigned long vec = 0;

    vec = __get_MCAUSE();

    printf("CPU Exception(mcause);: NO.0x%lx", vec);
    printf("\n");

    for (i = 0; i < 31; i++) {
        printf("x%d: %p\t", i + 1, (void *)regs[i]);

        if ((i % 4) == 3) {
            printf("\n");
        }
    }

    printf("\n");
    printf("mepc   : %p\n", (void *)regs[31]);
    printf("mstatus: %p\n", (void *)regs[32]);

    if (trap_c_callback) {
        trap_c_callback();
    }

    while (1);
}

__attribute__((weak)) void exceptionHandler( void *context )
{
    trap_c((uintptr_t *)context);
}
