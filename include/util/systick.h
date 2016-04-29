/*******************************************************************************
 *	systick.h
 *
 *  system tick
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


 
#ifndef __SYSTICK
#define __SYSTICK

#include <stdint.h> 



void systick_init();


// 0-999 us
uint16_t get_uptime_us();


// 0-59999 miliseconds
uint16_t get_uptime_ms();


// 0-65535 secods
uint16_t get_uptime_sec();


// complete uptime
void get_uptime(uint16_t sec, uint16_t ms, uint16_t us);

#endif /* __SYSTICK */
