## Zynq7000 Test Demo

### Introduction

This folder contains a test demo for the FreeRTOS [Zynq7000 port](https://github.com/FreeRTOS/FreeRTOS-Kernel-Community-Supported-Ports/pull/21). __The demo supports both single core and multi core (SMP) testing__, even though, in the latter case, a few changes to the tests are required. This is necessary because the FreeRTOS tests were designed for single core so some assumptions may not hold true when multiple cores are available.

The demo has been developed starting from the test [template](https://github.com/FreeRTOS/FreeRTOS/blob/main/FreeRTOS/Demo/ThirdParty/Template/) and the [ZC702 demo](https://github.com/FreeRTOS/FreeRTOS/tree/main/FreeRTOS/Demo/CORTEX_A9_Zynq_ZC702) on the FreeRTOS repository.

### Organization

[`FreeRTOSDemo`](FreeRTOSDemo/) contains the files that implement the test demo. The files in the [`Demo`](FreeRTOSDemo/Demo/) folder are located in this subdirectory so that the user can implement different test demos in separate directories and run them from the same `main.c`. The `main` function also provides an example on how to initialize Percepio View in SMP.

No BSP folder is included because the demo does not target any specific board.

### Development environment

The demo has been developed with [Vitis 2021.1](https://www.xilinx.com/support/download.html) and [Vivado 2021.1](https://www.xilinx.com/support/download.html) on a [TUL Pynq-Z2](https://www.tulembedded.com/fpga/ProductsPYNQ-Z2.html). 

### Usage

1. Create a project in Vitis and import FreeRTOS as explained [here](https://github.com/Matth9814/FreeRTOS-Kernel-Community-Supported-Ports/blob/main/GCC/CORTEX_A9_Zynq7000/README.md).

2. Compile the following additional files in your project:
    * All files in the [FreeRTOS/Demo/Common/Minimal](https://github.com/FreeRTOS/FreeRTOS/tree/main/FreeRTOS/Demo/Common/Minimal) directory except `comtest_strings.c`, `crhook.c` , `comtest.c` ,`crflash.c`,`flash.c`, `flash_timer.c` and `sp_flop.c`.
3. Add the following paths to your include search path:
   * `FreeRTOS/Demo/Common/include`. 

    __NOTE:__ 2. and 3. are part of the official [test project creation guide](https://github.com/FreeRTOS/FreeRTOS/blob/main/FreeRTOS/Demo/ThirdParty/Template/README.md#:~:text=Project%20Configuration) available on the FreeRTOS repository.

4. Add source and headers in [`FreeRTOSDemo`](FreeRTOSDemo/) directory into the project and use the provided [`FreeRTOSConfig.h`](FreeRTOSDemo/Demo/FreeRTOSConfig.h) as template to configure the test program. Some macros need to be set appropriately:
    * `#define configTICK_RATE_HZ   ( ( TickType_t ) 1000 )` \
    A tick rate of 100Hz would not allow to define a reasonable margin on some tests that need to respect certain timings in order to pass (e.g. `xAllowableMargin` in `MessageBufferDemo.c`).

    * `#define configPRINTF( X )    /* thread-safe printf */` \
    The macro should be defined as a thread-safe print function. However, in some cases, a simple `xil_printf()` could do the job as well.

    * `#define configSTART_xxx_TESTS`
    A set of macro defined in the _Demo definitions_ section. Set one of them to `1` to enable the corrsponding test, to `0` otherwise.

At this point, it is already possible to test the single core port but for the SMP port a few more steps are required.
As mentioned earlier, some test files need to be modified to preserve the assumptions they were designed with and/or adjust them to a multi core environment:

* `FreeRTOSConfig.h`
    * `#define configRUN_MULTIPLE_PRIORITIES    0` \
    Ensures the "single core logic" of most of the tests is not invalidated by the availability of multiple cores.
    From a practical prospective, enabling this option will make the program assert in some tests (e.g. `GenQTest.c`).  

    * `#define configUSE_CORE_AFFINITY          1` \
    Some tasks with the same priority need to be bound to a specific core to preserve the test logic. 


* `StreamBufferDemo.c`
```C

/* --- CODE TO ADD --- */

/* The core where the non blocking tasks are executed. */
#if ( configNUMBER_OF_CORES > 1 )
	#ifndef configSTREAM_BUFFER_NON_BLOCKING_TASKS_CORE
		#define sbNON_BLOCKING_TASKS_CORE 	(1 << 0)
	#else
		#define sbNON_BLOCKING_TASKS_CORE	(1 << configSTREAM_BUFFER_NON_BLOCKING_TASKS_CORE)
	#endif
#endif

/* Other code */ 

void vStartStreamBufferTasks( void )
{

    /* --- CODE TO MODIFY --- */

    /* The non blocking tasks run continuously and will interleave with each
    * other, so must be created at the lowest priority.  The stream buffer they
    * use is created and passed in using the task's parameter. */
    xStreamBuffer = xStreamBufferCreate( sbSTREAM_BUFFER_LENGTH_BYTES, sbTRIGGER_LEVEL_1 );
    #if ( configNUMBER_OF_CORES == 1 )
        xTaskCreate( prvNonBlockingReceiverTask, "StrNonBlkRx", configMINIMAL_STACK_SIZE, ( void * ) xStreamBuffer, tskIDLE_PRIORITY, NULL );
        xTaskCreate( prvNonBlockingSenderTask, "StrNonBlkTx", configMINIMAL_STACK_SIZE, ( void * ) xStreamBuffer, tskIDLE_PRIORITY, NULL );
    #else
        /* The tasks are bounded on one core */
        xTaskCreateAffinitySet( prvNonBlockingReceiverTask, "StrNonBlkRx", configMINIMAL_STACK_SIZE, ( void * ) xStreamBuffer, tskIDLE_PRIORITY, sbNON_BLOCKING_TASKS_CORE, NULL );
        xTaskCreateAffinitySet( prvNonBlockingSenderTask, "StrNonBlkTx", configMINIMAL_STACK_SIZE, ( void * ) xStreamBuffer, tskIDLE_PRIORITY, sbNON_BLOCKING_TASKS_CORE, NULL );
    #endif

}
```
The test implemented with `prvNonBlockingReceiverTask` and `prvNonBlockingSenderTask` is based on the assumption that these tasks interleave their execution. To ensure this remains true and they do not execute at the same time on different cores, the tasks are bounded to a single core.  


* `MessageBufferDemo.c`
```C

/* --- CODE TO ADD --- */

/* The core where the non blocking tasks are executed. */
#if ( configNUMBER_OF_CORES > 1 )
	#ifndef configMESSAGE_BUFFER_NON_BLOCKING_TASKS_CORE
		#define mbNON_BLOCKING_TASKS_CORE 	(1 << 0)
	#else
		#define mbNON_BLOCKING_TASKS_CORE	(1 << configMESSAGE_BUFFER_NON_BLOCKING_TASKS_CORE)
	#endif
#endif

/* Other code */ 

void vStartMessageBufferTasks( configSTACK_DEPTH_TYPE xStackSize )
{
    /* --- CODE TO MODIFY --- */

    /* The non blocking tasks run continuously and will interleave with each
     * other, so must be created at the lowest priority.  The message buffer they
     * use is created and passed in using the task's parameter. */
    xMessageBuffer = xMessageBufferCreate( mbMESSAGE_BUFFER_LENGTH_BYTES );
    #if ( configNUMBER_OF_CORES == 1 )
        xTaskCreate( prvNonBlockingReceiverTask, "NonBlkRx", xStackSize, ( void * ) xMessageBuffer, tskIDLE_PRIORITY, NULL );
        xTaskCreate( prvNonBlockingSenderTask, "NonBlkTx", xStackSize, ( void * ) xMessageBuffer, tskIDLE_PRIORITY, NULL );
	#else
		/* The tasks are bounded on one core */
		xTaskCreateAffinitySet( prvNonBlockingReceiverTask, "NonBlkRx", xStackSize, ( void * ) xMessageBuffer, tskIDLE_PRIORITY, mbNON_BLOCKING_TASKS_CORE, NULL );
		xTaskCreateAffinitySet( prvNonBlockingSenderTask, "NonBlkTx", xStackSize, ( void * ) xMessageBuffer, tskIDLE_PRIORITY, mbNON_BLOCKING_TASKS_CORE, NULL );
	#endif

    /* Code */ 
}
```
The code is changed for the same reason of `StreamBufferDemo.c`. However, in this case, the implementation of the non-blocking tasks causes the error to appear less frequently.  

* `IntQueue.c`
```C
BaseType_t xSecondTimerHandler( void )
{
    /* --- CODE TO MODIFY --- */

    if( uxNextOperation & ( UBaseType_t ) 0x01 )
    {
        #if ( configNUMBER_OF_CORES > 1 )
            UBaseType_t uxSavedInterrupt;
            uxSavedInterrupt = taskENTER_CRITICAL_FROM_ISR();
        #endif
        
        timerNORMALLY_EMPTY_TX();
        timerNORMALLY_EMPTY_TX();

        timerNORMALLY_EMPTY_RX();
        timerNORMALLY_EMPTY_RX();

        #if ( configNUMBER_OF_CORES > 1)
		    taskEXIT_CRITICAL_FROM_ISR( uxSavedInterrupt );
        #endif
    }
    else
    
    /* Other code */
}
```
Placing the code inside a critical section is necessary to avoid that the tasks that read `xNormallyEmptyQueue` are woken up and executed on the other core after an item is placed in the queue by `timerNORMALLY_EMPTY_TX()`.

```C
static void prvLowerPriorityNormallyEmptyTask( void * pvParameters )
{
    for( ; ; )
    {
        if( xQueueReceive( xNormallyEmptyQueue, &uxRxed, intqONE_TICK_DELAY ) != errQUEUE_EMPTY )
        {
            /* --- CODE TO MODIFY --- */
            
            #if ( configNUMBER_OF_CORES == 1 )
                /* A value should only be obtained when the high priority task is
                * suspended. */
                if( eTaskGetState( xHighPriorityNormallyEmptyTask1 ) != eSuspended )
                {
                    prvQueueAccessLogError( __LINE__ );
                }
            #endif

            /* Other code */
        }
    }
}

static void prvLowerPriorityNormallyFullTask( void * pvParameters )
{
    for( ; ; )
    {
        if( xQueueSend( xNormallyFullQueue, &uxTxed, intqONE_TICK_DELAY ) != errQUEUE_FULL )
        {
            /* --- CODE TO MODIFY --- */

            #if ( configNUMBER_OF_CORES == 1 )
                /* Should only succeed when the higher priority task is suspended */
                if( eTaskGetState( xHighPriorityNormallyFullTask1 ) != eSuspended )
                {
                    prvQueueAccessLogError( __LINE__ );
                }
            #endif

            /* Other code */
        }
    }
}
```
No assumption can be easily made on the state of other tasks when `configNUMBER_OF_CORES > 1` (FreeRTOS SMP). In multiple test sessions, the state of other tasks of the same test set has been observed to be very different from the predicted one.


### License
Distributed under the MIT License. See `LICENSE` for more information.