/*******************************************************************************
 *	infrared.c
 *
 *  infrared
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


#include <avr/io.h>
#include <avr/interrupt.h>

#include <boards/arduinoUNO.h>
#include <systick.h>
#include "peripherals/infrared.h"

// BUFFER_LENGTH <= 255
#define BUFFER_LENGTH 80

/*
 * IR receive consist in watching for digital pulses in one pin.
 * The duration on the pulses and the time between them is the data carried by 
 * the stream
 */


/*
 * The ISR can receive and buffer the input stream so it can be interpreted in 
 * some other part of the code (It's not a good idea to make it in the ISR)
 */

/*
 * Allow infrared inputs in PD2 and PD3, pins 2 and 3 of arduinoUNO board
 */


// stream buffer
uint16_t stream_buffer[BUFFER_LENGTH];
uint8_t data_length;
uint8_t data_start;
uint8_t data_end;

time_t last_pulse;


void ir_init() {
    data_start = 0;
    data_end = 0;
    data_length = 0;
    
    // set initial time
    get_uptime(&last_pulse);
    
    // configure corresponding pin as input
    
    // enable external interrupts in such pin
    EIMSK |= _BV(INT0);
}


// buffer -> data buffer
// returns the number of positions in buffer
uint8_t ir_get_buffer(uint16_t* buffer) {
    
    buffer = &stream_buffer[data_start];
    
    return data_length;
}

/*
 * Read buffer means advance the "start" pointer
 */
int8_t ir_remove_from_buffer(uint8_t n_positions) {
    
    // if more than the actual data positions are meant to be read, 
    // read the whole buffer instead of interpreting it as an error.
    if (n_positions > data_length) {
        n_positions = data_length;
    }
    
    // stream_buffer is a circular buffer, so if we reach the end of the array,
    // the pointer have to go to the beggining
    // (The simplest way to do this is to use a 256 positions buffer, so the 
    // 8bit position variable overflow will get rid of it.)
    if ((data_start + n_positions) > BUFFER_LENGTH) {
        data_start = (data_start + n_positions) - BUFFER_LENGTH;
    }
    else {
        data_start += n_positions;
    }
    
    data_length -= n_positions;
    
    return n_positions;
}


ISR(INT0_vect, ISR_BLOCK) {
    time_t curr_time, time_interval;
    uint16_t time;
    
    // get current time
    get_uptime(&curr_time);
    
    // compare with last_pulse    
    time_sub(&curr_time, &last_pulse, &time_interval);
    
    last_pulse.ms = curr_time.ms;
    last_pulse.us = curr_time.us;
    
    // (time_interval.ms / 1024) => 2,34% relative error
    time = (time_interval.ms << 10) + time_interval.us;
    
    if ((time < 20000) && (data_length < BUFFER_LENGTH)) {
        stream_buffer[data_end] = time;
        if (data_end == BUFFER_LENGTH-1) {
            data_end = 0;
        }
        else {
            data_end++;
        }
        data_length++;
    }
}
