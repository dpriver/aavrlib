/*******************************************************************************
 *	ioports.h
 *
 *  ioports
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

/* IOports registers
 * 
 * MCUCR	-> MCU Control Register (bit 4)
 * 
 * PORTB	|
 * PORTC	|-> Port Data Register B,C,D
 * PORTD	|
 * 
 * DDRB		|
 * DDRC		|-> Port Direction Register B,C,D
 * DDRD		|
 * 
 * PINB		|
 * PINC		|-> Port Input Pin Address B,C,D
 * PIND		|
 */


/*
 * Task to do in ioports.c
 * 
 * 1. Configure the pins direction
 * 2. Set and get pin values
 * 3. get rid of the pin current function (alternate functions)
 */
