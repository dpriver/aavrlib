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
 ********************************************************************************/

/*
 * avr AtMega328p have 3 timers (all of them with PWM):
 *	- 8bit compare reg. timer
 *	- 16bit compare reg. timer
 *	- 8bit compare reg. timer with async. operation
 *
 */

 
#ifndef __TIMERS
#define __TIMERS

#include <avr/io.h>
#include <avr/power.h>
#include <stdint.h>


typedef enum {
	disabled=0x00, no_prescale=0x01, prescale_8=0x02, prescale_64=0x03, 
	prescale_256=0x04, prescale_1024=0x05
} prescale_t;

#define SOFTPWM_DUTY_ISR() ISR(TIMER2_COMPB_vect, ISR_BLOCK)

#define SOFTPWM_TOP_ISR() ISR(TIMER2_COMPA_vect, ISR_BLOCK)

#define PWM_TIMER timer2


void timers_init();

// basic delay
void timer0_delay(uint8_t ms);

// generate fast PWM in PIN6  
//	freq_pwm = F_CPU/((freq_cnt+1)*prescale)
//	duty	 = duty_cnt/freq_cnt
void timer0_fast_pwm(prescale_t prescale, uint8_t freq_cnt, uint8_t duty_cnt);

// generate phase corect PWM in PIN6  
//	freq_pwm = F_CPU/((2*freq_cnt)*prescale)
//	duty	 = duty_cnt/freq_cnt
void timer0_pcorrect_pwm(prescale_t prescale, uint8_t freq_cnt, uint8_t duty_cnt);

void timer0_stop();

// Init system tick feature
void timer1_systick_init();

// 0-999 us
uint16_t get_uptime_us();

// 0-59999 miliseconds
uint16_t get_uptime_ms();

// 0-65535 minutes
uint16_t get_uptime_sec();

// complete uptime
void get_uptime(uint16_t min, uint16_t ms, uint16_t us);

void timer2_ctc(prescale_t prescale, uint8_t top_cnt, uint8_t interrupt_cnt);

void timer2_set_interrupt_cnt(uint8_t interrupt_cnt);

#endif /* __TIMERS */
