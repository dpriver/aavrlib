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

// BUFFER_LENGTH <= 255
#define BUFFER_LENGTH 20

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
uint8_t position;

time_t last_pulse;


void ir_init() {
    position = 0;
    
    // set initial time
    get_uptime(&last_pulse);
    
    // configure corresponding pin as input
    
    // enable external interrupts in such pin
    EIMSK |= _BV(INT0);
    
    
}



ISR(INT0_vect, ISR_BLOCK) {
    time_t time;
    
    // get current time
    get_uptime(&curr_time);
    
    
    
    
    // compare with last_pulse    
    substract_time()
    
    
    // if compared value > MAX
        // discart
    
    // save in current stream_buffer position

}
