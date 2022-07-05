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

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* TI includes. */
#include "driverlib/driverlib.h"

/* Demo board specifics. */
#define mainLED_RED         2
#define mainLED_GREEN       4
#define mainLED_BLUE        8
#define mainBAUD_RATE       ( 9600 )
#define mainFIFO_SET        ( 0x10 )
#define mainPUSH_BUTTON     0

/* Priorities at which the tasks are created. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define	mainQUEUE_SEND_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )
#define	mainBUTTON_TASK_PRIORITY		    ( tskIDLE_PRIORITY + 1 )

/* The rate at which data is sent to the queue.  The 200ms value is converted
to ticks using the portTICK_PERIOD_MS constant. */
#define mainQUEUE_SEND_FREQUENCY_MS			( pdMS_TO_TICKS( 1000UL ) )

/* The number of items the queue can hold.  This is 1 as the receive task
will remove items as they are added, meaning the send task should always find
the queue empty. */
#define mainQUEUE_LENGTH					( 1 )
#define mainDEBOUNCE_DELAY			        ( ( TickType_t ) 150 / portTICK_PERIOD_MS )
#define mainNO_DELAY				        ( ( TickType_t ) 0 )

/* Values passed to the two tasks just to check the task parameter
functionality. */
#define mainQUEUE_SEND_PARAMETER			( 0x1111UL )
#define mainQUEUE_RECEIVE_PARAMETER			( 0x22UL )

/*-----------------------------------------------------------*/

/*
 * The tasks as described in the comments at the top of this file.
 */
static void prvQueueReceiveTask( void *pvParameters );
static void prvQueueSendTask( void *pvParameters );
static void prvButtonHandlerTask( void *pvParameters );


/*
 * Set up the hardware ready to run this demo.
 */
static void prvSetupHardware( void );

/*
 * Called by main() to create the simply blinky style application if
 * configCREATE_SIMPLE_TICKLESS_DEMO is set to 1.
 */
void main_blinky( void );

void vUART0_ISR( void );
void vGPIOF_ISR( void );

/* The queue used by both tasks. */
static QueueHandle_t xQueue = NULL;

/* The semaphore used to wake the button handler task from within the GPIO
interrupt handler. */
SemaphoreHandle_t xButtonSemaphore = NULL;

/* String that is transmitted on the UART. */
static char *cMessage = "Task woken by button SW1 interrupt! --- \r\n";
static volatile char *pcNextChar;

/*-----------------------------------------------------------*/

void main( void )
{
	/* Prepare the hardware to run this demo. */
	prvSetupHardware();
    
    /* Create the semaphore used to wake the button handler task from the GPIO
	ISR. */
	xButtonSemaphore = xSemaphoreCreateBinary();
	xSemaphoreTake( xButtonSemaphore, 0 );

	xTaskCreate( prvButtonHandlerTask, "Status", configMINIMAL_STACK_SIZE, 
                   NULL , mainBUTTON_TASK_PRIORITY, NULL );
	
    /* Create the queue. */
	xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( uint32_t ) );

	if( xQueue != NULL )
	{
		/* Start the two tasks as described in the comments at the top of this
		file. */
		xTaskCreate( prvQueueReceiveTask,					/* The function that implements the task. */
					"Rx", 									/* The text name assigned to the task - for debug only as it is not used by the kernel. */
					configMINIMAL_STACK_SIZE, 				/* The size of the stack to allocate to the task. */
					( void * ) mainQUEUE_RECEIVE_PARAMETER, /* The parameter passed to the task - just to check the functionality. */
					mainQUEUE_RECEIVE_TASK_PRIORITY, 		/* The priority assigned to the task. */
					NULL );									/* The task handle is not required, so NULL is passed. */

		xTaskCreate( prvQueueSendTask, "TX", configMINIMAL_STACK_SIZE, ( void * ) mainQUEUE_SEND_PARAMETER, mainQUEUE_SEND_TASK_PRIORITY, NULL );


		/* Start the tasks and timer running. */
		vTaskStartScheduler();
	}

	/* If all is well, the scheduler will now be running, and the following
	line will never be reached.  If the following line does execute, then
	there was insufficient FreeRTOS heap memory available for the idle and/or
	timer tasks	to be created.  See the memory management section on the
	FreeRTOS web site for more details. */
	for( ;; );
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
    /* Setup the PLL. 
     * CPU Clock : 50M hz
     */
    SysCtlClockSet( SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ );
    
    /* Setup RGB LED. */
    SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF );
    while( !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF ) ){}
    GPIOPinTypeGPIOOutput( GPIO_PORTF_BASE, mainLED_RED|mainLED_BLUE|mainLED_GREEN );
	
    /* Setup the push button. */
    GPIOPinTypeGPIOInput( GPIO_PORTF_BASE, GPIO_PIN_4 );
	GPIOPadConfigSet( GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU );
    
    /* Setup Interrupt. */
    GPIOIntTypeSet( GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_RISING_EDGE );
	IntPrioritySet( INT_GPIOF, configKERNEL_INTERRUPT_PRIORITY );
    GPIOIntEnable( GPIO_PORTF_BASE, GPIO_PIN_4 );
	IntEnable( INT_GPIOF );
	
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
	UARTConfigSetExpClk( UART0_BASE, SysCtlClockGet(), mainBAUD_RATE, UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE );
	
    /* We don't want to use the fifo.  This is for test purposes to generate
	as many interrupts as possible. */
	HWREG( UART0_BASE + UART_O_LCRH ) &= ~mainFIFO_SET;

	/* Enable Tx interrupts. */
	HWREG( UART0_BASE + UART_O_IM ) |= UART_INT_TX;
	IntPrioritySet( INT_UART0, configKERNEL_INTERRUPT_PRIORITY );
	IntEnable( INT_UART0 );
}

static void prvQueueSendTask( void *pvParameters )
{
TickType_t xNextWakeTime;
const unsigned long ulValueToSend = 100UL;

	/* Check the task parameter is as expected. */
	configASSERT( ( ( unsigned long ) pvParameters ) == mainQUEUE_SEND_PARAMETER );

	/* Initialise xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, mainQUEUE_SEND_FREQUENCY_MS );

		/* Send to the queue - causing the queue receive task to unblock and
		toggle the LED.  0 is used as the block time so the sending operation
		will not block - it shouldn't need to block as the queue should always
		be empty at this point in the code. */
		xQueueSend( xQueue, &ulValueToSend, 0U );
	}
}
/*-----------------------------------------------------------*/

static void prvQueueReceiveTask( void *pvParameters )
{
unsigned long ulReceivedValue;
static const TickType_t xShortBlock = pdMS_TO_TICKS( 50 );

	/* Check the task parameter is as expected. */
	configASSERT( ( ( unsigned long ) pvParameters ) == mainQUEUE_RECEIVE_PARAMETER );

	for( ;; )
	{
		/* Wait until something arrives in the queue - this task will block
		indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
		FreeRTOSConfig.h. */
		xQueueReceive( xQueue, &ulReceivedValue, portMAX_DELAY );

		/*  To get here something must have been received from the queue, but
		is it the expected value?  If it is, toggle the LED. */
		if( ulReceivedValue == 100UL )
		{
			/* Blip the LED for a short while so as not to use too much
			power. */
			//configTOGGLE_LED();
            GPIOPinWrite( GPIO_PORTF_BASE, mainLED_RED, mainLED_RED );
			vTaskDelay( xShortBlock );
            GPIOPinWrite( GPIO_PORTF_BASE, mainLED_RED, 0 );
			ulReceivedValue = 0U;
		}
	}
}
/*-----------------------------------------------------------*/
static void prvButtonHandlerTask( void *pvParameters )
{
//const char *pcInterruptMessage = "Int";
	
     
	for( ;; )
	{
		/* Wait for a GPIO interrupt to wake this task. */
		while( xSemaphoreTake( xButtonSemaphore, portMAX_DELAY ) != pdPASS );
		/* Start the Tx of the message on the UART. */
		UARTIntDisable( UART0_BASE, UART_INT_TX );
		{
			pcNextChar = cMessage;

			/* Send the first character. */
			if( !( HWREG( UART0_BASE + UART_O_FR ) & UART_FR_TXFF ) )
			{
				HWREG( UART0_BASE + UART_O_DR ) = *pcNextChar;
			}

			pcNextChar++;
		}
		UARTIntEnable(UART0_BASE, UART_INT_TX);


		/* Make sure we don't process bounces. */
		vTaskDelay( mainDEBOUNCE_DELAY );
		xSemaphoreTake( xButtonSemaphore, mainNO_DELAY );
	}
}



/*-----------------------------------------------------------*/
void vGPIOF_ISR( void )
{
portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    
    uint32_t s = GPIOIntStatus(GPIO_PORTF_BASE, true);
	/* Clear the interrupt. */
	GPIOIntClear(GPIO_PORTF_BASE, s);
    
	/* Wake the button handler task. */
	xSemaphoreGiveFromISR( xButtonSemaphore, &xHigherPriorityTaskWoken );
    
	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
    
}

void vUART0_ISR( void )
{
unsigned long ulStatus;

	/* What caused the interrupt. */
	ulStatus = UARTIntStatus( UART0_BASE, pdTRUE );

	/* Clear the interrupt. */
	UARTIntClear( UART0_BASE, ulStatus );

	/* Was a Tx interrupt pending? */
	if( ulStatus & UART_INT_TX )
	{
		/* Send the next character in the string.  We are not using the FIFO. */
		if( *pcNextChar != 0 )
		{
			if( !( HWREG( UART0_BASE + UART_O_FR ) & UART_FR_TXFF ) )
			{
				HWREG( UART0_BASE + UART_O_DR ) = *pcNextChar;
			}
			pcNextChar++;
		}
	}
}

void vPreSleepProcessing( uint32_t ulExpectedIdleTime )
{
}

void vApplicationIdleHook( void )
{
}

void vApplicationTickHook( void )
{
	/* This function will be called by each tick interrupt if
	configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
	added here, but the tick hook is called from an interrupt context, so
	code must not attempt to block, and only the interrupt safe FreeRTOS API
	functions can be used (those that end in FromISR()). */

	/* Only the full demo uses the tick hook so there is no code is
	executed here. */
}

void vApplicationMallocFailedHook( void );
void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for( ;; );

}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char* pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
