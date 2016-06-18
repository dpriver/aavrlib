/*******************************************************************************
 *	systick.c
 *
 *  system tick
 *
 *
 *  This file is part of aavrlib
 * 
 *  Copyright (C) 2015  Dennis Pinto Rivero
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/


// avr defines
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h> 

#include "uc/timers.h"
#include "uc/usart.h"
#include "systick.h"


/*
 * timer1 is a 16bit timer, so a valid configuration can be ctc mode with
 * presc = 8
 * top = 2000, 
 * so frequency results in 16000000/(8*2000) = 1000Hz, with a resolution of
 * 1/2 ms.
 * 
 * If systick is configured to work in a 8bit timer, it can be ctc mode with
 * presc = 64
 * top = 250
 * so frequency is 1000Hz again, with a resolution of 4ms.
 */

#if SYSTICK_RESOLUTION == 16

    #define PRESC       8
    #define SYSTICK_TOP_CNT     2000
    
#elif SYSTICK_RESOLUTION == 8

    #define PRESC       64
    #define SYSTICK_TOP_CNT     250
    
#endif

#define MAX_MIN UINT16_MAX
#define MAX_MS  59999
#define MAX_US  999


#define _TIMER_START_EXP2(TIMER)    TIMER ## _ctc(SYSTICK_PRESC(PRESC), SYSTICK_TOP_CNT)
#define _TIMER_START_EXP1(TIMER)    _TIMER_START_EXP2(TIMER)


// Start the timer configured to use by system tick
#define SYSTICK_TIMER_START()       _TIMER_START_EXP1(SYSTICK_TIMER)



// variables to count the system uptime
static volatile uint32_t curr_ms;




// Init system tick feature
void systick_init() {
    
	curr_ms = 0;
	sei();
    
    SYSTICK_TIMER_START();

}


// 0-999 us
uint16_t get_uptime_us() {
    
#if SYSTICK_RESOLUTION == 16
	return (uint16_t)SYSTICK_CURR_CNT() >> 1;  // 2000/2
#elif SYSTICK_RESOLUTION == 8
    return (uint16_t)SYSTICK_CURR_CNT() << 2;   // 250 * 4
#endif

}


uint32_t get_uptime_ms() {
	return (uint32_t)curr_ms;
}


// BUG -> Race condition
void get_uptime(time_t *time) {
    
#if SYSTICK_RESOLUTION == 16
	time->us = SYSTICK_CURR_CNT() >> 1;  // 2000/2
#elif SYSTICK_RESOLUTION == 8
    time->us = SYSTICK_CURR_CNT() << 2;   // 250 * 4
#endif

    time->ms = curr_ms;
}


void start_timeout(uint16_t ms, time_t *timeout) {

    timeout->ms = curr_ms + ms;    
}


uint8_t timeout_expired(time_t *timeout) {
    return (curr_ms > timeout->ms);
}


void delay_ms(uint16_t ms) {
    uint32_t _ms = curr_ms + ms;
    
    // if _ms overflows, this loop prevents from skiping the delay, waiting for 
    // curr_ms to also overflow
    //while (curr_ms > _ms);
    
    // There is a problem with the previous loop... if something interrupts 
    // just before it, time enought to actually overpass "ms", this will 
    // keep the system delaying for 2^(32) ms... which is ~50 days...
    
    
    // A possible aproach is to disable interrupts,
    // then execute the loop while (curr_ms > _ms);
    
    // actual delay busy wait
    while (curr_ms < _ms);
}


SYSTICK_ISR() {
    ++curr_ms;
}
