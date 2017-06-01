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
 ******************************************************************************/

#ifndef __ARDUINO_UNO_H
#define __ARDUINO_UNO_H

#ifdef __USE_BOARD
    #error "Multiple boards defined for project."
#endif

#define __USE_BOARD


#include <avr/io.h>
#include "ioport.h"

/*====================================================================
 *   Usable macros for I/O operations
 *====================================================================*/
 
// Single PIN access
#define _PIN_CONF_IN(pin)       IOPIN_CONF_IN(PORT(pin), _ ## pin) 
#define _PIN_CONF_OUT(pin)      IOPIN_CONF_OUT(PORT(pin), _ ## pin)
#define _PIN_WRITE_HIGH(pin)    IOPIN_WRITE_HIGH(PORT(pin), _ ## pin)
#define _PIN_WRITE_LOW(pin)     IOPIN_WRITE_LOW(PORT(pin), _ ## pin)
#define _PIN_WRITE(pin, value)  IOPIN_WRITE(PORT(pin), _ ## pin, value)
#define _PIN_READ(pin)          IOPIN_READ(PORT(pin), _ ## pin)
#define _PIN_SWITCH(pin)        IOPIN_SWITCH(PORT(pin), _ ## pin)
#define _PIN_PULLUP_ON(pin)     IOPIN_PULLUP_ON(PORT(pin), _ ## pin)
#define _PIN_PULLUP_OFF(pin)    IOPIN_PULLUP_OFF(PORT(pin), _ ## pin)


// Single PIN access
#define PIN_CONF_IN(pin)       _PIN_CONF_IN(pin) 
#define PIN_CONF_OUT(pin)      _PIN_CONF_OUT(pin)
#define PIN_WRITE_HIGH(pin)    _PIN_WRITE_HIGH(pin)
#define PIN_WRITE_LOW(pin)     _PIN_WRITE_LOW(pin)
#define PIN_WRITE(pin, value)  _PIN_WRITE(pin, value)
#define PIN_READ(pin)          _PIN_READ(pin)
#define PIN_SWITCH(pin)        _PIN_SWITCH(pin)
#define PIN_PULLUP_ON(pin)     _PIN_PULLUP_ON(pin)
#define PIN_PULLUP_OFF(pin)    _PIN_PULLUP_OFF(pin)

// Multiple PIN access
#define PORT_CONF_IN(port, mask)       IOPORT_CONF_IN(port, mask)
#define PORT_CONF_OUT(port, mask)      IOPORT_CONF_OUT(port, mask)
#define PORT_WRITE_HIGH(port, mask)    IOPORT_WRITE_HIGH(port, mask)
#define PORT_WRITE_LOW(port, mask)     IOPORT_WRITE_LOW(port, mask)
#define PORT_WRITE(port, mask, values) IOPORT_WRITE(port, mask, values)
#define PORT_READ(port, mask)          IOPORT_READ(port, mask)
#define PORT_SWITCH(port, mask)        IOPORT_SWITCH(port, mask)
#define PORT_PULLUP_ON(port, mask)     IOPORT_PULLUP_ON(port, mask)
#define PORT_PULLUP_OFF(port, mask)    IOPORT_PULLUP_OFF(port, mask)

// Get the port corresponding to pin
#define _PORT(pin)      pin ## _PORT
#define _REAL_PIN(pin)  _ ## pin

#define PORT(pin)       _PORT(pin)
#define REAL_PIN(pin)   _REAL_PIN(pin)

/*====================================================================
 *   Usable pins
 *====================================================================*/
 
// Analog pins
#define PIN_A0  PIN_A0
#define PIN_A1  PIN_A1
#define PIN_A2  PIN_A2
#define PIN_A3  PIN_A3
#define PIN_A4  PIN_A4
#define PIN_A5  PIN_A5

// Digital pins
#define PIN_0   PIN_0
#define PIN_1   PIN_1
#define PIN_2   PIN_2
#define PIN_3   PIN_3
#define PIN_4   PIN_4
#define PIN_5   PIN_5
#define PIN_6   PIN_6
#define PIN_7   PIN_7
#define PIN_8   PIN_8
#define PIN_9   PIN_9
#define PIN_10  PIN_10
#define PIN_11  PIN_11
#define PIN_12  PIN_12
#define PIN_13  PIN_13

/*====================================================================
 *   Usable pins for mask composition
 *====================================================================*/
// Analog pins
#define MPIN_A0	_BV(PORTC0)
#define MPIN_A1	_BV(PORTC1)
#define MPIN_A2	_BV(PORTC2)
#define MPIN_A3	_BV(PORTC3)
#define MPIN_A4	_BV(PORTC4)
#define MPIN_A5	_BV(PORTC5)

// Digital pins
#define MPIN_0	_BV(PORTD0)
#define MPIN_1	_BV(PORTD1)
#define MPIN_2	_BV(PORTD2)
#define MPIN_3	_BV(PORTD3)
#define MPIN_4  _BV(PORTD4)
#define MPIN_5	_BV(PORTD5)
#define MPIN_6	_BV(PORTD6)
#define MPIN_7	_BV(PORTD7)
#define MPIN_8	_BV(PORTB0)
#define MPIN_9	_BV(PORTB1)
#define MPIN_10	_BV(PORTB2)
#define MPIN_11	_BV(PORTB3)
#define MPIN_12	_BV(PORTB4)
#define MPIN_13	_BV(PORTB5)



/*====================================================================
 *   Internal representation of pins (DO NOT USE)
 *====================================================================*/
 /*
 * Definitions for use by the single pin access macros
 */
// Analog pins
#define _PIN_A0	PORTC0
#define _PIN_A1	PORTC1
#define _PIN_A2	PORTC2
#define _PIN_A3	PORTC3
#define _PIN_A4	PORTC4
#define _PIN_A5	PORTC5

// Digital pins
#define _PIN_0	PORTD0
#define _PIN_1	PORTD1
#define _PIN_2	PORTD2
#define _PIN_3	PORTD3
#define _PIN_4	PORTD4
#define _PIN_5	PORTD5
#define _PIN_6	PORTD6
#define _PIN_7	PORTD7
#define _PIN_8	PORTB0
#define _PIN_9	PORTB1
#define _PIN_10	PORTB2
#define _PIN_11	PORTB3
#define _PIN_12	PORTB4
#define _PIN_13	PORTB5

/*
 * Definitions for use by the PORT(pin) macro
 */
 // Analog pins
#define PIN_A0_PORT     (IOPORT_C)
#define PIN_A1_PORT     (IOPORT_C)
#define PIN_A2_PORT     (IOPORT_C)
#define PIN_A3_PORT     (IOPORT_C)
#define PIN_A4_PORT     (IOPORT_C)
#define PIN_A5_PORT     (IOPORT_C)

// Digital pins
#define PIN_0_PORT      (IOPORT_D)
#define PIN_1_PORT      (IOPORT_D)
#define PIN_2_PORT      (IOPORT_D)
#define PIN_3_PORT      (IOPORT_D)
#define PIN_4_PORT      (IOPORT_D)
#define PIN_5_PORT      (IOPORT_D)
#define PIN_6_PORT      (IOPORT_D)
#define PIN_7_PORT      (IOPORT_D)
#define PIN_8_PORT      (IOPORT_B)
#define PIN_9_PORT      (IOPORT_B)
#define PIN_10_PORT     (IOPORT_B)
#define PIN_11_PORT     (IOPORT_B)
#define PIN_12_PORT     (IOPORT_B)
#define PIN_13_PORT     (IOPORT_B)

#endif /* __ARDUINO_UNO_H */
