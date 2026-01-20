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

/******************************************************************************
 * This project provides two demo applications.  A simple blinky style project,
 * and a more comprehensive test and demo application.  The
 * mainCREATE_SIMPLE_BLINKY_DEMO_ONLY setting in main.c is used to select
 * between the two.  See the notes on using mainCREATE_SIMPLE_BLINKY_DEMO_ONLY
 * in main.c.  This file implements the simply blinky version.
 *
 * This file only contains the source code that is specific to the basic demo.
 * Generic functions, such FreeRTOS hook functions, are defined in main.c.
 ******************************************************************************
 *
 * mpu_blinky() creates one queue, one software timer, and two tasks.  It then
 * starts the scheduler.
 *
 * The Queue Send Task:
 * The queue send task is implemented by the prvQueueSendTask() function in
 * this file.  It uses vTaskDelayUntil() to create a periodic task that sends
 * the value 100 to the queue every 200 (simulated) milliseconds.
 *
 * The Queue Send Software Timer:
 * The timer is an auto-reload timer with a period of two (simulated) seconds.
 * Its callback function writes the value 200 to the queue.  The callback
 * function is implemented by prvQueueSendTimerCallback() within this file.
 *
 * The Queue Receive Task:
 * The queue receive task is implemented by the prvQueueReceiveTask() function
 * in this file.  prvQueueReceiveTask() waits for data to arrive on the queue.
 * When data is received, the task checks the value of the data, then outputs a
 * message to indicate if the data came from the queue send task or the queue
 * send software timer.
 */

/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

/* Priorities at which the tasks are created. */
//#define mainQUEUE_RECEIVE_TASK_PRIORITY    (( tskIDLE_PRIORITY + 2 ) | portPRIVILEGE_BIT )
//#define mainQUEUE_SEND_TASK_PRIORITY       (( tskIDLE_PRIORITY + 1 ) | portPRIVILEGE_BIT )
#define mainQUEUE_RECEIVE_TASK_PRIORITY    (( tskIDLE_PRIORITY + 2 ))
#define mainQUEUE_SEND_TASK_PRIORITY       (( tskIDLE_PRIORITY + 1 ))

/* The rate at which data is sent to the queue.  The times are converted from
 * milliseconds to ticks using the pdMS_TO_TICKS() macro. */
#define mainTASK_SEND_FREQUENCY_MS         pdMS_TO_TICKS( 200UL )
#define mainTIMER_SEND_FREQUENCY_MS        pdMS_TO_TICKS( 2000UL )

/* The number of items the queue can hold at once. */
#define mainQUEUE_LENGTH                   ( 2 )

/* The values sent to the queue receive task from the queue send task and the
 * queue send software timer respectively. */
#define mainVALUE_SENT_FROM_TASK           ( 100UL )
#define mainVALUE_SENT_FROM_TIMER          ( 200UL )

/*-----------------------------------------------------------*/

/*
 * The tasks as described in the comments at the top of this file.
 */
static void prvQueueReceiveTask( void * pvParameters );
static void prvQueueSendTask( void * pvParameters );

/*
 * The callback function executed when the software timer expires.
 */
static void prvQueueSendTimerCallback( TimerHandle_t xTimerHandle );

/*-----------------------------------------------------------*/

/* The queue used by both tasks. */
static QueueHandle_t xQueue = NULL;

/* A software timer that is started from the tick hook. */
static TimerHandle_t xTimer = NULL;

extern char _text[];
extern char _etext[];
extern char _rodata[];
extern char _erodata[];
extern char _data[];
extern char _edata[];
extern char _bss[];
extern char _ebss[];
extern char _privileged_data[];
extern char _eprivileged_data[];

/*-----------------------------------------------------------*/

/* application exception handler to catch MPU violation */
void freertos_risc_v_application_exception_handler( void )
{
    uint32_t mcause;
    uint32_t mtval;
    uint32_t mepc;
    uint32_t mstatus;

    __asm volatile( "csrr %0, mcause"  : "=r"( mcause ) );
    __asm volatile( "csrr %0, mtval"   : "=r"( mtval ) );
    __asm volatile( "csrr %0, mepc"    : "=r"( mepc ) );
    __asm volatile( "csrr %0, mstatus" : "=r"( mstatus ) );

    /* bit 31 = interrupt */
    if( mcause & 0x80000000UL )
    {
        printf( "Unexpected interrupt! mcause=0x%08lx\n", mcause );
        while( 1 );
    }

    switch( mcause & 0x7FFFFFFFUL )
    {
        case 1: /* Instruction access fault */
        case 5: /* Load access fault */
        case 7: /* Store/AMO access fault */
        {
            printf( "\n=== PMP ACCESS FAULT ===\n" );
            printf( "mcause  = 0x%08x\n", mcause );
            printf( "mepc    = 0x%08x\n", mepc );
            printf( "mtval   = 0x%08x\n", mtval );
            printf( "mstatus = 0x%08x\n", mstatus );

            if( ( mcause & 0x7FFFFFFFUL ) == 1 )
                printf( "type    = instruction fetch\n" );
            else if( ( mcause & 0x7FFFFFFFUL ) == 5 )
                printf( "type    = load\n" );
            else
                printf( "type    = store / amo\n" );

            if( xTaskGetCurrentTaskHandle() != NULL )
            {
                printf( "task    = %s\n",
                    pcTaskGetName( xTaskGetCurrentTaskHandle() ) );
            }

            printf( "system halted.\n" );

            while( 1 );
        }

        default:
        {
            printf( "\nUnhandled exception!\n" );
            printf( "mcause = 0x%08x\n", mcause );
            printf( "mepc   = 0x%08x\n", mepc );
            printf( "mtval  = 0x%08x\n", mtval );
            while( 1 );
        }
    }
}

/*** SEE THE COMMENTS AT THE TOP OF THIS FILE ***/
void mpu_blinky( void )
{
    printf ( "MPU blinky demo start\n" );
    printf ( ".text   = [0x%x - 0x%x]\n", &_text, &_etext );
    printf ( ".rodata = [0x%x - 0x%x]\n", &_rodata, &_erodata );
    printf ( ".data   = [0x%x - 0x%x]\n", &_data, &_edata );
    printf ( ".bss    = [0x%x - 0x%x]\n", &_bss , &_ebss );
    printf ( ".privileged_data = [0x%x - 0x%x]\n", &_privileged_data, &_eprivileged_data );

    const TickType_t xTimerPeriod = mainTIMER_SEND_FREQUENCY_MS;

    /* Create the queue. */
    xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( uint32_t ) );

    BaseType_t ret;

    static StackType_t xQueueReceiveTaskStack[ configMINIMAL_STACK_SIZE ] __attribute__((aligned( configMINIMAL_STACK_SIZE)));
    static StackType_t xQueueSendTaskStack[ configMINIMAL_STACK_SIZE ] __attribute__((aligned( configMINIMAL_STACK_SIZE)));
    printf("xQueueReceiveTaskStack = [0x%x - 0x%x]\n", xQueueReceiveTaskStack, (uintptr_t)xQueueReceiveTaskStack + configMINIMAL_STACK_SIZE);
    printf("xQueueSendTaskStack    = [0x%x - 0x%x]\n", xQueueSendTaskStack, (uintptr_t)xQueueSendTaskStack + configMINIMAL_STACK_SIZE);
    TaskParameters_t xQueueReceiveTaskParameters =
    {
        .pvTaskCode     = prvQueueReceiveTask,
        .pcName         = "Rx",
        .usStackDepth   = configMINIMAL_STACK_SIZE / sizeof(StackType_t),
        .pvParameters   = NULL,
        .uxPriority     = mainQUEUE_RECEIVE_TASK_PRIORITY,
        .puxStackBuffer = xQueueReceiveTaskStack,
        .xRegions       =
        {
            { &_text, _erodata - _text, portMPU_REGION_READ | portMPU_REGION_EXECUTE },
            { &_data, _ebss - _data, portMPU_REGION_READ | portMPU_REGION_WRITE },
            /* NS16550 */
            { (void *)0x10000000UL, 0x1000, portMPU_REGION_READ | portMPU_REGION_WRITE },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            /* *MUST* reserve one entry for stack */
            { 0, 0, 0 },
        }
    };
    TaskParameters_t xQueueSendTaskParameters =
    {
        .pvTaskCode     = prvQueueSendTask,
        .pcName         = "Tx",
        .usStackDepth   = configMINIMAL_STACK_SIZE / sizeof(StackType_t),
        .pvParameters   = NULL,
        .uxPriority     = mainQUEUE_SEND_TASK_PRIORITY,
        .puxStackBuffer = xQueueSendTaskStack,
        .xRegions       =
        {
            { &_text, _erodata - _text, portMPU_REGION_READ | portMPU_REGION_EXECUTE },
            { &_data, _ebss - _data, portMPU_REGION_READ | portMPU_REGION_WRITE },
            /* NS16550 */
            { (void *)0x10000000UL, 0x1000, portMPU_REGION_READ | portMPU_REGION_WRITE },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            /* *MUST* reserve one entry for stack */
            { 0, 0, 0 },
        }
    };
    TaskHandle_t xQueueReceiveTask;
    TaskHandle_t xQueueSendTask;

    if( xQueue != NULL )
    {
        /* Start the two tasks as described in the comments at the top of this
         * file. */
        ret = xTaskCreateRestricted( &( xQueueReceiveTaskParameters ), &xQueueReceiveTask );
        if ( ret != pdPASS )
        {
            printf( "Task Create Failed\r\n" );
            for ( ;; ) {}
        }

        vGrantAccessToKernelObject( xQueueReceiveTask, (int32_t)xQueue );

        ret = xTaskCreateRestricted( &( xQueueSendTaskParameters ), &xQueueSendTask );
        if ( ret != pdPASS )
        {
            printf( "Task Create Failed\r\n" );
            for ( ;; ) {}
        }
        vGrantAccessToKernelObject( xQueueSendTask, (int32_t)xQueue );

        /* Create the software timer, but don't start it yet. */
        xTimer = xTimerCreate( "Timer",                     /* The text name assigned to the software timer - for debug only as it is not used by the kernel. */
                               xTimerPeriod,                /* The period of the software timer in ticks. */
                               pdTRUE,                      /* xAutoReload is set to pdTRUE, so this is an auto-reload timer. */
                               NULL,                        /* The timer's ID is not used. */
                               prvQueueSendTimerCallback ); /* The function executed when the timer expires. */

        xTimerStart( xTimer, 0 );                           /* The scheduler has not started so use a block time of 0. */

        /* Start the tasks and timer running. */
        vTaskStartScheduler();
    }

    /* If all is well, the scheduler will now be running, and the following
     * line will never be reached.  If the following line does execute, then
     * there was insufficient FreeRTOS heap memory available for the idle and/or
     * timer tasks	to be created.  See the memory management section on the
     * FreeRTOS web site for more details.  NOTE: This demo uses static allocation
     * for the idle and timer tasks so this line should never execute. */
    for( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

static void prvQueueSendTask( void * pvParameters )
{
    TickType_t xNextWakeTime;
    const TickType_t xBlockTime = mainTASK_SEND_FREQUENCY_MS;
    const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TASK;
    int i = 0;

    /* Prevent the compiler warning about the unused parameter. */
    ( void ) pvParameters;

    /* Initialise xNextWakeTime - this only needs to be done once. */
    xNextWakeTime = xTaskGetTickCount();

    for( ; ; )
    {
        if ( i == 10 )
        {
            printf( "%s: trying to access privileged data\n", __func__ );
            /* Triggers PMP access fault */
            uint32_t some_privileged_data = *((uint32_t *)_privileged_data);
            printf( "%lu\n", some_privileged_data );
        }
        /* Place this task in the blocked state until it is time to run again.
         *  The block time is specified in ticks, pdMS_TO_TICKS() was used to
         *  convert a time specified in milliseconds into a time specified in ticks.
         *  While in the Blocked state this task will not consume any CPU time. */
        vTaskDelayUntil( &xNextWakeTime, xBlockTime );

        /* Send to the queue - causing the queue receive task to unblock and
         * write to the console.  0 is used as the block time so the send operation
         * will not block - it shouldn't need to block as the queue should always
         * have at least one space at this point in the code. */
        xQueueSend( xQueue, &ulValueToSend, 0U );
        i++;
    }
}
/*-----------------------------------------------------------*/

static void prvQueueSendTimerCallback( TimerHandle_t xTimerHandle )
{
    const uint32_t ulValueToSend = mainVALUE_SENT_FROM_TIMER;

    /* This is the software timer callback function.  The software timer has a
     * period of two seconds and is reset each time a key is pressed.  This
     * callback function will execute if the timer expires, which will only happen
     * if a key is not pressed for two seconds. */

    /* Avoid compiler warnings resulting from the unused parameter. */
    ( void ) xTimerHandle;

    /* Send to the queue - causing the queue receive task to unblock and
     * write out a message.  This function is called from the timer/daemon task, so
     * must not block.  Hence the block time is set to 0. */
    xQueueSend( xQueue, &ulValueToSend, 0U );
}
/*-----------------------------------------------------------*/

static void prvQueueReceiveTask( void * pvParameters )
{
    uint32_t ulReceivedValue;

    /* Prevent the compiler warning about the unused parameter. */
    ( void ) pvParameters;

    for( ; ; )
    {
        /* Wait until something arrives in the queue - this task will block
         * indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
         * FreeRTOSConfig.h.  It will not use any CPU time while it is in the
         * Blocked state. */
        xQueueReceive( xQueue, &ulReceivedValue, portMAX_DELAY );

        /*  To get here something must have been received from the queue, but
         * is it an expected value? */
        if( ulReceivedValue == mainVALUE_SENT_FROM_TASK )
        {
            /* It is normally not good to call printf() from an embedded system,
             * although it is ok in this simulated case. */
            printf( "Message received from task\r\n" );
        }
        else if( ulReceivedValue == mainVALUE_SENT_FROM_TIMER )
        {
            printf( "Message received from software timer\r\n" );
        }
        else
        {
            printf( "Unexpected message\r\n" );
        }
    }
}
/*-----------------------------------------------------------*/
