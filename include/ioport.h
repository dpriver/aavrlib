/*******************************************************************************
 *	ioports.h
 *
 *  Definitions and macros for I/O
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
#ifndef __IOPORT_H
#define __IOPORT_H
 
#include <avr/io.h>
// PINx    if written (switch vale of PORTx) if read (pin value syncronized)
// PORTx   pin value (if configured as input, 1-> pullup)
// DDRx    pin direction (1-> output, 0->input)


// changing from input low to output high requires and intermediate step
// input pullup or output low
 
 
 // PORTD  2B
 // DDRD   2A
 // PIND  29
 
 // PORTC  28
 // DDRC   27
 // PINC  26
 
 // PORTB  25
 // DDRB   24
 // PINB   23
 

typedef enum {IOPORT_B = 0x5+0x20, IOPORT_C = 0x8+0x20, IOPORT_D = 0xB+0x20} ioport_t;

// IOPORTS
#define WRITE_PORT_W(port) (*(volatile uint8_t *)(port))
#define CONF_PORT_WR(port) (*(volatile uint8_t *)(port - 1))
#define READ_PORT_R(port)  (*(volatile uint8_t *)(port - 2))

#define SWITCH_PORT_W(port) (*(volatile uint8_t *)(port - 2))
#define PULLUP_PORT_W(port) (*(volatile uint8_t *)(port))


// PIN access
#define IO_CONF_IN(port, pin)       CONF_PORT_WR(port) &= ~_BV(pin)
#define IO_CONF_OUT(port, pin)      CONF_PORT_WR(port) |= _BV(pin)
#define IO_WRITE_HIGH(port, pin)    WRITE_PORT_W(port) |= _BV(pin)
#define IO_WRITE_LOW(port, pin)     WRITE_PORT_W(port) &= ~_BV(pin)
#define IO_WRITE(port, pin, value)  WRITE_PORT_W(port) = (WRITE_PORT_WR(port) & ~_BV(pin)) | (value << pin)
#define IO_READ(port, pin)          ((READ_PORT_R(port) & _BV(pin)) >> pin)
#define IO_SWITCH(port, pin)        SWITCH_PORT_W(port) |= _BV(pin)
#define IO_PULLUP_ON(port, pin)     PULLUP_PORT_W(port) |= _BV(pin)
#define IO_PULLUP_OFF(port, pin)    PULLUP_PORT_W(port) &= ~_BV(pin)

#endif /* __IOPORT_H */
