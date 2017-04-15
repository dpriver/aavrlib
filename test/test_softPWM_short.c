/*******************************************************************************
 *  test_softPWM_short.c
 *
 *  Short pulse software generated PWM test
 *  Send a software based PWN signal to the pin 4 of the arduinoUNO board. The 
 *  pulse width comes determined for the analog value readed from the board's 
 *  a0 pin. Each 300ms, the readed and the assigned values are showed via USART.
 *
 *  This file is part of aavrlib
 *
 *  Copyright (C) 2015  Dennis Pinto Rivero
 *  Copyright (C) 2016  Germán Castaño Roldán
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

/*
 * Physical configuration:
 * BOARD: Arduino UNO (atmega328p)
 * 
 * PIN_4 -> LED -> OHM -> GND
 * PIN_5 -> servo.control (yellow)
 * 5V    -> servo.gcc     (orange)
 * GND   -> servo.gnd     (brown)
 */

#include <avr/io.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include <uc/system.h>
#include <uc/usart.h>
#include <uc/analog.h>
#include <boards/arduinoUNO.h>
#include <systick.h>
#include <softPWM_short.h>


// Pins
#define LED_PIN   PIN_4
#define PWM_PIN   PIN_5

#define FREQ_CNT    (20)
#define DUTY_HALF   (FREQ_CNT/2)



int main( void ) {
    
    uint8_t duty_count = 30;
    uint8_t direction = 1;

    system_init();
    systick_init();
    usart_init(bitrate_115200);
    softPWM_s_init();

    usart_print("====================================================\n");
    usart_print("=  aavrlib software based short PWM test           =\n");
    usart_print("====================================================\n\n");
    usart_print("This test: \n" \
                " - Generates a software based PWM signal on pin 5 with\n" \
                " a changing duty cycle to control a servo motor.\n" \
                " - Prints the current duty cycle value\n" \
                " - Switches the pin 4 of the arduino UNO board with \n" \
                " a period of 600ms\n\n");
    
    PIN_CONF_OUT(LED_PIN);
    PIN_CONF_OUT(PWM_PIN);
    PIN_WRITE_HIGH(LED_PIN);
    
    softPWM_s_add_signal(PORT(PWM_PIN), REAL_PIN(PWM_PIN), 0, 0);
    
	while(1) {
        
        duty_count = (direction)? duty_count+1: duty_count-1;
        if ((duty_count == 120) || (duty_count == 30)) {
            direction = !direction;
        }
    
		usart_print("Assigned value: ");
        usart_printnumber8(duty_count);
        usart_print("\n");
        
        softPWM_s_set_pulse_width(0, duty_count);
        
        delay_ms(300);
        PIN_SWITCH(LED_PIN);
    }
	
	return 0;
}
