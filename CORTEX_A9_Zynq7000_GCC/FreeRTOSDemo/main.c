/*
 * FreeRTOS V202212.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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

/* FreeRTOS includes. */
#include "FreeRTOS.h"

/* Test includes. */
#include "TestRunner.h"

/* Xilinx includes. */
#include "xscugic.h"

/*
 * The Xilinx projects use a BSP that do not allow the start up code to be
 * altered easily. Therefore the vector table used by FreeRTOS is defined in
 * FreeRTOS_asm_vectors.S, which is part of this project. Switch to use the
 * FreeRTOS vector table.
 */
extern void vPortInstallFreeRTOSVectorTable( void );

/*
 * Configure the hardware as necessary to run this demo.
 */
static void prvSetupHardware( void );


int main(void){

	configPRINTF( ("------------------ New Test Session ------------------\r\n") );

	/* Startup and Hardware initialization. */
	prvSetupHardware();

	/* Setup Percepio View. */
	#if ( configUSE_PERCEPIO_VIEW == 1 )
		#if ( configNUMBER_OF_CORES > 1 )
			/* Configure the timer used for the timestamps. */
			vTraceSetupGlobalTimer();
			/* Set up and start the Percepio View trace recorder. */
			xil_printf("Initialize trace w/Percepio View on %d cores\r\n", TRC_CFG_CORE_COUNT);
			xTraceEnable(TRC_START);
		#endif
	#endif

	/* Start tests. */
	vStartTests();

	/* Should never reach here. */
	for( ; ; );

	return 0;
}

/*----------------------------------------------------*/
static void prvSetupHardware( void )
{
	XScuGic_Config *pxGICConfig;

	/* Ensure no interrupts execute while the scheduler is in an inconsistent
	state. Interrupts are automatically enabled when the scheduler is
	started. */
	portDISABLE_INTERRUPTS();

	/* Obtain the configuration of the GIC. */
	pxGICConfig = XScuGic_LookupConfig( XPAR_SCUGIC_SINGLE_DEVICE_ID );
	( void ) pxGICConfig; /* Prevent compiler warning when configASSERT() is not defined. */

	/* Sanity check the FreeRTOSConfig.h settings are correct for the
	hardware. */
	configASSERT( pxGICConfig );
	configASSERT( pxGICConfig->CpuBaseAddress == ( configINTERRUPT_CONTROLLER_BASE_ADDRESS + configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET ) );
	configASSERT( pxGICConfig->DistBaseAddress == configINTERRUPT_CONTROLLER_BASE_ADDRESS );

	#if ( configNUMBER_OF_CORES > 1 )
		/* Test IC init function. */	
		void vInitialiseInterruptController( void );
	#endif
}
