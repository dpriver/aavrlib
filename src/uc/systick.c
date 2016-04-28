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
#include "uc/systick.h"
#include "uc/timers.h"


#define PRESC       8
#define SYSTICK_TOP_CNT     2000


#define _TIMER_START_EXP2(TIMER)    TIMER ## _ctc(SYSTICK_PRESC(PRESC), SYSTICK_TOP_CNT, 0)
#define _TIMER_START_EXP1(TIMER)    _TIMER_START_EXP2(TIMER)


// Start the timer configured to use by system tick
#define SYSTICK_TIMER_START()       _TIMER_START_EXP1(SYSTICK_TIMER)



// variables to count the system uptime
static uint16_t curr_sec;
static uint16_t curr_ms;




// Init system tick feature
void systick_init() {
    
	curr_ms = 0;
	curr_sec = 0;
	
    SYSTICK_TIMER_START();

}


// 0-999 us
uint16_t get_uptime_us() {
	return SYSTICK_CURR_CNT();
}


// 0-59999 miliseconds
uint16_t get_uptime_ms() {
	return curr_ms;
}


// 0-65535 secods
uint16_t get_uptime_sec() {
	return curr_sec;
}


// complete uptime
void get_uptime(uint16_t sec, uint16_t ms, uint16_t us) {
	sec = curr_sec;
	ms = curr_ms;
	us = SYSTICK_CURR_CNT();
}


SYSTICK_ISR() {
    
	// Counts 60.000 cycles at 1/ms freq 
	if (curr_ms == 59999) {
		++curr_sec;
		curr_ms = 0;
	}
	else {
		++curr_ms;
	}
}
