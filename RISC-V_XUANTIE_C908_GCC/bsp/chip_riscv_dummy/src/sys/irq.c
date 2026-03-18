 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>
#include <soc.h>
#include <csi_core.h>
#include <csi_config.h>
#include <drv/common.h>

extern uint32_t soc_irq_get_irq_num(void);
extern void soc_irq_end(uint32_t irq_num);

csi_dev_t *g_irq_table[CONFIG_IRQ_NUM];

/**
  \brief       register irq handler(deprecated).
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
void csi_irq_attach(uint32_t irq_num, void *irq_handler, csi_dev_t *dev)
{
    dev->irq_handler = irq_handler;
    g_irq_table[irq_num] = dev;
}

/**
  \brief       Attach irq handler2 for compatible(Recommended).
  \param[in]   irq_num      Number of IRQ.
  \param[in]   irq_handler2 IRQ Handler.
  \param[in]   dev          The dev to operate
  \param[in]   arg          user data of irq_handler2
  \return      None.
*/
void csi_irq_attach2(uint32_t irq_num, void *irq_handler2, csi_dev_t *dev, void *arg)
{
    dev->arg             = arg;
    dev->irq_handler2    = irq_handler2;
    g_irq_table[irq_num] = dev;
}

/**
  \brief       unregister irq handler.
  \param[in]   irq_num Number of IRQ.
  \param[in]   irq_handler IRQ Handler.
  \return      None.
*/
void csi_irq_detach(uint32_t irq_num)
{
    g_irq_table[irq_num] = NULL;
}


extern void tick_irq_handler(void *arg);
void CORET_IRQHandler(void)
{
    tick_irq_handler(NULL);
}

void prvHandlingPlatformLevelIRQS(void)
{
    return;
}

uint32_t prvGetIRQ(void)
{
    uint32_t xIRQ = __get_MCAUSE() & 0x3FFU;
    /* platform level-irqs */
    if (xIRQ == 0xb)
    {
        xIRQ = soc_irq_get_irq_num();
    }
    return xIRQ;
}

/**
  \brief       dispatching irq handlers
  \return      None.
*/
void do_irq(void)
{
    uint32_t irqn;

    irqn = prvGetIRQ();
    if (irqn == 7)
    {
        tick_irq_handler(NULL);
    }
    else
    {
        int max_irqn = sizeof(g_irq_table) / sizeof(g_irq_table[0]) - 1;
        if (irqn > max_irqn || g_irq_table[irqn] == NULL) {
            printf("IRQ [%d] is not registered to the table\n", irqn);
            while(1);
        } else {
            if (g_irq_table[irqn]->irq_handler) {
                /* irq-function without parameter */
                g_irq_table[irqn]->irq_handler(g_irq_table[irqn]);
            } else if (g_irq_table[irqn]->irq_handler2) {
                /* irq-function with parameter */
                g_irq_table[irqn]->irq_handler2(irqn, g_irq_table[irqn]->arg);
            } else {
                printf("callback function of IRQ [%d] is not registered\n", irqn);
                /*the interrupt has no registered isr*/
                while(1);
            }
        }
    }
    soc_irq_end(irqn);
}
