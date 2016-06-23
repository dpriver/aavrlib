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
#include "time.h"


#define MAX_MICROS_COUNT (UINT16_MAX*1000) + 999


void systick_init();



// complete uptime
void get_uptime(time_t *time);

uint32_t get_micros();

void delay_ms(uint16_t ms);


void start_timeout(uint16_t ms, time_t *timeout);

uint8_t timeout_expired(time_t *timeout);

#endif /* __SYSTICK */
