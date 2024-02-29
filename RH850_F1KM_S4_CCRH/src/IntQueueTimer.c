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
 * https://github.com/FreeRTOS
 *
 */

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo includes. */
#include "IntQueueTimer.h"
#include "IntQueue.h"

/* Hardware includes */
#include "bsp_common.h"

/*-----------------------------------------------------------*/

#define TAUD0_PCLK    80000000

void vInitialiseTimerForIntQueueTest (void)
{
    /* Initialize a hardware timer. */

    INTC2.ICTAUD0I1.BIT.RFTAUD0I1 = 0x0U;      /* clear interrupt flag */
    INTC2.ICTAUD0I1.BIT.MKTAUD0I1 = 0x0U;      /* unmask interrupt */
    INTC2.ICTAUD0I1.BIT.TBTAUD0I1 = 0x1U;      /* table reference method */
    INTC2.ICTAUD0I1.UINT16       &= (0x00C0U); /* interrupt priority first highest */

    INTC2.ICTAUD0I3.BIT.RFTAUD0I3 = 0x0U;      /* clear interrupt flag */
    INTC2.ICTAUD0I3.BIT.MKTAUD0I3 = 0x0U;      /* unmask interrupt */
    INTC2.ICTAUD0I3.BIT.TBTAUD0I3 = 0x1U;      /* table reference method */
    INTC2.ICTAUD0I1.UINT16       &= (0x00C1U); /* interrupt priority first highest */

    TAUD0.TPS &= (0xFFF0U);                    /* CK0_PRE - clear */
    TAUD0.TPS |= (0x0000U);                    /* CK0_PRE - PCLK/2^0 */

    /* Set channel 0 setting */
    TAUD0.CMOR1 = 0x0000U;
    TAUD0.CMOR3 = 0x0000U;

    /* Set compare match register */
    TAUD0.CMUR1 = 0x00U;
    TAUD0.CDR1  = TAUD0_PCLK / 2000 - 1;

    TAUD0.CMUR3 = 0x00U;
    TAUD0.CDR3  = TAUD0_PCLK / 2001 - 1;

    /* Set output mode setting */
    TAUD0.TOM = 0;
    TAUD0.TOC = 0;
    TAUD0.TOL = 0;
    TAUD0.TOE = 0;

    TAUD0.RDE = 0;
    TAUD0.RDM = 0;

    /* start TAUJ0I0 and TAUJ0I1 */
    TAUD0.TS = 10;
}

void TAUD0I1_Handler (void)
{
    portYIELD_FROM_ISR(xFirstTimerHandler());
}

void TAUD0I3_Handler (void)
{
    portYIELD_FROM_ISR(xSecondTimerHandler());
}
