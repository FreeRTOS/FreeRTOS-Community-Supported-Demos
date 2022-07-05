/*
 * FreeRTOS V202112.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

#include "driverlib/driverlib.h"
#include "utils/uartstdio.h"

/* */
#include "TestRunner.h"

void prvSetupHardware( void );
void vPortUARTprintf ( char* );

int main ( void )
{
    /* Startup and Hardware initialization. */
    prvSetupHardware();
    
    vStartTests();

    for( ; ; );
    return 0;
}
void prvSetupHardware( void )
{
    /* Setup the PLL. 
     * CPU Clock : 50M hz
     */
    SysCtlClockSet( SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ );
    
    /* Setup RGB LED. */
    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF );
    while( !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF ) ){}
    GPIOPinTypeGPIOOutput( GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 );
    
    /* Enable the UART.  */
	SysCtlPeripheralEnable( SYSCTL_PERIPH_UART0 );
    while( !SysCtlPeripheralReady(SYSCTL_PERIPH_UART0 ) ){}
	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA );
    while( !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA ) ){}

	/* Set GPIO A0 and A1 as peripheral function.  They are used to output the
	UART signals. */
    GPIOPinTypeUART( GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1 );
    GPIOPinConfigure( GPIO_PA0_U0RX);
    GPIOPinConfigure( GPIO_PA1_U0TX);
	
    /* Configure the UART for 8-N-1 operation. */
	UARTConfigSetExpClk( UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE );

    //vPortUARTprintf("123456789poiuytrewwsdfggh\r\n");
}

void vPortUARTprintf( char* message )
{
    char * pcNextChar = message;
    
	while( *pcNextChar != '\0')
    {
        UARTCharPut(UART0_BASE, *pcNextChar);
		pcNextChar++;
	}

}

void vConfigureTimerForRunTimeStats( void )
{

}

uint32_t ulGetRunTimeCounterValue( void )
{

}

void vApplicationMallocFailedHook( void );
void vApplicationMallocFailedHook( void )
{
	taskDISABLE_INTERRUPTS();
	for( ;; );

}
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char* pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	taskDISABLE_INTERRUPTS();
	for( ;; );
}
void vApplicationIdleHook( void )
{
}
void vPreSleepProcessing( uint32_t ulExpectedIdleTime )
{
}
