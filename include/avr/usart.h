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


#ifndef _USART
#define _USART

#include <stdint.h>
#include <avr/io.h>

// BAUD = Fose/16/(UBBR0+1)
// setting of baud rate UBRR0=103=0x67 9600 baud rate
// setting of baud rate UBRR0=3=0x03   250k baud rate
// setting the frame format 1bit-stop 8bit-data
// enable transmitter or receiver

#define usart_init() \
	UBRR0H = 0x00; \
	UBRR0L = 0x01; \
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); \
	UCSR0B = _BV(TXEN0);

void usart_send(uint8_t data_byte);
void usart_printnumber(uint8_t number);
void usart_printnumber32(uint32_t number);
void usart_print(char* string);


#endif
