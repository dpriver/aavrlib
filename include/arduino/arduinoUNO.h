/*******************************************************************************
 *	arduinoUNO.h
 *
 *  Definitions and macros for the arduinoUNO board
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

#include <avr/io.h>


// Arduino pins convenience macros
// Really, PORTxn is the corresponding PIN for the IOPORT value register, but, 
// since all 3 IOPORTS registers (PORTx, PINx, DDRx) use the same bit for the 
// same pin, it works... (by the time) 
// if this changes in the future, a fix would be mandatory


// Digital IOport A
#define PIN_0	(1 << PORTD0)
#define PIN_1	(1 << PORTD1)
#define PIN_2	(1 << PORTD2)
#define PIN_3	(1 << PORTD3)
#define PIN_4	(1 << PORTD4)
#define PIN_5	(1 << PORTD5)
#define PIN_6	(1 << PORTD6)
#define PIN_7	(1 << PORTD7)

// Digital IOPort B
#define PIN_8	(1 << PORTB0)
#define PIN_9	(1 << PORTB1)
#define PIN_10	(1 << PORTB2)
#define PIN_11	(1 << PORTB3)
#define PIN_12	(1 << PORTB4)
#define PIN_13	(1 << PORTB5)

// Analog IOPort
#define PIN_A0	(1 << PORTC0)
#define PIN_A1	(1 << PORTC1)
#define PIN_A2	(1 << PORTC2)
#define PIN_A3	(1 << PORTC3)
#define PIN_A4	(1 << PORTC4)
#define PIN_A5	(1 << PORTC5)


#define PIN_PWM_0	PIN_6


// _MODE values
// SET can be used for both _CONFIG_MODE and _VALUE_MODE
#define SET		= (

// _CONFIG_MODE values
#define INPUT 	|= (
#define OUTPUT 	&= ~(

//	_VALUE_MODE values
#define HIGH	|= (
#define LOW		$= ~(

// _PORT values
#define PORT_A	DDRD
#define PORT_B	DDRB


// Configure and set values for digital I/O pins
// for example:
// 	pins 0, 3, 5 as output    
//	DIGITAL_CONFIG(OUTPUT, PORT_A, PIN0 | PIN3 | PIN5);

// 	pins 8, 12, 13 as input    
//	DIGITAL_CONFIG(OUTPUT, PORT_B, PIN8 | PIN12 | PIN13);

// 	pins 0, 3 as 1, and 11 as 0
//	DIGITAL_VALUE(HIGH, PORT_A, PIN0 | PIN3);
//	DIGITAL_VALUE(LOW, PORT_B, PIN11);

// Of course, unless included in the mask, or invoked in SET mode, the other
// port pins keep their previous value and configuration.

#define DIGITAL_CONFIG(_CONFIG_MODE, _PORT,  pinmask) \
	_PORT _CONFIG_MODE pinmask )


#define DIGITAL_VALUE(_VALUE_MODE, _PORT, pinmask) \
	_PORT _VALUE_MODE pinmask )
