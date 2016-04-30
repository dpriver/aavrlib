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



#include <stdint.h> 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "util/systick.h"
#include "uc/timers.h"


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


#define _TIMER_START_EXP2(TIMER)    TIMER ## _ctc(SYSTICK_PRESC(PRESC), SYSTICK_TOP_CNT, 0)
#define _TIMER_START_EXP1(TIMER)    _TIMER_START_EXP2(TIMER)


// Start the timer configured to use by system tick
#define SYSTICK_TIMER_START()       _TIMER_START_EXP1(SYSTICK_TIMER)



// variables to count the system uptime
static uint16_t curr_ms;
static uint16_t curr_min;




// Init system tick feature
void systick_init() {
    
	curr_ms = 0;
	curr_min = 0;
	
    SYSTICK_TIMER_START();

}


// 0-999 us
uint16_t get_uptime_us() {
    
#if SYSTICK_RESOLUTION == 16
	return SYSTICK_CURR_CNT() >> 1;  // 2000/2
#elif SYSTICK_RESOLUTION == 8
    return SYSTICK_CURR_CNT() << 2;   // 250 * 4
#endif

}


// 0-59999 miliseconds
uint16_t get_uptime_ms() {
	return curr_ms;
}


// 0-65535 minutes
uint16_t get_uptime_min() {
	return curr_min;
}


// complete uptime
void get_uptime(uint16_t *min, uint16_t *ms, uint16_t *us) {
	*min = curr_min;
	*ms = curr_ms;
    
#if SYSTICK_RESOLUTION == 16
	*us = SYSTICK_CURR_CNT() >> 1;  // 2000/2
#elif SYSTICK_RESOLUTION == 8
    *us = SYSTICK_CURR_CNT() << 2;   // 250 * 4
#endif

}


void delay_ms(uint16_t ms) {
    uint16_t _min = curr_min;
    uint16_t _ms = curr_ms;
    
    // calculate ms and min to stop looping
    if ((_ms + ms) > MAX_MS) {
        _min = _min + 1;
        _ms = _ms + ms - MAX_MS;
    }
    else {
        _ms = _ms + ms;
    }
    
    while( (_min > curr_min) || ( (_min == curr_min) && (_ms > curr_ms) ));
}


SYSTICK_ISR() {
    
	// Counts 60.000 cycles at 1/ms freq 
	if (curr_ms == MAX_MS) {
		++curr_min;
		curr_ms = 0;
	}
	else {
		++curr_ms;
	}
}
