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

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/* Interface include files. */
#include "RegTests.h"

/* Tasks that implement register tests. */
static void prvRegisterTest1Task( void *pvParameters );
static void prvRegisterTest2Task( void *pvParameters );
static void prvRegisterTest3Task( void *pvParameters );
static void prvRegisterTest4Task( void *pvParameters );

/* Flag that will be latched to pdTRUE should any unexpected behaviour be
detected in any of the tasks. */
static volatile BaseType_t xErrorDetected = pdFALSE;

/* Counters that are incremented on each cycle of a test.  This is used to
detect a stalled task - a test that is no longer running. */
static volatile uint32_t ulRegisterTest1Counter = 0;
static volatile uint32_t ulRegisterTest2Counter = 0;
static volatile uint32_t ulRegisterTest3Counter = 0;
static volatile uint32_t ulRegisterTest4Counter = 0;
/*-----------------------------------------------------------*/

static void prvRegisterTest1Task( void *pvParameters )
{
    ( void ) pvParameters;

    /* 1. Fill the registers stored as part of task context with known values.
     * 2. Force a context switch.
     * 3. Verify that all the registers contain expected values.
     * 4. If all the registers contain expected values, increment ulRegisterTest1Counter.
     */

    __asm__ __volatile__ (
        "reg1_loop:                                             \n"
        
        /* Fill the core registers with known values. */
        "   li  t0, 0x1111111111111111                          \n"
        "   li  t1, 0x2222222222222222                          \n"
        "   li  t2, 0x3333333333333333                          \n"
        "   li  s0, 0x4444444444444444                          \n"
        "   li  s1, 0x5555555555555555                          \n"
        "   li  s2, 0x6666666666666666                          \n"
        "   li  s3, 0x7777777777777777                          \n"
        "   li  s4, 0x8888888888888888                          \n"
        "   li  s5, 0x9999999999999999                          \n"
        "   li  s6, 0xAAAAAAAAAAAAAAAA                          \n"
        "   li  s7, 0xBBBBBBBBBBBBBBBB                          \n"
        "   li  s8, 0xCCCCCCCCCCCCCCCC                          \n"
        "   li  s9, 0xDDDDDDDDDDDDDDDD                          \n"
        "   li  s10, 0xEEEEEEEEEEEEEEEE                         \n"
        "   li  s11, 0xFFFFFFFFFFFFFFFF                         \n"
        "   li  t3, 0x0123456789ABCDEF                          \n"
        "   li  t4, 0xFEDCBA9876543210                          \n"
        "   li  t5, 0xDEADBEEFDEADBEEF                          \n"
        "   li  t6, 0xCAFEBABECAFEBABE                          \n"
    );

    /* Force a context switch. */
    vTaskDelay( 0 );

    __asm__ __volatile__ (
        /* Verify that all the registers contain expected values. */

        /* Test t0 value. */
        "   li   a0, 0x1111111111111111                         \n"
        "   bne  t0, a0, reg1_error_loop                        \n"

        /* Test t1 value. */
        "   li   a0, 0x2222222222222222                         \n"
        "   bne  t1, a0, reg1_error_loop                        \n"

        /* Test t2 value. */
        "   li   a0, 0x3333333333333333                         \n"
        "   bne  t2, a0, reg1_error_loop                        \n"

        /* Test s0 value. */
        "   li   a0, 0x4444444444444444                         \n"
        "   bne  s0, a0, reg1_error_loop                        \n"

        /* Test s1 value. */
        "   li   a0, 0x5555555555555555                         \n"
        "   bne  s1, a0, reg1_error_loop                        \n"

        /* Test s2 value. */
        "   li   a0, 0x6666666666666666                         \n"
        "   bne  s2, a0, reg1_error_loop                        \n"

        /* Test s3 value. */
        "   li   a0, 0x7777777777777777                         \n"
        "   bne  s3, a0, reg1_error_loop                        \n"

        /* Test s4 value. */
        "   li   a0, 0x8888888888888888                         \n"
        "   bne  s4, a0, reg1_error_loop                        \n"

        /* Test s5 value. */
        "   li   a0, 0x9999999999999999                         \n"
        "   bne  s5, a0, reg1_error_loop                        \n"

        /* Test s6 value. */
        "   li   a0, 0xAAAAAAAAAAAAAAAA                         \n"
        "   bne  s6, a0, reg1_error_loop                        \n"

        /* Test s7 value. */
        "   li   a0, 0xBBBBBBBBBBBBBBBB                         \n"
        "   bne  s7, a0, reg1_error_loop                        \n"

        /* Test s8 value. */
        "   li   a0, 0xCCCCCCCCCCCCCCCC                         \n"
        "   bne  s8, a0, reg1_error_loop                        \n"

        /* Test s9 value. */
        "   li   a0, 0xDDDDDDDDDDDDDDDD                         \n"
        "   bne  s9, a0, reg1_error_loop                        \n"

        /* Test s10 value. */
        "   li   a0, 0xEEEEEEEEEEEEEEEE                         \n"
        "   bne  s10, a0, reg1_error_loop                       \n"

        /* Test s11 value. */
        "   li   a0, 0xFFFFFFFFFFFFFFFF                         \n"
        "   bne  s11, a0, reg1_error_loop                       \n"

        /* Test t3 value. */
        "   li   a0, 0x0123456789ABCDEF                         \n"
        "   bne  t3, a0, reg1_error_loop                        \n"

        /* Test t4 value. */
        "   li   a0, 0xFEDCBA9876543210                         \n"
        "   bne  t4, a0, reg1_error_loop                        \n"

        /* Test t5 value. */
        "   li   a0, 0xDEADBEEFDEADBEEF                         \n"
        "   bne  t5, a0, reg1_error_loop                        \n"

        /* Test t6 value. */
        "   li   a0, 0xCAFEBABECAFEBABE                         \n"
        "   bne  t6, a0, reg1_error_loop                        \n"

        /* If this line is reached then all registers contained expected values.
         * Increment the loop counter to indicate this test is still functioning
         * correctly. */
        "   la   a0, ulRegisterTest1Counter                     \n"
        "   ld   a1, 0(a0)                                      \n"
        "   addi a1, a1, 1                                      \n"
        "   sd   a1, 0(a0)                                      \n"

        /* Start the test loop again. */
        "   j    reg1_loop                                      \n"

        "reg1_error_loop:                                       \n"
        /* If this line is hit then there was an error in a core register value.
         * This loop ensures the loop counter variable stops incrementing. */
        "   j    reg1_error_loop                                \n"
    );
}

/*-----------------------------------------------------------*/

static void prvRegisterTest2Task( void *pvParameters )
{
    ( void ) pvParameters;

    /* 1. Fill the registers stored as part of task context with known values.
     * 2. Force a context switch.
     * 3. Verify that all the registers contain expected values.
     * 4. If all the registers contain expected values, increment ulRegisterTest2Counter.
     */

    __asm__ __volatile__ (
        "reg2_loop:                                             \n"
        
        /* Fill the core registers with known values. */
        "   li  t0, 0xEEEEEEEEEEEEEEEE                          \n"
        "   li  t1, 0xDDDDDDDDDDDDDDDD                          \n"
        "   li  t2, 0xCCCCCCCCCCCCCCCC                          \n"
        "   li  s0, 0xBBBBBBBBBBBBBBBB                          \n"
        "   li  s1, 0xAAAAAAAAAAAAAAAA                          \n"
        "   li  s2, 0x9999999999999999                          \n"
        "   li  s3, 0x8888888888888888                          \n"
        "   li  s4, 0x7777777777777777                          \n"
        "   li  s5, 0x6666666666666666                          \n"
        "   li  s6, 0x5555555555555555                          \n"
        "   li  s7, 0x4444444444444444                          \n"
        "   li  s8, 0x3333333333333333                          \n"
        "   li  s9, 0x2222222222222222                          \n"
        "   li  s10, 0x1111111111111111                         \n"
        "   li  s11, 0x0F0F0F0F0F0F0F0F                         \n"
        "   li  t3, 0xF0F0F0F0F0F0F0F0                          \n"
        "   li  t4, 0x5A5A5A5A5A5A5A5A                          \n"
        "   li  t5, 0xA5A5A5A5A5A5A5A5                          \n"
        "   li  t6, 0xBAADF00DBAADF00D                          \n"
    );

    /* Force a context switch. */
    vTaskDelay( 0 );

    __asm__ __volatile__ (
        /* Verify that all the registers contain expected values. */

        /* Test t0 value. */
        "   li   a0, 0xEEEEEEEEEEEEEEEE                         \n"
        "   bne  t0, a0, reg2_error_loop                        \n"

        /* Test t1 value. */
        "   li   a0, 0xDDDDDDDDDDDDDDDD                         \n"
        "   bne  t1, a0, reg2_error_loop                        \n"

        /* Test t2 value. */
        "   li   a0, 0xCCCCCCCCCCCCCCCC                         \n"
        "   bne  t2, a0, reg2_error_loop                        \n"

        /* Test s0 value. */
        "   li   a0, 0xBBBBBBBBBBBBBBBB                         \n"
        "   bne  s0, a0, reg2_error_loop                        \n"

        /* Test s1 value. */
        "   li   a0, 0xAAAAAAAAAAAAAAAA                         \n"
        "   bne  s1, a0, reg2_error_loop                        \n"

        /* Test s2 value. */
        "   li   a0, 0x9999999999999999                         \n"
        "   bne  s2, a0, reg2_error_loop                        \n"

        /* Test s3 value. */
        "   li   a0, 0x8888888888888888                         \n"
        "   bne  s3, a0, reg2_error_loop                        \n"

        /* Test s4 value. */
        "   li   a0, 0x7777777777777777                         \n"
        "   bne  s4, a0, reg2_error_loop                        \n"

        /* Test s5 value. */
        "   li   a0, 0x6666666666666666                         \n"
        "   bne  s5, a0, reg2_error_loop                        \n"

        /* Test s6 value. */
        "   li   a0, 0x5555555555555555                         \n"
        "   bne  s6, a0, reg2_error_loop                        \n"

        /* Test s7 value. */
        "   li   a0, 0x4444444444444444                         \n"
        "   bne  s7, a0, reg2_error_loop                        \n"

        /* Test s8 value. */
        "   li   a0, 0x3333333333333333                         \n"
        "   bne  s8, a0, reg2_error_loop                        \n"

        /* Test s9 value. */
        "   li   a0, 0x2222222222222222                         \n"
        "   bne  s9, a0, reg2_error_loop                        \n"

        /* Test s10 value. */
        "   li   a0, 0x1111111111111111                         \n"
        "   bne  s10, a0, reg2_error_loop                       \n"

        /* Test s11 value. */
        "   li   a0, 0x0F0F0F0F0F0F0F0F                         \n"
        "   bne  s11, a0, reg2_error_loop                       \n"

        /* Test t3 value. */
        "   li   a0, 0xF0F0F0F0F0F0F0F0                         \n"
        "   bne  t3, a0, reg2_error_loop                        \n"

        /* Test t4 value. */
        "   li   a0, 0x5A5A5A5A5A5A5A5A                         \n"
        "   bne  t4, a0, reg2_error_loop                        \n"

        /* Test t5 value. */
        "   li   a0, 0xA5A5A5A5A5A5A5A5                         \n"
        "   bne  t5, a0, reg2_error_loop                        \n"

        /* Test t6 value. */
        "   li   a0, 0xBAADF00DBAADF00D                         \n"
        "   bne  t6, a0, reg2_error_loop                        \n"

        /* If this line is reached then all registers contained expected values.
         * Increment the loop counter to indicate this test is still functioning
         * correctly. */
        "   la   a0, ulRegisterTest2Counter                     \n"
        "   ld   a1, 0(a0)                                      \n"
        "   addi a1, a1, 1                                      \n"
        "   sd   a1, 0(a0)                                      \n"

        /* Start the test loop again. */
        "   j    reg2_loop                                      \n"

        "reg2_error_loop:                                       \n"
        /* If this line is hit then there was an error in a core register value.
         * This loop ensures the loop counter variable stops incrementing. */
        "   j    reg2_error_loop                                \n"
    );
}
/*-----------------------------------------------------------*/

static void prvRegisterTest3Task( void *pvParameters )
{
    ( void ) pvParameters;

    /* 1. Fill the registers stored as part of task context with known values.
     * 2. Force a context switch.
     * 3. Verify that all the registers contain expected values.
     * 4. If all the registers contain expected values, increment ulRegisterTest3Counter.
     */

    __asm__ __volatile__ (
        "reg3_loop:                                             \n"
        
        /* Fill the core registers with known values. */
        "   li  t0, 0xA5A5A5A5A5A5A5A5                          \n"
        "   li  t1, 0x5A5A5A5A5A5A5A5A                          \n"
        "   li  t2, 0x1234567812345678                          \n"
        "   li  s0, 0x8765432187654321                          \n"
        "   li  s1, 0xDEADBEEFDEADBEEF                          \n"
        "   li  s2, 0xCAFEBABECAFEBABE                          \n"
        "   li  s3, 0xBAADF00DBAADF00D                          \n"
        "   li  s4, 0xFEEDFACEFEEDFACE                          \n"
        "   li  s5, 0x0123456789ABCDEF                          \n"
        "   li  s6, 0xFEDCBA9876543210                          \n"
        "   li  s7, 0x1111222233334444                          \n"
        "   li  s8, 0x5555666677778888                          \n"
        "   li  s9, 0x9999AAAABBBBCCCC                          \n"
        "   li  s10, 0xDDDDEEEEFFFF0000                         \n"
        "   li  s11, 0xABCDEF0123456789                         \n"
        "   li  t3, 0x9876543210ABCDEF                          \n"
        "   li  t4, 0xF0F0F0F00F0F0F0F                          \n"
        "   li  t5, 0x0F0F0F0FF0F0F0F0                          \n"
        "   li  t6, 0x5555AAAA5555AAAA                          \n"
    );

    /* Force a context switch. */
    vTaskDelay( 0 );

    __asm__ __volatile__ (
        /* Verify that all the registers contain expected values. */
        
        /* Test t0 value. */
        "   li   a0, 0xA5A5A5A5A5A5A5A5                         \n"
        "   bne  t0, a0, reg3_error_loop                        \n"
        
        /* Test t1 value. */
        "   li   a0, 0x5A5A5A5A5A5A5A5A                         \n"
        "   bne  t1, a0, reg3_error_loop                        \n"
        
        /* Test t2 value. */
        "   li   a0, 0x1234567812345678                         \n"
        "   bne  t2, a0, reg3_error_loop                        \n"
        
        /* Test s0 value. */
        "   li   a0, 0x8765432187654321                         \n"
        "   bne  s0, a0, reg3_error_loop                        \n"
        
        /* Test s1 value. */
        "   li   a0, 0xDEADBEEFDEADBEEF                         \n"
        "   bne  s1, a0, reg3_error_loop                        \n"
        
        /* Test s2 value. */
        "   li   a0, 0xCAFEBABECAFEBABE                         \n"
        "   bne  s2, a0, reg3_error_loop                        \n"
        
        /* Test s3 value. */
        "   li   a0, 0xBAADF00DBAADF00D                         \n"
        "   bne  s3, a0, reg3_error_loop                        \n"
        
        /* Test s4 value. */
        "   li   a0, 0xFEEDFACEFEEDFACE                         \n"
        "   bne  s4, a0, reg3_error_loop                        \n"
        
        /* Test s5 value. */
        "   li   a0, 0x0123456789ABCDEF                         \n"
        "   bne  s5, a0, reg3_error_loop                        \n"
        
        /* Test s6 value. */
        "   li   a0, 0xFEDCBA9876543210                         \n"
        "   bne  s6, a0, reg3_error_loop                        \n"
        
        /* Test s7 value. */
        "   li   a0, 0x1111222233334444                         \n"
        "   bne  s7, a0, reg3_error_loop                        \n"
        
        /* Test s8 value. */
        "   li   a0, 0x5555666677778888                         \n"
        "   bne  s8, a0, reg3_error_loop                        \n"
        
        /* Test s9 value. */
        "   li   a0, 0x9999AAAABBBBCCCC                         \n"
        "   bne  s9, a0, reg3_error_loop                        \n"
        
        /* Test s10 value. */
        "   li   a0, 0xDDDDEEEEFFFF0000                         \n"
        "   bne  s10, a0, reg3_error_loop                       \n"
        
        /* Test s11 value. */
        "   li   a0, 0xABCDEF0123456789                         \n"
        "   bne  s11, a0, reg3_error_loop                       \n"
        
        /* Test t3 value. */
        "   li   a0, 0x9876543210ABCDEF                         \n"
        "   bne  t3, a0, reg3_error_loop                        \n"
        
        /* Test t4 value. */
        "   li   a0, 0xF0F0F0F00F0F0F0F                         \n"
        "   bne  t4, a0, reg3_error_loop                        \n"
        
        /* Test t5 value. */
        "   li   a0, 0x0F0F0F0FF0F0F0F0                         \n"
        "   bne  t5, a0, reg3_error_loop                        \n"
        
        /* Test t6 value. */
        "   li   a0, 0x5555AAAA5555AAAA                         \n"
        "   bne  t6, a0, reg3_error_loop                        \n"
        
        /* If this line is reached then all registers contained expected values.
         * Increment the loop counter to indicate this test is still functioning
         * correctly. */
        "   la   a0, ulRegisterTest3Counter                     \n"
        "   ld   a1, 0(a0)                                      \n"
        "   addi a1, a1, 1                                      \n"
        "   sd   a1, 0(a0)                                      \n"
        
        /* Start the test loop again. */
        "   j    reg3_loop                                      \n"
        
        "reg3_error_loop:                                       \n"
        /* If this line is hit then there was an error in a core register value.
         * This loop ensures the loop counter variable stops incrementing. */
        "   j    reg3_error_loop                                \n"
    );
}

/*-----------------------------------------------------------*/

static void prvRegisterTest4Task( void *pvParameters )
{
    ( void ) pvParameters;

    /* 1. Fill the registers stored as part of task context with known values.
     * 2. Force a context switch.
     * 3. Verify that all the registers contain expected values.
     * 4. If all the registers contain expected values, increment ulRegisterTest4Counter.
     */

    __asm__ __volatile__ (
        "reg4_loop:                                             \n"
        
        /* Fill the core registers with known values. */
        "   li  t0, 0x0001000200030004                          \n"
        "   li  t1, 0x0005000600070008                          \n"
        "   li  t2, 0x0009000A000B000C                          \n"
        "   li  s0, 0x000D000E000F0010                          \n"
        "   li  s1, 0x0011001200130014                          \n"
        "   li  s2, 0x0015001600170018                          \n"
        "   li  s3, 0x0019001A001B001C                          \n"
        "   li  s4, 0x001D001E001F0020                          \n"
        "   li  s5, 0xAAAA5555AAAA5555                          \n"
        "   li  s6, 0x5555AAAA5555AAAA                          \n"
        "   li  s7, 0xFF00FF00FF00FF00                          \n"
        "   li  s8, 0x00FF00FF00FF00FF                          \n"
        "   li  s9, 0xF00FF00FF00FF00F                          \n"
        "   li  s10, 0x0FF00FF00FF00FF0                         \n"
        "   li  s11, 0x123456789ABCDEF0                         \n"
        "   li  t3, 0x0FEDCBA987654321                          \n"
        "   li  t4, 0xC0FFEE00DEADBEEF                          \n"
        "   li  t5, 0xBADC0FFEE0DDF00D                          \n"
        "   li  t6, 0xFACEFEEDCAFEBABE                          \n"
    );

    /* Force a context switch. */
    vTaskDelay( 0 );

    __asm__ __volatile__ (
        /* Verify that all the registers contain expected values. */

        /* Test t0 value. */
        "   li   a0, 0x0001000200030004                         \n"
        "   bne  t0, a0, reg4_error_loop                        \n"

        /* Test t1 value. */
        "   li   a0, 0x0005000600070008                         \n"
        "   bne  t1, a0, reg4_error_loop                        \n"

        /* Test t2 value. */
        "   li   a0, 0x0009000A000B000C                         \n"
        "   bne  t2, a0, reg4_error_loop                        \n"

        /* Test s0 value. */
        "   li   a0, 0x000D000E000F0010                         \n"
        "   bne  s0, a0, reg4_error_loop                        \n"

        /* Test s1 value. */
        "   li   a0, 0x0011001200130014                         \n"
        "   bne  s1, a0, reg4_error_loop                        \n"

        /* Test s2 value. */
        "   li   a0, 0x0015001600170018                         \n"
        "   bne  s2, a0, reg4_error_loop                        \n"

        /* Test s3 value. */
        "   li   a0, 0x0019001A001B001C                         \n"
        "   bne  s3, a0, reg4_error_loop                        \n"

        /* Test s4 value. */
        "   li   a0, 0x001D001E001F0020                         \n"
        "   bne  s4, a0, reg4_error_loop                        \n"

        /* Test s5 value. */
        "   li   a0, 0xAAAA5555AAAA5555                         \n"
        "   bne  s5, a0, reg4_error_loop                        \n"

        /* Test s6 value. */
        "   li   a0, 0x5555AAAA5555AAAA                         \n"
        "   bne  s6, a0, reg4_error_loop                        \n"

        /* Test s7 value. */
        "   li   a0, 0xFF00FF00FF00FF00                         \n"
        "   bne  s7, a0, reg4_error_loop                        \n"

        /* Test s8 value. */
        "   li   a0, 0x00FF00FF00FF00FF                         \n"
        "   bne  s8, a0, reg4_error_loop                        \n"

        /* Test s9 value. */
        "   li   a0, 0xF00FF00FF00FF00F                         \n"
        "   bne  s9, a0, reg4_error_loop                        \n"

        /* Test s10 value. */
        "   li   a0, 0x0FF00FF00FF00FF0                         \n"
        "   bne  s10, a0, reg4_error_loop                       \n"

        /* Test s11 value. */
        "   li   a0, 0x123456789ABCDEF0                         \n"
        "   bne  s11, a0, reg4_error_loop                       \n"

        /* Test t3 value. */
        "   li   a0, 0x0FEDCBA987654321                         \n"
        "   bne  t3, a0, reg4_error_loop                        \n"

        /* Test t4 value. */
        "   li   a0, 0xC0FFEE00DEADBEEF                         \n"
        "   bne  t4, a0, reg4_error_loop                        \n"

        /* Test t5 value. */
        "   li   a0, 0xBADC0FFEE0DDF00D                         \n"
        "   bne  t5, a0, reg4_error_loop                        \n"

        /* Test t6 value. */
        "   li   a0, 0xFACEFEEDCAFEBABE                         \n"
        "   bne  t6, a0, reg4_error_loop                        \n"

        /* If this line is reached then all registers contained expected values.
         * Increment the loop counter to indicate this test is still functioning
         * correctly. */
        "   la   a0, ulRegisterTest4Counter                     \n"
        "   ld   a1, 0(a0)                                      \n"
        "   addi a1, a1, 1                                      \n"
        "   sd   a1, 0(a0)                                      \n"

        /* Start the test loop again. */
        "   j    reg4_loop                                      \n"

        "reg4_error_loop:                                       \n"
        /* If this line is hit then there was an error in a core register value.
         * This loop ensures the loop counter variable stops incrementing. */
        "   j    reg4_error_loop                                \n"
    );
}
/*-----------------------------------------------------------*/

void vStartRegisterTasks( UBaseType_t uxPriority )
{
	BaseType_t ret;

	ret = xTaskCreate( prvRegisterTest1Task, "RegTest1", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
	configASSERT( ret == pdPASS );

	ret = xTaskCreate( prvRegisterTest2Task, "RegTest2", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
	configASSERT( ret == pdPASS );

	ret = xTaskCreate( prvRegisterTest3Task, "RegTest3", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
	configASSERT( ret == pdPASS );

	ret = xTaskCreate( prvRegisterTest4Task, "RegTest4", configMINIMAL_STACK_SIZE, NULL, uxPriority, NULL );
	configASSERT( ret == pdPASS );
}
/*-----------------------------------------------------------*/

BaseType_t xAreRegisterTasksStillRunning( void )
{
static uint32_t ulLastRegisterTest1Counter = 0, ulLastRegisterTest2Counter = 0;
static uint32_t ulLastRegisterTest3Counter = 0, ulLastRegisterTest4Counter = 0;

	/* If the register test task is still running then we expect the loop
	 * counters to have incremented since this function was last called. */
	if( ulLastRegisterTest1Counter == ulRegisterTest1Counter )
	{
		xErrorDetected = pdTRUE;
	}

	if( ulLastRegisterTest2Counter == ulRegisterTest2Counter )
	{
		xErrorDetected = pdTRUE;
	}

	if( ulLastRegisterTest3Counter == ulRegisterTest3Counter )
	{
		xErrorDetected = pdTRUE;
	}

	if( ulLastRegisterTest4Counter == ulRegisterTest4Counter )
	{
		xErrorDetected = pdTRUE;
	}

	ulLastRegisterTest1Counter = ulRegisterTest1Counter;
	ulLastRegisterTest2Counter = ulRegisterTest2Counter;
	ulLastRegisterTest3Counter = ulRegisterTest3Counter;
	ulLastRegisterTest4Counter = ulRegisterTest4Counter;

	/* Errors detected in the task itself will have latched xErrorDetected
	 * to true. */
	return ( BaseType_t ) !xErrorDetected;
}
/*-----------------------------------------------------------*/
