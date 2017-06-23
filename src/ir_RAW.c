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

#include "ir_RAW.h"


struct {
    uint32_t *buffer;
    uint8_t n;
    uint8_t index;
    
    ir_raw_completion_handler completion;
} ir_RAW_data;


void ir_raw_init(uint32_t *buffer, uint8_t size, ir_raw_completion_handler completion) {
    
    ir_RAW_data.buffer = buffer;
    ir_RAW_data.n = size;
    ir_RAW_data.index = 0;
    ir_RAW_data.completion = completion;
}


uint8_t ir_raw_decode(uint32_t interval) {
    
    ir_RAW_data.buffer[ir_RAW_data.index] = interval;
    ir_RAW_data.index++;

    if (ir_RAW_data.index == ir_RAW_data.n) {
        ir_RAW_data.index = 0;
        ir_RAW_data.completion(ir_RAW_data.buffer, ir_RAW_data.n);
    }

    return 0;
}
