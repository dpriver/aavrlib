/*******************************************************************************
 *	timer.h
 *
 *  timers
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


/************************** REGISTERS ******************************************
 * TCCRxA   COM0A1	COM0A0	COM0B1	COM0B0	-		-		WGM01	WGM00
 * TCCRxB	FOC01	FOC0B	-		-		WGM02	CS02	CS01	CS00
 * TCNTx[7:0]
 * OCRxA[7:0]
 * OCRxB[7:0
 * TIMSKx	-		-		-		-		-		OCIE0B	OCIEOA	TOIE0
 * TIFRx	-		-		-		-		-		OCF0B	OCF0A	TOV0
 */

/***************************** PINS ********************************************
 * OCxA
 * OCxB
 */
/*
 * avr AtMega328p have 3 timers (all of them with PWM):
 *	- 8bit compare reg. timer
 *	- 16bit compare reg. timer
 *	- 8bit compare reg. timer with async. operation
 *
 */


/*
 * In programs using timers, timers_init() have to be called at the beggining
 * 
 * Then, if a setup functions is called, the corresponding timer is configured,
 * when a start function is called, the timer is blocked and start counting.
 * anytime, the corresponding stop function can be called to stop and release
 * the timer
 */

#include <stdint.h> 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uc/timers.h"

// variables to count the system uptime
static uint16_t curr_min;
static uint16_t curr_ms;



void timers_init() {
	
	TIMSK0 = 0;
	TIFR0 = 0;
	TIMSK1 = 0;
	TIFR1 = 0;
	TIMSK2 = 0;
	TIFR2 = 0;	
	
	power_timer0_disable();
	power_timer1_disable();
	power_timer2_disable();
}


// basic delay
void timer0_delay(uint8_t ms) {
	power_timer0_enable();
	
}


// generate fast PWM in PIN6  
//	freq_pwm = F_FPU/((freq_cnt+1)*prescale)
//	duty	 = duty_cnt/freq_cnt
void timer0_fast_pwm(prescale_t prescale, uint8_t freq_cnt, uint8_t duty_cnt) {
	// clear OC0B on compare match (with OCR0B)
	// fast PWM with OCR0A as TOP
	power_timer0_enable();
	TCNT0 	= 0;
	OCR0A 	= freq_cnt;
	OCR0B 	= duty_cnt;
	TIMSK0 	= 0;
	TCCR0A 	= (2 << COM0B0) | (3 << WGM00);
	TCCR0B 	= (1 << WGM02) | (prescale << CS00);
}


// generate phase corect PWM in PIN6  
//	freq_pwm = F_FPU/((2*freq_cnt)*prescale)
//	duty	 = duty_cnt/freq_cnt
void timer0_pcorrect_pwm(prescale_t prescale, uint8_t freq_cnt, uint8_t duty_cnt) {
	// clear OC0B on compare match (with OCR0B)
	// phase correct PWM with OCR0A as TOP
	power_timer0_enable();
	TCNT0 	= 0;
	OCR0A 	= freq_cnt;
	OCR0B 	= duty_cnt;
	TIMSK0 	= 0;
	TCCR0A 	= (2 << COM0B0) | (1 << WGM00);
	TCCR0B 	= (1 << WGM02) | (prescale << CS00);
}


void timer0_stop() {
	power_timer0_disable();
}


// Init system tick feature
void timer1_init_systick() {
	curr_ms = 0;
	curr_min = 0;
	
	power_timer1_enable();
	
	TCNT1 	= 0;
	OCR1A 	= 2000;
	OCR1B 	= 0;
	TIMSK1 	= (1 << OCIE1A);
	TCCR1A 	= 0;
	TCCR1B 	= (1 << WGM12) | (prescale_8 << CS10);
}


// 0-999 us
uint16_t get_uptime_us() {
	return TCNT1;
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
void get_uptime(uint16_t min, uint16_t ms, uint16_t us) {
	min = curr_min;
	ms = curr_ms;
	us = TCNT1;
}


// System tick ISR
ISR(TIMER0_COMPA_vect, ISR_BLOCK) {
	if (curr_ms == 59999) {
		++curr_min;
		curr_ms = 0;
	}
	else {
		++curr_ms;
	}
}
