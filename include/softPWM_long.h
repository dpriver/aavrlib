/*******************************************************************************
 *	softPWM_long.h
 *
 *  softPWM_long
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

#ifndef __SOFTPWM_LONG
#define __SOFTPWM_LONG


#include <stdint.h>


void softPWM_l_init();

int8_t softPWM_l_add_signal(uint8_t pin, volatile uint8_t *config_port, 
    volatile uint8_t *data_port, uint8_t slot, uint8_t pulse_width);

int8_t softPWM_l_stop_signal(uint8_t slot);

int8_t softPWM_l_set_pulse_width(uint8_t slot, uint8_t pulse_width);

void softPWM_l_start();

void softPWM_l_stop();


#endif /* __SOFTPWM_LONG */
