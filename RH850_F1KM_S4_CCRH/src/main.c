#include "bsp_common.h"
#include "TestRunner.h"
#include <stdint.h>
#include <stdio.h>

int main(void);

int main (void)
{
    bsp_clock_init();
    printf("Start of program\r\n");

    vStartTests();

    return 0;
}

int printf (const char * format, ...)
{
    char    tx_buff[100];
    va_list arg;
    va_start(arg, format);
    vsprintf(tx_buff, format, arg);
    va_end(arg);

    /* Put your transmit function here */

    return 0;
}
