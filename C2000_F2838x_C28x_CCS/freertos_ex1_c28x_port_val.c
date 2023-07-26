//#############################################################################
//
// FILE:   freertos_ex1_c28x_port_val.c
//
// TITLE:  FreeRTOS C28x Port Validation
//
//! This example validates the FreeRTOS C28x port and is based on the project
//! template detailed in the below shown link:
//! https://github.com/FreeRTOS/FreeRTOS/blob/main/FreeRTOS/Demo/ThirdParty/Template/README.md
//! 
//! The project configures following tests for the c28x port and periodically
//! blinks LED2 available on the controlcard.
//! #define configSTART_TASK_NOTIFY_TESTS             1
//! #define configSTART_TASK_NOTIFY_ARRAY_TESTS       1
//! #define configSTART_BLOCKING_QUEUE_TESTS          1
//! #define configSTART_SEMAPHORE_TESTS               1
//! #define configSTART_POLLED_QUEUE_TESTS            1
//! #define configSTART_INTEGER_MATH_TESTS            1
//! #define configSTART_GENERIC_QUEUE_TESTS           1
//! #define configSTART_PEEK_QUEUE_TESTS              1
//! #define configSTART_MATH_TESTS                    1
//! #define configSTART_RECURSIVE_MUTEX_TESTS         1
//! #define configSTART_COUNTING_SEMAPHORE_TESTS      1
//! #define configSTART_QUEUE_SET_TESTS               1
//! #define configSTART_QUEUE_OVERWRITE_TESTS         1
//! #define configSTART_EVENT_GROUP_TESTS             1
//! #define configSTART_INTERRUPT_SEMAPHORE_TESTS     1
//! #define configSTART_QUEUE_SET_POLLING_TESTS       1
//! #define configSTART_BLOCK_TIME_TESTS              1
//! #define configSTART_ABORT_DELAY_TESTS             1
//! #define configSTART_MESSAGE_BUFFER_TESTS          1
//! #define configSTART_STREAM_BUFFER_TESTS           1
//! #define configSTART_STREAM_BUFFER_INTERRUPT_TESTS 1
//! #define configSTART_TIMER_TESTS                   1
//! #define configSTART_REGISTER_TESTS                1
//! #define configSTART_DELETE_SELF_TESTS             1
//! 
//! For running the application open the COM port with the following settings
//! using a terminal:
//!  -  Find correct COM port
//!  -  Bits per second = 9600
//!  -  Data Bits = 8
//!  -  Parity = None
//!  -  Stop Bits = 1
//!  -  Hardware Control = None
//!  The program will print out the test results on COM port
//! 
//! External Connections:
//! Connect the SCI-A port to a PC via a transceiver and cable.
//! 
//! Watch Variables:
//!  - pcStatusMessage: Captures the validation result. The same result can also
//!                     be checked over COM port.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.co/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//
#include <stdio.h>
#include "driverlib.h"
#include "device.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "TestRunner.h"
#include <assert.h>
#include <file.h>
#include "uart_drv.h"

//
// Globals
//
static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];
#pragma DATA_SECTION(uxIdleTaskStack,   ".freertosStaticStack")

static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];
#pragma DATA_SECTION(uxTimerTaskStack,   ".freertosStaticStack")

#if(configAPPLICATION_ALLOCATED_HEAP == 1)
uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
#pragma DATA_SECTION(ucHeap,   ".freertosHeap")
#endif

//
// Function Declarations
//
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName);
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationTickHook(void);
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize );
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize );
void vApplicationSetupTimerInterrupt( void );
void vMainAssertCalled( const char *pcFileName, uint32_t ulLineNumber );
void vMainToggleLED( void );
void configCPUTimer(uint32_t cpuTimer, uint32_t period);
#if defined(__TI_EABI__)
void *malloc( size_t xSize );
#pragma WEAK (malloc)
#endif

//
// UART stdout redirection configuration related APIs
//
void UartSetup();
void UartPutChar(uint16_t charToWrite);

extern int checkPrintf();

void main(void)
{
    /* Startup and Hardware initialization. */
    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Initializes PIE and clears PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    Device_initGPIO();
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);

    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1);
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 1);

    //
	// Disable all the interrupts and clear all CPU interrupt flags:
	//
	DINT;
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initializes the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Redirect STDOUT to SCI
    //
    //**************************************************************************
    // NOTE: SCI Configuration for this example is done in UartSetup()
    // As an alternative, the user can configure SCI here in the main, and then
    // provide an empty UartSetup() function. UartSetup() must be defined, even
    // if it is empty.
    //**************************************************************************
    FILE *uart = NULL;

    //
    // Add the UART device.  When fopen is called with a filename that
    // begins "uart:", the UART device will be used to handle the file.
    //
    add_device("uart",
               _SSA,
               UART_open,
               UART_close,
               UART_read,
               UART_write,
               UART_lseek,
               UART_unlink,
               UART_rename);

    //
    // Assign stdout to be a UART device!
    //
    assert(freopen("uart:", "w", stdout) != NULL);

    //
    // Uncomment to check printf() functionality
    // if no output is seen on COM port.
    // checkPrintf();

    /* Start tests. */
    vStartTests();

    /* Should never reach here. */
    for( ; ; );
}

//
// Configures the timer used for generating the FreeRTOS tick interrupt
//
void vApplicationSetupTimerInterrupt( void )
{
    // Start the timer than activate timer interrupt to switch into first task.
    Interrupt_register(INT_TIMER2, &portTICK_ISR);

    CPUTimer_setPeriod(CPUTIMER2_BASE, 0xFFFFFFFF);
    CPUTimer_setPreScaler(CPUTIMER2_BASE, 0);
    CPUTimer_stopTimer(CPUTIMER2_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER2_BASE);

    configCPUTimer(CPUTIMER2_BASE, 1000000 / configTICK_RATE_HZ);

    CPUTimer_enableInterrupt(CPUTIMER2_BASE);

    Interrupt_enable(INT_TIMER2);
    CPUTimer_startTimer(CPUTIMER2_BASE);
}

//
// Application must provide an implementation of vApplicationGetIdleTaskMemory()
// to provide the memory that is used by the Idle task if configUSE_STATIC_ALLOCATION
// is set to 1.
//
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
    /* If the buffers to be provided to the Idle task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

//
// Application must provide an implementation of vApplicationGetTimerTaskMemory()
// to provide the memory that is used by the Timer service task if both
// configUSE_STATIC_ALLOCATION and configUSE_TIMERS are set to 1.
//
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
    /* If the buffers to be provided to the Timer task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

//
// Hook function for catching pvPortMalloc() failures
//
void vApplicationMallocFailedHook( void )
{
    /* vApplicationMallocFailedHook() will only be called if
    configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
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

//
// Hook function for idle task
//
void vApplicationIdleHook( void )
{
    /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
    to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
    task.  It is essential that code added to this hook function never attempts
    to block in any way (for example, call xQueueReceive() with a block time
    specified, or call vTaskDelay()).  If the application makes use of the
    vTaskDelete() API function (as this demo application does) then it is also
    important that vApplicationIdleHook() is permitted to return to its calling
    function, because it is the responsibility of the idle task to clean up
    memory allocated by the kernel to any task that has since been deleted. */
}

//
// Checks run time stack overflow
//
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */
    taskDISABLE_INTERRUPTS();
    for( ;; );
}

//
// Catch asserts so the file and line number of the assert can be viewed.
//
void vMainAssertCalled( const char *pcFileName, uint32_t ulLineNumber )
{
volatile BaseType_t xSetToNonZeroToStepOutOfLoop = 0;

    taskENTER_CRITICAL();
    while( xSetToNonZeroToStepOutOfLoop == 0 )
    {
        /* Use the variables to prevent compiler warnings and in an attempt to
        ensure they can be viewed in the debugger.  If the variables get
        optimised away then set copy their values to file scope or globals then
        view the variables they are copied to. */
        ( void ) pcFileName;
        ( void ) ulLineNumber;
    }
}

#if defined(__TI_EABI__)
//
// Traps malloc calls
//
void *malloc( size_t xSize )
{
    /* There should not be a heap defined, so trap any attempts to call
    malloc. */
    taskDISABLE_INTERRUPTS();
    for( ;; );
}
#endif

//
// Toggles onboard LED2
//
void vMainToggleLED( void )
{
    GPIO_togglePin(DEVICE_GPIO_PIN_LED2);
}

//
// configCPUTimer - This function initializes the selected timer to the
// period specified by the "freq" and "period" variables. The "freq" is
// CPU frequency in Hz and the period in uSeconds. The timer is held in
// the stopped state after configuration.
//
void
configCPUTimer(uint32_t cpuTimer, uint32_t period)
{
    uint32_t temp, freq = DEVICE_SYSCLK_FREQ;

    //
    // Initialize timer period:
    //
    temp = ((freq / 1000000) * period);
    CPUTimer_setPeriod(cpuTimer, temp);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);

}

//
// Configures SCIA
//
void UartSetup()
{
    //
    // DEVICE_GPIO_PIN_SCIRXDA is the SCI Rx pin.
    //
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCIRXDA, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_QUAL_ASYNC);

    //
    // DEVICE_GPIO_PIN_SCITXDA is the SCI Tx pin.
    //
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCITXDA, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_QUAL_ASYNC);

    //
    // Initialize SCIA and its FIFO.
    //
    SCI_performSoftwareReset(SCIA_BASE);

    //
    // Configure SCIA with FIFO
    //
    SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, 9600, (SCI_CONFIG_WLEN_8 |
                                                        SCI_CONFIG_STOP_ONE |
                                                        SCI_CONFIG_PAR_NONE));
    SCI_resetChannels(SCIA_BASE);
    SCI_resetRxFIFO(SCIA_BASE);
    SCI_resetTxFIFO(SCIA_BASE);
    SCI_enableFIFO(SCIA_BASE);
    SCI_enableModule(SCIA_BASE);
    SCI_performSoftwareReset(SCIA_BASE);
}

//
// Implements SCI based putchar()
//
void UartPutChar(uint16_t charToWrite)
{
    SCI_writeCharBlockingFIFO(SCIA_BASE, charToWrite);
}

//
// End of File
//
