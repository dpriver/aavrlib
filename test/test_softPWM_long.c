/*******************************************************************************
 *  test_softPWMlong.h
 *
 *  long pulse software PWM test
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
#include <util/softPWM_long.h>
#include <uc/analog.h>
#include <uc/usart.h>


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


void delay();

int main( void ) {
    
    uint8_t analog_read, pulse_width;
    //uint8_t direction = 0;
    
    timers_init();
    usart_init();
    softPWM_l_init();
    adc_init(adc_presc_128, adc_ref_vcc ,adc_channel_a0, 0);
    
    // 2 PWMs are needed in order to handle a dc motor, both directions
    
    sei();
    
    // set pin13 as output to low value so teh led "LED" is off
    IOPORT_CONFIG(OUTPUT, PORT_C, PIN_13);
    IOPORT_VALUE(LOW, PORT_C_V, PIN_13);
    
    // config digital outputs to set direction
    IOPORT_CONFIG(OUTPUT, PORT_B, PIN_2);
    IOPORT_CONFIG(OUTPUT, PORT_B, PIN_3);
    
    IOPORT_VALUE(HIGH, PORT_B_V, PIN_2);
    IOPORT_VALUE(LOW, PORT_B_V, PIN_3);
    
    // start pwm generation
    softPWM_l_start();
    
    
    // long pulse PWM in pin 4, with duty at 50%
    if (softPWM_l_add_signal(PIN_4, &PORT_B, &PORT_B_V, 0, 15) == -1) {
        usart_print("\n\nError, could not add PWM signal\n");
        return 0;
    }
    
    // long pulse PWM in pin 5, with duty at 50%
    //softPWM_l_add_signal(PIN_5, &PORT_B, &PORT_B_V, 1, 15);
    
    
    
    while(1) {
        
        // get speed input
        analog_read = adc_single_read();
        pulse_width = (77./255) * analog_read;
        
        
        usart_print("\nAnalog read: ");
        usart_printnumber8(analog_read);
        
        usart_print("\t\tpulse width: ");
        usart_printnumber8(pulse_width);
       

        if (softPWM_l_set_pulse_width(0, pulse_width) == -1) {
            usart_print("\n\nError, could not add PWM signal\n");
            return 0;
        }
        
        
        // get direction
        //direction = 0;
        
        // set motor direction and speed
        /*
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
        */
        delay();
    }
    
    return 0;
}
    


void delay() {
	//uint16_t t;
	uint16_t i, j;
	
	for(i = 0 ; i < 100 ; i++){
		for(j = 0 ; j < 6000 ; j++) {
			//for(k = 0 ; k < 99999 ; k++);
		}
	}
	//t = get_uptime_sec() + ms;
	
	//while(get_uptime_sec() != t);
}
