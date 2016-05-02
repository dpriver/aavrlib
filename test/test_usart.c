/*******************************************************************************
 *  test_usart.c
 *
 *  usart test
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
 *******************************************************************************/
 

#include <avr/io.h>
#include <avr/interrupt.h>

#include <uc/usart.h>
#include <systick.h>


int main(void){

	systick_init();
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
