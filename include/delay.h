/*====================================================================================================================================
 * Daniel Pinto Rivero	09-08-2014 Cáceres, Spain
 * delay.h
 * Library with diferent delay implementations
 *=====================================================================================================================================*/

#ifndef _DELAY_
#define _DELAY_

#include <stdint.h>
#include "timer.h"
 
/*
 * Busy millisec delay implementation
 * Iterates a number of times to cover the delay ms.
 * It's recommended only for small delay time with low probability of being interrupted, because
 * the processor is ocupied during delay time and interrupts are disabled.
 */
void delay_ms_0();

/*
 * 8-bit timer millisec implementation
 */
void delay_ms_1(uint16_t ms);

/*
 * 16-bit timer millisec implementation 
 */
void delay_ms_2();

/*
 * cycle delay implementation
 */
void delay_cycle();

#endif