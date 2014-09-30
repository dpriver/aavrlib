#include "systick.h"
#include "delay.h"
#include "usart.h"
#include <avr/interrupt.h>


int main(void){

	init_system_tick();
	usart_init();
	sei();

	// pin del sensor
	DIGITAL_CONF_REG_B = _BV(DIGITAL_CONF_11) | _BV(DIGITAL_CONF_12);


	// led test
	DIGITAL_PORT_B |= _BV(DIGITAL_12);
	delay_ms(250);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_12);
	DIGITAL_PORT_B |= _BV(DIGITAL_11);
	delay_ms(250);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_11);
	DIGITAL_PORT_B |= _BV(DIGITAL_10);
	delay_ms(250);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_10);

	delay_ms(250); 
	delay_ms(250);
	delay_ms(250);
	delay_ms(250);

/*
	DIGITAL_PORT_B |= _BV(DIGITAL_12);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_11);

	usart_send((uint8_t)0x41);
	delay_ms_1(250); 
	delay_ms_1(250);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_12);
	DIGITAL_PORT_B |= _BV(DIGITAL_11);
	delay_ms_1(250);
	delay_ms_1(250);
*/

	while(1){
		DIGITAL_PORT_B |= _BV(DIGITAL_12);
		DIGITAL_PORT_B &= ~_BV(DIGITAL_11);

		usart_print("Dale a tu cuerpo alegría macarena que tu cuerpo es pa darle alegria y cosa buena, dale a tu cuerpo alegría macarena, eeeeeeh, macarena aaaaaaaayy!\n");
		usart_printnumber((uint8_t)23);
		delay_ms(250); 
		delay_ms(250);
		DIGITAL_PORT_B &= ~_BV(DIGITAL_12);
		DIGITAL_PORT_B |= _BV(DIGITAL_11);
		delay_ms(250);
		delay_ms(250);
	}



	return 0;
}