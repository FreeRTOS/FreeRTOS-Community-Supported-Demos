/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

/*
 * Blinky: a task and a software timer send to a queue, a receive task
 * prints what came from where. Ends with PASS after 10 timer messages.
 */

#include <stdio.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "timers.h"
#include "rh850_board.h"

#define FROM_TASK         1U
#define FROM_TIMER        2U
#define TIMER_MESSAGES    10

static QueueHandle_t queue;

static void send_task( void * arg )
{
    const uint32_t v = FROM_TASK;

    ( void ) arg;

    for( ; ; )
    {
        vTaskDelay( pdMS_TO_TICKS( 200 ) );
        xQueueSend( queue, &v, 0 );
    }
}

static void timer_cb( TimerHandle_t timer )
{
    const uint32_t v = FROM_TIMER;

    ( void ) timer;
    xQueueSend( queue, &v, 0 );
}

static void receive_task( void * arg )
{
    uint32_t v;
    int timer_messages = 0;

    ( void ) arg;

    for( ; ; )
    {
        xQueueReceive( queue, &v, portMAX_DELAY );

        if( v == FROM_TASK )
        {
            printf( "Message received from task\n" );
        }
        else if( v == FROM_TIMER )
        {
            printf( "Message received from software timer\n" );

            if( ++timer_messages == TIMER_MESSAGES )
            {
                printf( "blinky pass\n" );
                board_exit( 0 );
            }
        }
        else
        {
            printf( "blinky FAIL: unexpected %lu\n", ( unsigned long ) v );
            board_exit( 1 );
        }
    }
}

int main( void )
{
    board_init();
    queue = xQueueCreate( 4, sizeof( uint32_t ) );
    TimerHandle_t timer = xTimerCreate( "blink", pdMS_TO_TICKS( 100 ), pdTRUE, NULL, timer_cb );

    configASSERT( queue != NULL && timer != NULL );
    xTaskCreate( receive_task, "rx", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
    xTaskCreate( send_task, "tx", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
    xTimerStart( timer, 0 );
    vTaskStartScheduler();
    return 1;
}
