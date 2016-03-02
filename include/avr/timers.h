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

 
#ifndef _TIMER_
#define _TIMER_

#include <avr/io.h>
#include <avr/power.h>
#include <stdint.h>


enum{timer0, timer1, timer2};
enum{disabled=0x00, no_prescale=0x01, prescale_8=0x02, prescale_64=0x03, prescale_256=0x04, prescale_1024=0x05};
enum{match_disconected=0x00, match_toggle=0x10, match_clear=0x20, match_set=0x30};


/*===========================================================
 * Timer 0
 *===========================================================*/
#define timer0_setup_mode_CTC(prescale) \
 	TCCR0A = 0x02; \
 	TCCR0B = 0x00 | prescale;

#define timer0_setup_compA(mode, ocr) \
 	TCCR0A |= mode << 2; \
 	OCR0A 	= ocr;

#define timer0_setup_compB(mode, ocr) \
 	TCCR0A |= mode; \
 	OCR0B	= ocr;

#define timer0_en_int_compA() TIMSK0 |= _BV(OCIE0A);
#define timer0_dis_int_compA() TIMSK0 &= ~_BV(OCIE0A);
#define timer0_en_int_compB() TIMSK0 |= _BV(OCIE0B);
#define timer0_dis_int_compB() TIMSK0 &= ~_BV(OCIE0B);
#define timer0_start() power_timer0_enable();
#define timer0_stop() power_timer0_disable();

/*===========================================================
 * Timer 1
 *===========================================================*/
#define timer1_setup_mode_CTC(prescale) \
 	TCCR1A = 0x00; \
 	TCCR1B = 0x08 | prescale;

#define timer1_setup_compA(mode, ocr) \
 	TCCR1A |= mode << 2; \
 	OCR1A 	= ocr;

#define timer1_setup_compB(mode, ocr) \
 	TCCR1A |= mode; \
 	OCR1B	= ocr;

#define timer1_en_int_compA() TIMSK1 |= _BV(OCIE1A);
#define timer1_dis_int_compA() TIMSK1 &= ~_BV(OCIE1A);
#define timer1_en_int_compB() TIMSK1 |= _BV(OCIE1B);
#define timer1_dis_int_compB() TIMSK1 &= ~_BV(OCIE1B);
#define timer1_start() power_timer1_enable();
#define timer1_stop() power_timer1_disable();

#endif
