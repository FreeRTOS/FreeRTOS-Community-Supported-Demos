/*
 * Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com/
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
 */

#include "driverlib.h"
#include "device.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define STACK_SIZE  256U
#define RED         0xDEADBEAF
#define BLUE        0xBAADF00D

static StaticTask_t redTaskBuffer;
static StackType_t  redTaskStack[STACK_SIZE];

static StaticTask_t blueTaskBuffer;
static StackType_t  blueTaskStack[STACK_SIZE];

static StaticTask_t idleTaskBuffer;
static StackType_t  idleTaskStack[STACK_SIZE];

static SemaphoreHandle_t xSemaphore = NULL;
static StaticSemaphore_t xSemaphoreBuffer;

//-------------------------------------------------------------------------------------------------
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
    while(1);
}

//-------------------------------------------------------------------------------------------------
static void blueLedToggle(void)
{
    static uint32_t counter = 0;

    counter++;
    GPIO_writePin(31, counter & 1);
}

//-------------------------------------------------------------------------------------------------
static void redLedToggle(void)
{
    static uint32_t counter = 0;

    counter++;
    GPIO_writePin(34, counter & 1);
}

//-------------------------------------------------------------------------------------------------
static void ledToggle(uint32_t led)
{
    if(RED == led)
    {
        redLedToggle();
    }
    else
    if(BLUE == led)
    {
        blueLedToggle();
    } 
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

//-------------------------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------------------------
interrupt void timer1_ISR( void )
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xSemaphoreGiveFromISR( xSemaphore, &xHigherPriorityTaskWoken );

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

//-------------------------------------------------------------------------------------------------
static void setupTimer1( void )
{
    Interrupt_register(INT_TIMER1, &timer1_ISR);

    CPUTimer_setPeriod(CPUTIMER1_BASE, 0xFFFFFFFF);
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 0);
    CPUTimer_stopTimer(CPUTIMER1_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);

    configCPUTimer(CPUTIMER1_BASE, 100000);

    CPUTimer_enableInterrupt(CPUTIMER1_BASE);

    Interrupt_enable(INT_TIMER1);
    CPUTimer_startTimer(CPUTIMER1_BASE);
}

//-------------------------------------------------------------------------------------------------
void LED_TaskRed(void * pvParameters)
{
    for(;;)
    {
        if(xSemaphoreTake( xSemaphore, portMAX_DELAY ) == pdTRUE)
        {
            ledToggle((uint32_t)pvParameters);
        }
    }
}

//-------------------------------------------------------------------------------------------------
void LED_TaskBlue(void * pvParameters)
{
    for(;;)
    {
        ledToggle((uint32_t)pvParameters);
        vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}

//-------------------------------------------------------------------------------------------------
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
    *ppxIdleTaskTCBBuffer = &idleTaskBuffer;
    *ppxIdleTaskStackBuffer = idleTaskStack;
    *pulIdleTaskStackSize = STACK_SIZE;
}

//-------------------------------------------------------------------------------------------------
void main(void)
{
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

    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    DINT;


    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initializes the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    xSemaphore = xSemaphoreCreateBinaryStatic( &xSemaphoreBuffer );

    setupTimer1();

    // Enable global Interrupts and higher priority real-time debug events:
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    // Create the task without using any dynamic memory allocation.
    xTaskCreateStatic(LED_TaskRed,          // Function that implements the task.
                      "Red LED task",       // Text name for the task.
                      STACK_SIZE,           // Number of indexes in the xStack array.
                      ( void * ) RED,       // Parameter passed into the task.
                      tskIDLE_PRIORITY + 2, // Priority at which the task is created.
                      redTaskStack,         // Array to use as the task's stack.
                      &redTaskBuffer );     // Variable to hold the task's data structure.

    xTaskCreateStatic(LED_TaskBlue,         // Function that implements the task.
                      "Blue LED task",      // Text name for the task.
                      STACK_SIZE,           // Number of indexes in the xStack array.
                      ( void * ) BLUE,      // Parameter passed into the task.
                      tskIDLE_PRIORITY + 1, // Priority at which the task is created.
                      blueTaskStack,        // Array to use as the task's stack.
                      &blueTaskBuffer );    // Variable to hold the task's data structure.

    vTaskStartScheduler();
}
