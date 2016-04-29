/*******************************************************************************
 *	delay.h
 *
 *  Delays
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

/* with F_CPU = 16000000, it runs 16000 instructions per ms, so a first approach
 * is a ~16000/3 instructions loop.
 * the previous 3 is arbitrary, kind of an estimation of the num of instruccions
 * needed in order to run a loop
 */

#ifndef __DELAY
#define __DELAY

#include <stdint.h>


void delay_ms(uint16_t ms);


#endif /* __DELAY */
