/*******************************************************************************
 *	system.h
 *
 *  interrupt, clock, and sleep configuration
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

#include <avr/power.h>
#include <avr/interrupt.h>

/* Clock registers
 * 
 * OSCCAL	-> Oscillator calibration Register
 * CLKPR	-> Clock Prescale Register
*/

/* Power registers
 * 
 * SMCR		-> Sleep Mode Control Register
 * MCUCR	-> MCU Control Register (bits 6,5)
 * PRR		-> Power Reduction Register
 */


/* System control and reset registers
 * 
 * MCUSR	-> MCU Status Register
 * WDTCSR	-> Watchdog Timer Control Register
 */

/* Interrupt registers
 * 
 * MCUCR	-> MCU Control Register (bits 1,0)
 */

/* External Interrupt registers
 * 
 * EICRA	-> External Interrupt Control Register A
 * EIMSK	-> External Interrupt Mask Register
 * EIFR		-> External Interrupt Flag Register
 * PCICR	-> Pin Change Interrupt Control Register
 * PCIFR	-> Pin Change Interrupt Flag Register
 * PCMSK2	|
 * PCMSK1	|-> Pin Change Mask Register 2,1,0
 * PCMSK0	|
 */



/*
 * Task to do in system.c
 * 
 * 1. Configure the system initial status
 * 2. Allow changes in power configuration (Clock and Power)
 * 3. Configure watchdog (reset when detecting faillures...)
 * 4. Configure initial interrupt vector and interrupt global masks
 */
 
 
 void system_init() {
	 
	 cli();
	 power_all_disable();
	 
 }
