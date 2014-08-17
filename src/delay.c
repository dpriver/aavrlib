/*====================================================================================================================================
 * Daniel Pinto Rivero	09-08-2014 Cáceres, Spain
 * delay.c 
 * Library with diferent delay implementations
 *=====================================================================================================================================*/

#include "delay.h"
#include "timer.h"
#include <avr/interrupt.h>

enum {timer0, timer1, timer2};

volatile static struct {
	uint16_t duration;
	uint8_t blocked;
} timer_attr[3];


void delay_ms_0(){
	#warning TODO "Not implemented"
	// NOT IMPLEMENTED
}

void delay_ms_1(uint16_t ms){
	timer_attr[timer0].duration = ms;
	timer0_setup_mode_CTC(prescale_1024);
	timer0_setup_compA(match_disconected, (uint8_t)16);
	timer0_en_int_compA();
	timer0_start();

	while(timer_attr[timer0].duration > 0);
}

void delay_ms_2(){
	#warning TODO "Not implemented"
	// NOT IMPLEMENTED
}

void delay_cycle(){
	#warning TODO "Not implemented"
	// NOT IMLPEMENTED
}

ISR(TIMER0_COMPA_vect, ISR_BLOCK){
	if(timer_attr[timer0].duration <= 0){
		timer0_dis_int_compA();
		timer0_stop();
	}
	else
		timer_attr[timer0].duration--;
}