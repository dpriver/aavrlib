/*******************************************************************************
 *	usart.h
 *
 *  usart
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
 
#include "avr/usart.h"

void usart_printnumber32(uint32_t number){
	uint8_t digits[10] = {'0','0','0','0','0','0','0','0','0','0'};
	uint8_t index = 9;

	for(; number > 0 ; index--, number/=10)
		digits[index] = (number % 10) + '0';

	for(index = 0 ; index < 10 ; index++)
		usart_send(digits[index]);
}

void usart_printnumber(uint8_t number){
	uint8_t digits[3] = {'0','0','0'};
	uint8_t index = 2;


	for(; number > 0 ; index--, number/=10)
		digits[index] = (number % 10) + '0';

	usart_send(digits[0]);
	usart_send(digits[1]);
	usart_send(digits[2]);
}

void usart_print(char* string){
	while(*string != '\0'){
		usart_send(*string);
		string++;
	}
}

void usart_send(uint8_t data_byte){
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data_byte;
}
