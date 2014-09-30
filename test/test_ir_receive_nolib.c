/*====================================================================================================================================
 * Daniel Pinto Rivero	09-08-2014 Cáceres, Spain
 * program to play with ir receiver before making the lib functions
 *=====================================================================================================================================*/

#include <stdint.h>
#include <avr/interrupt.h>
#include "systick.h"
#include "delay.h"
#include "usart.h"
#include "ir.h"

#define NUM_VALORES 1000

void comm_handler(uint16_t address, uint8_t command){
	switch(command){
		case 0:
			DIGITAL_PORT_B &= ~_BV(DIGITAL_8);
			DIGITAL_PORT_B &= ~_BV(DIGITAL_9);
			break;
		case 8:
			DIGITAL_PORT_B |= _BV(DIGITAL_8);
			break;
		case 136:
			DIGITAL_PORT_B |= _BV(DIGITAL_9);
			break;
	}
}

int main(void){

	init_system_tick();
	usart_init();
	sei();

	// pin del sensor
	DIGITAL_CONF_REG_B = _BV(DIGITAL_CONF_8) | _BV(DIGITAL_CONF_10) | _BV(DIGITAL_CONF_11) | _BV(DIGITAL_CONF_12);

	// led test
	usart_print("Led_test:");
	DIGITAL_PORT_B |= _BV(DIGITAL_12);
	delay_ms(250);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_12);
	DIGITAL_PORT_B |= _BV(DIGITAL_11);
	delay_ms(250);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_11);
	DIGITAL_PORT_B |= _BV(DIGITAL_10);
	delay_ms(250);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_10);
	DIGITAL_PORT_B |= _BV(DIGITAL_8);
	delay_ms(250);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_8);
	DIGITAL_PORT_B |= _BV(DIGITAL_9);
	delay_ms(250);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_9);
	delay_ms(250);
	DIGITAL_PORT_B |= _BV(DIGITAL_8);
	DIGITAL_PORT_B |= _BV(DIGITAL_9);
	DIGITAL_PORT_B |= _BV(DIGITAL_10);
	DIGITAL_PORT_B |= _BV(DIGITAL_11);
	DIGITAL_PORT_B |= _BV(DIGITAL_12);
	delay_ms(500);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_8);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_9);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_10);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_11);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_12);	
	usart_print("................Completed.\n");
	delay_ms(1000);

	init_IR_receiver(comm_handler);
	
	
	DIGITAL_PORT_B |= _BV(DIGITAL_12); // 12

	while(1){
		DIGITAL_PORT_B |= _BV(DIGITAL_10);
		delay_ms(500);
		DIGITAL_PORT_B &= ~_BV(DIGITAL_10);
		delay_ms(500);
	}

}
