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

/*******************************************************************************
 *   PRESCALERS
 ******************************************************************************/

// timer 0 prescalers
typedef enum {
	disabled0=0x00, prescale0_0=0x01, prescale0_8=0x02, prescale0_64=0x03, 
	prescale0_256=0x04, prescale0_1024=0x05
} prescale0_t;

// timer 1 prescalers
typedef enum {
	disabled1=0x00, prescale1_0=0x01, prescale1_8=0x02, prescale1_64=0x03, 
	prescale1_256=0x04, prescale1_1024=0x05
} prescale1_t;

// timer 2 prescalers
typedef enum {
	disabled2=0x0, prescale2_0=0x1, prescale2_8=0x2, prescale2_32=0x3, prescale2_64=0x4, 
	prescale2_128=0x5, prescale2_256=0x6, prescale2_1024=0x7
} prescale2_t;



/*******************************************************************************
 *   MACROS
 ******************************************************************************/
 
// TIMER 0 macros
#define TIMER0_COMPA_ISR    ISR(TIMER0_COMPA_vect, ISR_BLOCK)
#define TIMER0_COMPB_ISR    ISR(TIMER0_COMPB_vect, ISR_BLOCK)
#define TIMER0_TOV_ISR      ISR(TIMER0_TOV_vect, ISR_BLOCK)
#define TIMER0_TIMER        timer0
#define TIMER0_PRESCALER(presc) prescale0_ ## presc
#define TIMER0_CURR_CNT     (TCNT0)   
#define TIMER0_RESOLUTION   (8) 

// TIMER 1 macros
#define TIMER1_COMPA_ISR    ISR(TIMER1_COMPA_vect, ISR_BLOCK)
#define TIMER1_COMPB_ISR    ISR(TIMER1_COMPB_vect, ISR_BLOCK)
#define TIMER1_TOV_ISR      ISR(TIMER1_TOV_vect, ISR_BLOCK)
#define TIMER1_TIMER        timer1
#define TIMER1_PRESCALER(presc) prescale1_ ## presc
#define TIMER1_CURR_CNT     (TCNT1)   
#define TIMER1_RESOLUTION   (16)  

// TIMER 2 macros
#define TIMER2_COMPA_ISR    ISR(TIMER2_COMPA_vect, ISR_BLOCK)
#define TIMER2_COMPB_ISR    ISR(TIMER2_COMPB_vect, ISR_BLOCK)
#define TIMER2_TOV_ISR      ISR(TIMER2_TOV_vect, ISR_BLOCK)
#define TIMER2_TIMER        timer2
#define TIMER2_PRESCALER(presc) prescale2_ ## presc
#define TIMER2_CURR_CNT     (TCNT2)
#define TIMER2_RESOLUTION   (8) 


// GENERIC TIMER MACROS (internal use)
// Needed in order to expand correctly the timer macros
#define _COMPB_ISR_EXP(TIM)      TIM ## _COMPB_ISR
#define _COMPB_ISR(TIM)          _COMPB_ISR_EXP(TIM)

#define _COMPA_ISR_EXP(TIM)       TIM ## _COMPA_ISR
#define _COMPA_ISR(TIM)           _COMPA_ISR_EXP(TIM)

#define _TIMER_EXP(TIM)         TIM ## _TIMER
#define _TIMER(TIM)             _TIMER_EXP(TIM)

#define _PRESC_EXP(TIM,presc)   TIM ## _PRESCALER(presc)
#define _PRESC(TIM,presc)       _PRESC_EXP(TIM, presc)

#define _CURR_CNT_EXP(TIM)      TIM ## _CURR_CNT
#define _CURR_CNT(TIM)          _CURR_CNT_EXP(TIM)

#define _RESOLUTION_EXP(TIM)    TIM ## _RESOLUTION
#define _RESOLUTION(TIM)        _RESOLUTION_EXP(TIM)


/*******************************************************************************
 *   TIMER APPLICATIONS MACROS
 ******************************************************************************/
 
/* 
 * Timers configuration 
 * 
 * All the library implementations that depend on timers are listed here.
 * 
 * To configure the timer in wih a certain library should run, it has to be specified
 * below, so each library has a timer asigned.
 * 
 * Note that libraries with the same assigned timer should not be used in the same program.
 * Doing so may result in unpredictable results, such as compile or run time errors. Please, if you
 * try to do so, don't feel confident if the compiler ends succesfully, without checking the
 * correctness of the generated code or the program behaviour.
 **/
#define _SOFTPWM_S_TIMER TIMER0
#define _SOFTPWM_L_TIMER TIMER2
#define _SYSTICK_TIMER   TIMER1


/* short pulse softPWM macros*/
#define SOFTPWM_S_DUTY_ISR()     _COMPB_ISR(_SOFTPWM_S_TIMER)
#define SOFTPWM_S_TOP_ISR()      _COMPA_ISR(_SOFTPWM_S_TIMER)
#define SOFTPWM_S_TIMER          _TIMER(_SOFTPWM_S_TIMER)
#define SOFTPWM_S_PRESC(presc)   _PRESC(_SOFTPWM_S_TIMER, presc)
#define SOFTPWM_S_CURR_CNT()     _CURR_CNT(_SOFTPWM_S_TIMER)

/* long pulse softPWM macros*/
#define SOFTPWM_L_DUTY_ISR()     _COMPB_ISR(_SOFTPWM_L_TIMER)  
#define SOFTPWM_L_TOP_ISR()      _COMPA_ISR(_SOFTPWM_L_TIMER)
#define SOFTPWM_L_TIMER          _TIMER(_SOFTPWM_L_TIMER)
#define SOFTPWM_L_PRESC(presc)   _PRESC(_SOFTPWM_L_TIMER, presc)
#define SOFTPWM_L_CURR_CNT()     _CURR_CNT(_SOFTPWM_L_TIMER)

/* system tick */
#define SYSTICK_ISR()            _COMPB_ISR(_SYSTICK_TIMER)
#define SYSTICK_TIMER            _TIMER(_SYSTICK_TIMER)
#define SYSTICK_PRESC(presc)     _PRESC(_SYSTICK_TIMER, presc)
#define SYSTICK_CURR_CNT()       _CURR_CNT(_SYSTICK_TIMER)
#define SYSTICK_RESOLUTION       _RESOLUTION(_SYSTICK_TIMER)

/*******************************************************************************
 *   TIMERS FUNCTIONALITY
 ******************************************************************************/

void timers_init();


// basic delay
void timer0_delay(uint8_t ms);

void timer0_ctc(prescale0_t prescale, uint8_t top_cnt, uint8_t interrupt_cnt);

void timer0_set_interrupt_cnt(uint8_t interrupt_cnt);

// generate fast PWM in PIN6  
//	freq_pwm = F_CPU/((freq_cnt+1)*prescale)
//	duty	 = duty_cnt/freq_cnt
void timer0_fast_pwm(prescale0_t prescale, uint8_t freq_cnt, uint8_t duty_cnt);

// generate phase corect PWM in PIN6  
//	freq_pwm = F_CPU/((2*freq_cnt)*prescale)
//	duty	 = duty_cnt/freq_cnt
void timer0_pcorrect_pwm(prescale0_t prescale, uint8_t freq_cnt, uint8_t duty_cnt);

void timer0_stop();



/*******************************************************************************
 *         Timer 1
 *******************************************************************************
*/
void timer1_ctc(prescale1_t prescale, uint16_t top_cnt, uint16_t interrupt_cnt);

void timer1_set_interrupt_cnt(uint8_t interrupt_cnt);

/*******************************************************************************
 *         Timer 2
 *******************************************************************************
*/
void timer2_ctc(prescale2_t prescale, uint8_t top_cnt, uint8_t interrupt_cnt);

void timer2_set_interrupt_cnt(uint8_t interrupt_cnt);

#endif /* __TIMERS */
