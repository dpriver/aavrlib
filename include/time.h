/*******************************************************************************
 *	time.h
 *
 *  Time related definitions and functions
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

#ifndef __TIME
#define __TIME

#include <stdint.h>

typedef struct {
    uint16_t us;
    uint32_t ms;
} time_t;

// the 16 and 32 bit registers used in time_t makes this an ineficient calculation
int8_t time_add(time_t *op1, time_t *op2, time_t *result);
int8_t time_sub(time_t *op1, time_t *op2, time_t *result);


#endif /* __TIME */
