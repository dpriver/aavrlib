/*====================================================================================================================================
 * Daniel Pinto Rivero	09-08-2014 Cáceres, Spain
 * timer.h
 * Library with all the functions needed to work with hardware timers
 *=====================================================================================================================================*/


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
