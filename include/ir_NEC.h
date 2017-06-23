/*******************************************************************************
 *	ir_NEC.h
 *
 *  infrared NEC protocol
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

#ifndef __IR_NEC
#define __IR_NEC

#include <stdint.h>
#include "config.h"


// IR NEC errors
#define IR_NEC_REDUNDANCY_ERROR         (1)
#define IR_NEC_INVALID_PULSE_ERROR      (2)
#define IR_NEC_INVALID_SPACE_ERROR      (3)
#define IR_NEC_INVALID_TAIL_ERROR       (4)

// In NEC "extended" mode, the address width is 16bits
#ifdef IR_NEC_EXTENDED
    typedef void (*ir_nec_completion_handler)(uint16_t address, uint8_t command);
#else
    typedef void (*ir_nec_completion_handler)(uint8_t address, uint8_t command);
#endif

typedef void (*ir_nec_faillure_handler)(uint8_t error, uint32_t data);

void ir_nec_init(ir_nec_completion_handler completion, ir_nec_faillure_handler faillure);
uint8_t ir_nec_decode(uint32_t interval);

#endif /* __IR_NEC */
