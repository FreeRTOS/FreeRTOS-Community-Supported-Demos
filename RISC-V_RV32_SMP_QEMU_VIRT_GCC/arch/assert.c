#include "assert.h"
#include "stdio.h"
#include "interrupt.h"

void arch_assert(const char *pcMessage,
                    const char * pcFileName,
                    unsigned long ulLine)
{
    arch_disable_interrupts();
    printf( "ASSERT! %s (Line %d, file %s)\r\n", pcMessage, ( int ) ulLine, pcFileName );
    while(1)
    {
        __asm volatile ( "wfi" );
    }
}
