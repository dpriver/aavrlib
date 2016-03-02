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
#include "avr/timers.h"

/*
static uint8_t timer_stat[3];

void timers_init() {
	
	timer_stat[0] = TIMER_OFF;
	timer_stat[1] = TIMER_OFF;
	timer_stat[2] = TIMER_OFF;
	
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


uint8_t timer_status(uint8_t timer) {
	return timer_stat[timer];
}
*/


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


/*------------------------------------------------------------------------------
 *  TIMER 0
 *----------------------------------------------------------------------------*/

/*
 * Setup timer 0 to work in non PWM mode ( normal or Clear on Compare match)
 * 
 * Count direction 	-> UP
 * Count behavior 	-> overflows at TOP or Clears at OCRxA
 *
uint8_t timer0_setup(timer_prescale_t prescale, timer_mode_t mode, 
	uint8_t pwm_limit, pin_mode_t pin_A, pin_mode_t pin_B, 
	uint8_t comp_A, uint8_t comp_B) 
{ 	
	if (timer_stat[0] == TIMER_ON)
		return -1;

	power_timer0_enable();
	timer_stat[0] = TIMER_ON;
	
	TCNT0	= 0;
 	TCCR0A	= (pin_A << 6) | (pin_B << 4) | (mode);
 	TCCR0B	= (pwm_limit << 3) | (prescale);
	OCR0A 	= comp_A;
	OCR0B 	= comp_B;
	
	return 0;
}
*/

/*
 * Setup timer 0 to work in non PWM mode ( normal or Clear on Compare match)
 * 
 * Count direction 	-> UP
 * Count behavior 	-> overflows at TOP or Clears at OCRxA
 *
uint8_t timer1_setup(timer_prescale_t prescale, timer_mode_t mode, 
	uint8_t pwm_limit, pin_mode_t pin_A, pin_mode_t pin_B, 
	uint16_t comp_A, uint16_t comp_B) 
{ 	
	if (timer_stat[1] == TIMER_ON)
		return -1;

	power_timer0_enable();
	timer_stat[1] = TIMER_ON;
	
	TCNT1	= 0;
 	TCCR1A	= (pin_A << 6) | (pin_B << 4) | (mode);
 	TCCR1B	= (pwm_limit << 3) | (prescale);
	OCR1A 	= comp_A;
	OCR1B 	= comp_B;
	
	return 0;
}
*/
