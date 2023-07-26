//#############################################################################
//
// FILE:   freertos_ex4_c28x_interrupt_latency.c
//
// TITLE:  FreeRTOS C28x Zero latency Interrupt
//
//! This example demonstrates usage of interrupts along with RTOS functionality.
//! Two tasks are configured which access a shared resource to do some work.
//! CPUTimer1 is configured with 1sec period and the interrupt latency is measured
//! through ERAD IP.
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
//!  - time_isr: Time taken by CPUTimer1 ISR
//!  - number_of_interrupts: Number of timer1 interrupts generated
//!  - number_of_executions: Number of times CPUTimer1 ISR got executed
//!  - time_bw_int_ex: cycles elapsed between timer1 interrupt and execution
//!                    of the CPUTimer1 ISR
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
/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <file.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Device specific includes */
#include "driverlib.h"
#include "device.h"

/* STDOUT redirection specific includes*/
#include "uart_drv.h"
#include "sci.h"

//
// Macro to define stack size of individual tasks
//
#define TASK1_STACK_SIZE 256
#define TASK2_STACK_SIZE 256

//
// Macro to define priorities of individual tasks
//
#define TASK1_PRIORITY   4
#define TASK2_PRIORITY   2

//
// Macro to define delay(in ticks) between LED toggle
// in tasks. This delay determines the LED toggle
// frequency within a task.
// Note: 1 tick is configured as 1ms in FreeRTOSConfig.h
//
#define TASK1_BLINK_DELAY 500
#define TASK2_BLINK_DELAY 1500
#define LED_TASK_BLOCK_TICKS  10

//
// Macro to define task duration(in ticks)
//
#define TASK1_DURATION  10000
#define TASK2_DURATION  10000

#define STACK_SIZE  256U

// Uncomment to enable profiling
#define ENABLE_PROFILING

//
// Globals
//

//
// Task handles
//
TaskHandle_t task1Handle, task2Handle;

//
// Execution counters
//
static uint32_t ctrTask1, ctrTask2;

//
// The mutex that protects concurrent access of resource from multiple tasks.
//
xSemaphoreHandle semHandle;

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

uint32_t resource = 0;

//
// ERAD specific declarations
//
//
// Threshold for COUNTER1 to generate interrupt
// Interrupt is invoked if the ISR takes more than 800 cycles to complete
//
const uint16_t threshold = 800;

//
// Variable accessed at the end of the ISR. We are interested in measuring the
// time between the start if ISR to the write to this variable
//
uint64_t cpuTimer1IntCount = 0;

//
// Time taken by ISR to complete
//
uint32_t time_isr = 0;

//
// Number of interrupts generated
//
uint32_t number_of_interrupts = 0;

//
// Number of times the ISR actually gets executed
//
uint32_t number_of_executions = 0;

//
// Time elapsed between the interrupt and the execution of the ISR
//
uint32_t time_bw_int_ex = 0;

//
// Variable to show RTOS interrupt was invoked
//
bool RTOSintCount = 0;

//
// Function Declarations
//
void task1Fxn(void *pvParameters);
void task2Fxn(void *pvParameters);

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
void configCPUTimer(uint32_t cpuTimer, uint32_t period);
#if defined(__TI_EABI__)
void *malloc( size_t xSize );
#pragma WEAK (malloc)
#endif

//
// UART stdout redirection configuration related functions
//
void UartSetup();
void UartPutChar(uint16_t charToWrite);

//
// Function to initialize CPU Timer 1
//
void initCPUTimer1();

//
// ISR
//
__interrupt void cpuTimer1ISR(void) __attribute__((ramfunc));
interrupt void RTOSISR(void) __attribute__((ramfunc));
void configERAD(void);

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
    // ISRs for RTOS interrupt
    //
    Interrupt_register(INT_RTOS, &RTOSISR);
    Interrupt_enableInCPU(INTERRUPT_CPU_RTOSINT);

    //
    // Configure the ERAD module
    //
    configERAD();

    //
    // Enable the necessary sub-modules in ERAD
    //
    ERAD_enableModules(ERAD_INST_BUSCOMP1 | ERAD_INST_BUSCOMP2 |
                       ERAD_INST_COUNTER1 | ERAD_INST_COUNTER2 |
                       ERAD_INST_COUNTER3 | ERAD_INST_COUNTER4);

    //
    // Configure CPU Timer 1
    //
    initCPUTimer1();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;


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
    // Create a mutex to guard the resource.
    //
    semHandle = xSemaphoreCreateMutex();

    if(semHandle != NULL)
    {
        //
        // Create tasks to toggle LEDs at varying frequency
        //
        if(xTaskCreate(task1Fxn, (const char *)"Task1", TASK1_STACK_SIZE, NULL,
                       (tskIDLE_PRIORITY + TASK1_PRIORITY), &task1Handle) != pdTRUE)
        {
            ESTOP0;
        }

        if(xTaskCreate(task2Fxn, (const char *)"Task2", TASK2_STACK_SIZE, NULL,
                       (tskIDLE_PRIORITY + TASK2_PRIORITY), &task2Handle) != pdTRUE)
        {
            ESTOP0;
        }

        //
        // Start the scheduler.  This should not return.
        //
        vTaskStartScheduler();
    }

    /* Should never reach here. */
    for( ; ; );
}

//
// Task1 Fxn - Task function for task 1
//
void task1Fxn(void *pvParameters)
{
    while(1)
    {
        if(xSemaphoreTake(semHandle, portMAX_DELAY) == pdPASS)
        {
            //
            // Do work on locked resource and access the stdout
            //
            resource += 1;

            //
            // Increment counter
            //
            ctrTask1++;

            //
            // Give semaphore
            //
            xSemaphoreGive(semHandle);

            // Uncomment for console ouput
            // printf("Task1 is running\r\n");

            //
            // Put the task in blocked state
            //
            vTaskDelay(LED_TASK_BLOCK_TICKS);
        }
    }
}

//
// led Task2 Func - Task function for led task 2
//
void task2Fxn(void *pvParameters)
{
    while(1)
    {
        if(xSemaphoreTake(semHandle, portMAX_DELAY) == pdPASS)
        {
            //
            // Do work on locked resource and access the stdout
            //
            resource += 1;

            //
            // Increment counter
            //
            ctrTask2++;

            //
            // Give semaphore
            //
            xSemaphoreGive(semHandle);

            // Uncomment for console ouput
            // printf("Task2 is running\r\n");

            //
            // Put the task in blocked state
            //
            vTaskDelay(LED_TASK_BLOCK_TICKS);
        }
    }
}

//
// vApplicationSetupTimerInterrupt Configures the timer used for generating
// the FreeRTOS tick interrupt
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
// vApplicationGetIdleTaskMemory - Application must provide an implementation
// of vApplicationGetIdleTaskMemory() to provide the memory that is used by
// the Idle task if configUSE_STATIC_ALLOCATION is set to 1.
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
// vApplicationGetTimerTaskMemory - Application must provide an implementation
// of vApplicationGetTimerTaskMemory() to provide the memory that is used by
// the Timer service task if both configUSE_STATIC_ALLOCATION and
// configUSE_TIMERS are set to 1.
//
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
    /* If the buffers to be provided to the Timer task are declared inside this
    function then they must be declared static - otherwise they will be allocated
    on the stack and so not exists after this function exits. */

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
// vApplicationMallocFailedHook - Hook function for catching pvPortMalloc()
// failures
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
// vApplicationIdleHook - Hook function for idle task
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
// vApplicationTickHook - Hook function for tick interrupt
//
void vApplicationTickHook( void )
{
    /* vApplicationTickHook() will only be called if configUSE_TICK_HOOK is set
    to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the tick ISR.
    It is essential that code added to this hook function never attempts
    to block in any way. */
}

//
// vApplicationStackOverflowHook - Checks run time stack overflow
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
// vMainAssertCalled - Catch asserts so the file and line number of the assert
// can be viewed.
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
// malloc - Traps malloc calls
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
// configCPUTimer - This function initializes the selected timer to the
// period specified by the "freq" and "period" variables. The "freq" is
// CPU frequency in Hz and the period in uSeconds. The timer is held in
// the stopped state after configuration.
//
void configCPUTimer(uint32_t cpuTimer, uint32_t period)
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
// init Zero Latency Interrupts - Initialize interrupts outside of RTOS context
//
void initCPUTimer1()
{
    //
    // Configure Timer 1 interrupt
    //
    Interrupt_register(INT_TIMER1, &cpuTimer1ISR);

    CPUTimer_setPeriod(CPUTIMER1_BASE, 0xFFFFFFFF);
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 0);
    CPUTimer_stopTimer(CPUTIMER1_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);

    configCPUTimer(CPUTIMER1_BASE, 1000000);

    CPUTimer_enableInterrupt(CPUTIMER1_BASE);

    Interrupt_enable(INT_TIMER1);
    CPUTimer_startTimer(CPUTIMER1_BASE);
}

//
// cpuTimer1ISR - Counter for CpuTimer1
//
__interrupt void cpuTimer1ISR(void)
{
    //
    // Simulate storing data to a location. "volatile" keyword ensures this is
    // not optimized out by the compiler.
    //
    volatile uint32_t output;

    //
    // Simulate a task that can take some time to complete.
    //
    uint32_t i;
    for(i = 0; i < 50; i++)
    {
        output = i;
    }

    //
    // The CPU acknowledges the interrupt. We are interested in the ISR
    // until here. Rest is to display the results.
    //
    cpuTimer1IntCount++;

    //
    // Get all the profiling related values
    //
    time_isr             = ERAD_getMaxCount(ERAD_COUNTER1_BASE);
    number_of_interrupts = ERAD_getCurrentCount(ERAD_COUNTER2_BASE);
    number_of_executions = ERAD_getCurrentCount(ERAD_COUNTER3_BASE);
    time_bw_int_ex       = ERAD_getMaxCount(ERAD_COUNTER4_BASE);
    ERAD_setMaxCount(ERAD_COUNTER1_BASE, 0);
    ERAD_setMaxCount(ERAD_COUNTER4_BASE, 0);
}

//
// RTOSISR - ISR to be executed if counter generates RTOS interrupt
//
interrupt void RTOSISR(void)
{
    //
    // Variable to show that ISR executed
    //
    RTOSintCount++;
    ESTOP0;
}

//
// configERAD - Configure ERAD for profiling ISR
//
void configERAD(void)
{
    ERAD_BusComp_Config buscomp_params;
    ERAD_Counter_Config counter_params;

    //
    // Initialize the ERAD module with the APPLICATION as owner
    //
    ERAD_initModule(ERAD_OWNER_APPLICATION);

    //
    // Configure BUSCOMP1 to generate an event when the ISR begins
    // execution
    //
    buscomp_params.bus_sel     = ERAD_BUSCOMP_BUS_VPC;
    buscomp_params.reference   = (uint32_t)&cpuTimer1ISR;
    buscomp_params.mask        = 0x0;
    buscomp_params.comp_mode   = ERAD_BUSCOMP_COMPMODE_EQ;
    buscomp_params.enable_stop = 0;
    buscomp_params.enable_int  = 0;
    ERAD_configBusComp(ERAD_HWBP1_BASE, buscomp_params);

    //
    // Configure BUSCOMP2 to generate and event when there is write to
    // cpuTimer1IntCount.
    //
    buscomp_params.bus_sel     = ERAD_BUSCOMP_BUS_DWAB;
    buscomp_params.reference   = (uint32_t)&cpuTimer1IntCount;
    buscomp_params.mask        = 0x0;
    buscomp_params.comp_mode   = ERAD_BUSCOMP_COMPMODE_EQ;
    buscomp_params.enable_stop = 0;
    buscomp_params.enable_int  = 0;
    ERAD_configBusComp(ERAD_HWBP2_BASE, buscomp_params);

    //
    // Time spent between the start of execution and the write to
    // cpuTimer1IntCount is what is of interest.
    // Configure COUNTER1 to measure CPU cycles elapsed between them
    // (between the BUSCOMP1 event to BUSCOMP2 event)
    //
    counter_params.event        = ERAD_EVENT_NO_EVENT;
    counter_params.event_mode   = ERAD_COUNTER_MODE_ACTIVE;
    counter_params.reference    = threshold;
    counter_params.rst_on_match = 0;
    counter_params.enable_stop  = 0;
    counter_params.enable_int   = 1;
    ERAD_configCounterInStartStopMode(ERAD_COUNTER1_BASE, counter_params,
                                      ERAD_EVENT_HWBP1, ERAD_EVENT_HWBP2);

    //
    // Configure COUNTER2 to count the number of interrupts that are raised
    //
    counter_params.event        = ERAD_EVENT_TIMER1_TINT1;
    counter_params.event_mode   = ERAD_COUNTER_MODE_RISING_EDGE;
    counter_params.reference    = 0x0;
    counter_params.rst_on_match = 0;
    counter_params.enable_stop  = 0;
    counter_params.enable_int   = 0;
    ERAD_configCounterInCountingMode(ERAD_COUNTER2_BASE, counter_params);

    //
    // Configure COUNTER3 to count the number of times the ISR is executed
    // (the number of times the BUSCOMP1 event has occurred)
    //
    counter_params.event        = ERAD_EVENT_HWBP1;
    counter_params.event_mode   = ERAD_COUNTER_MODE_RISING_EDGE;
    counter_params.reference    = 0x0;
    counter_params.rst_on_match = 0;
    counter_params.enable_stop  = 0;
    counter_params.enable_int   = 0;
    ERAD_configCounterInCountingMode(ERAD_COUNTER3_BASE, counter_params);

    //
    // Configure COUNTER4 to count the number of CPU cycles that elapsed
    // between the interrupt and the actual execution of the ISR
    //
    counter_params.event        = ERAD_EVENT_NO_EVENT;
    counter_params.event_mode   = ERAD_COUNTER_MODE_ACTIVE;
    counter_params.reference    = 0x0;
    counter_params.rst_on_match = 0;
    counter_params.enable_stop  = 0;
    counter_params.enable_int   = 0;
    ERAD_configCounterInStartStopMode(ERAD_COUNTER4_BASE, counter_params,
                                      ERAD_EVENT_TIMER1_TINT1, ERAD_EVENT_HWBP1);
}

//
// UartSetup - Configures SCIA
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
// UartPutChar - Implements SCI based putchar()
//
void UartPutChar(uint16_t charToWrite)
{
    SCI_writeCharBlockingFIFO(SCIA_BASE, charToWrite);
}

//
// End of File
//
