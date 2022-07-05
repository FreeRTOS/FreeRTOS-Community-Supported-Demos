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
 * copies or substantial portions of the Software. If you wish to use our Amazon
 * FreeRTOS name, please do so in a fair use way that does not cause confusion.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://aws.amazon.com/freertos
 *
 */

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo includes. */
#include "IntQueueTimer.h"
#include "IntQueue.h"

#include "driverlib/driverlib.h"

#define tmrTIMER_0_FREQUENCY     ( 2000UL )

void Timer0A_Handler( void );
void vUartPrintf( char* );
/*-----------------------------------------------------------*/

void vInitialiseTimerForIntQueueTest( void )
{
	/* Initialize a hardware timer. */
    SysCtlPeripheralEnable( SYSCTL_PERIPH_TIMER0 );
    while( !SysCtlPeripheralReady( SYSCTL_PERIPH_TIMER0 ) ){}
    TimerConfigure( TIMER0_BASE, TIMER_CFG_PERIODIC );
    TimerLoadSet( TIMER0_BASE, TIMER_A, ( ( configCPU_CLOCK_HZ / tmrTIMER_0_FREQUENCY ) + 1UL ));
    TimerIntRegister(TIMER0_BASE,TIMER_A,Timer0A_Handler);
	IntPrioritySet( INT_TIMER0A, configKERNEL_INTERRUPT_PRIORITY );
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
    IntMasterEnable();
    TimerEnable(TIMER0_BASE,TIMER_A);

}
/*-----------------------------------------------------------*/

void IntQueueTestTimerHandler( void )
{
	portYIELD_FROM_ISR( xSecondTimerHandler() );
}
/*-----------------------------------------------------------*/

void Timer0A_Handler( void )
{
    /* Clear Interrupt. */
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntQueueTestTimerHandler(); 
}
