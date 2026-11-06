/*
 * Copyright (c) 2026 Linumiz
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef RH850_INTC_H
#define RH850_INTC_H

#include <stdint.h>

typedef void (* rh850_isr_t)( void * arg );

/* Lowest priority is 15 (EICn.EIP, U2C HW UM Table 6.16 p548) */
#define RH850_INTC_PRIO_LOWEST    15

/*
 * Handlers live in RH850_INTC_HANDLERS slots (set by the board); connecting
 * more channels than that is a fault (cause 10000H + channel).
 */
void rh850_intc_connect( unsigned int ch,
                         rh850_isr_t isr,
                         void * arg );
void rh850_intc_set_priority( unsigned int ch,
                              unsigned int prio );
void rh850_intc_enable( unsigned int ch );
void rh850_intc_disable( unsigned int ch );

/*
 * Set or clear EIRF of an edge channel: a software request
 * (HW Table 6.16 p547)
 */
void rh850_intc_raise( unsigned int ch );
void rh850_intc_clear( unsigned int ch );

/* Called by the EIINT entry with the EIIC value */
void rh850_intc_dispatch( uint32_t eiic );

#endif /* RH850_INTC_H */
