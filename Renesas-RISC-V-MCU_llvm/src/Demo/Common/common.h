/*
 * common.h
 *
 *  Created on: 14 Oct 2024
 *      Author: Pole
 */

#ifndef DEMO_COMMON_COMMON_H_
#define DEMO_COMMON_COMMON_H_

#define printf vcom_printf

void vcom_printf( char const * format, ...);
void machine_timer_enable(void);

#endif /* DEMO_COMMON_COMMON_H_ */
