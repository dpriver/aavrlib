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

// timer 0 and 1
typedef enum {
	disabled=0x00, prescale_0=0x01, prescale_8=0x02, prescale_64=0x03, 
	prescale_256=0x04, prescale_1024=0x05
} prescale_0_1_t;

// timer2 
typedef enum {
	disabled2=0x0, prescale2_0=0x1, prescale2_8=0x2, prescale2_32=0x3, prescale2_64=0x4, 
	prescale2_128=0x5, prescale2_256=0x6, prescale2_1024=0x7
} prescale_2_t;



#define SOFTPWM_DUTY_ISR() ISR(TIMER2_COMPB_vect, ISR_BLOCK)

#define SOFTPWM_TOP_ISR() ISR(TIMER2_COMPA_vect, ISR_BLOCK)

#define SOFTPWM_TIMER timer2

#define SOFTPWM_PRESC(presc) prescale2_ ## presc

#define SOFTPWM_CURR_CNT() (TCNT2)


#define SOFTPWM_L_DUTY_ISR() ISR(TIMER0_COMPB_vect, ISR_BLOCK)

#define SOFTPWM_L_TOP_ISR() ISR(TIMER0_COMPA_vect, ISR_BLOCK)

#define SOFTPWM_L_TIMER timer0

#define SOFTPWM_L_PRESC(presc) prescale_ ## presc

#define SOFTPWM_L_CURR_CNT() (TCNT0)


#define SYSTICK_ISR ISR(TIMER1_COMPA_vect, ISR_BLOCK)

#define SYSTICK_TIMER timer1

#define SYSTICK_CURR_COUNT() (TCNT1)

#define SYSTICK_PRESC(presc) prescale_ ## presc



void timers_init();

/*******************************************************************************
 *         Timer 0
 *******************************************************************************
*/

// basic delay
void timer0_delay(uint8_t ms);

void timer0_ctc(prescale_0_1_t prescale, uint8_t top_cnt, uint8_t interrupt_cnt);

void timer0_set_interrupt_cnt(uint8_t interrupt_cnt);

// generate fast PWM in PIN6  
//	freq_pwm = F_CPU/((freq_cnt+1)*prescale)
//	duty	 = duty_cnt/freq_cnt
void timer0_fast_pwm(prescale_0_1_t prescale, uint8_t freq_cnt, uint8_t duty_cnt);

// generate phase corect PWM in PIN6  
//	freq_pwm = F_CPU/((2*freq_cnt)*prescale)
//	duty	 = duty_cnt/freq_cnt
void timer0_pcorrect_pwm(prescale_0_1_t prescale, uint8_t freq_cnt, uint8_t duty_cnt);

void timer0_stop();



/*******************************************************************************
 *         Timer 1
 *******************************************************************************
*/
void timer1_ctc(prescale_0_1_t prescale, uint16_t top_cnt, uint16_t interrupt_cnt);


/*******************************************************************************
 *         Timer 2
 *******************************************************************************
*/
void timer2_ctc(prescale_2_t prescale, uint8_t top_cnt, uint8_t interrupt_cnt);

void timer2_set_interrupt_cnt(uint8_t interrupt_cnt);

#endif /* __TIMERS */
