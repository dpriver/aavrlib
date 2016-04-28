/*******************************************************************************
 *	test_softPWMlong.h
 *
 *  timers
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
#include <arduino/arduinoUNO.h>
#include <uc/timers.h>
#include <uc/softPWM_long.h>
#include <uc/analog.h>


/*
 * SYSTEM DESCRIPTION
 * 
 * Direction PINS =>
 *      PORT_B -> PIN_2
 *      PORT_B -> PIN_3
 * 
 * PWM PINS =>
 *      PORT_B -> PIN_4
 *      PORT_B -> PIN_5
 *
 * Speed set input =>
 *      PORT_A -> 0
 * 
 */



int main( void ) {
    
    uint8_t analog_read;
    uint8_t direction = 0;
    
    timers_init();
    softPWM_l_init();
    adc_init(adc_presc_8, adc_ref_vcc ,adc_channel_a0, MSK_CH0);
    
    // 2 PWMs are needed in order to handle a dc motor, both directions
    
    
    // config digital outputs to set direction
    IOPORT_CONFIG(OUTPUT, PORT_B, PIN_2);
    IOPORT_CONFIG(OUTPUT, PORT_B, PIN_3);
    
    IOPORT_VALUE(LOW, PORT_B_V, PIN_2);
    IOPORT_VALUE(LOW, PORT_B_V, PIN_3);
    
    // long pulse PWM in pin 4, with duty at 50%
    softPWM_l_add_signal(PIN_4, &PORT_B, &PORT_B_V, 0, 15);
    
    // long pulse PWM in pin 5, with duty at 50%
    softPWM_l_add_signal(PIN_5, &PORT_B, &PORT_B_V, 1, 15);
    
    // start pwm generation
    softPWM_l_start();
    
    
    while(1) {
        
        // get speed input
        analog_read = (31/adc_single_read()) * 512;
        
        // get direction
        direction = 0;
        
        // set motor direction and speed
        if (direction == 0) {
            IOPORT_VALUE(HIGH, PORT_B_V, PIN_2);
            IOPORT_VALUE(LOW, PORT_B_V, PIN_3);
            
            softPWM_l_set_pulse_width(0, analog_read);
        }
        else {
            IOPORT_VALUE(HIGH, PORT_B_V, PIN_3);
            IOPORT_VALUE(LOW, PORT_B_V, PIN_2); 
        
            softPWM_l_set_pulse_width(1, analog_read);
        }
        
    }
    
    return 0;
}
    
