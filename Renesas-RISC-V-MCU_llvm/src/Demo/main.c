#include "r_smc_entry.h"
#include "TestRunner.h"
#include "common.h"

int main(void);

int main(void)
{
    /* Startup and Hardware initialization. */
	machine_timer_enable();

    R_Config_UART0_Create();
    R_Config_UART0_Start();

	printf("Starting...\n\r");

	/* Start tests. */
	vStartTests();

	/* Should never reach here. */
    for (;;);

    return 0;
}

