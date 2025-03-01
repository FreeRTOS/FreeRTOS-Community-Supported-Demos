#include "FreeRTOS.h"
#include "task.h"
#include "r_smc_entry.h"
#include "stdio.h"
#include "stdarg.h"
#include "assert.h"

volatile bool g_vcoms_tx_done = true;

//void vAssertCalled()
//{
//    /* Stop execution for debugging purposes or log the error */
//    for( ;; );
//}

void vAssertCalled(const char *pcFileName, unsigned long ulLine) {
    /* Stop execution for debugging purposes or log the error */
	for ( ;; );
}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
    /* Stop execution for debugging purposes or log the error */
    for( ;; );
}

void vApplicationMallocFailedHook() {
    /* Stop execution for debugging purposes or log the error */
    for( ;; );
}

void vApplicationIdleHook() {
}

void freertos_risc_v_application_interrupt_handler(void) {

}

void freertos_risc_v_application_exception_handler(void) {

}

void machine_timer_enable(void) {
    R_CPU_AUX->MACTCR_b.ENABLE = 1U;
    R_CLIC->clicintie7_b.IE = 1U;    /* enable mtip interrupt */
}

void vcom_printf( char const * format, ...)
{
    va_list args;
    MD_STATUS err;
    uint8_t tx_data[256];
    int len = 0;

    while (!g_vcoms_tx_done);  // Wait for last write to complete

    va_start(args, format);
    len = vsprintf((char *)tx_data, format, args);
    err = R_Config_UART0_Send(tx_data, (uint16_t) len);

    assert (err == MD_OK);
    g_vcoms_tx_done = false;

    va_end(args);
}
