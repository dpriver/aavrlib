/*******************************************************************************
 *	test_HC-SR04.h
 *
 *  HC-SR04 ultrasonic sensor test
 *
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
 * PIN_6 -> HCSR04.Trig
 * PIN_7 -> HCSR04.Echo
 * 5V    -> HCSR04.Vcc
 * GND   -> HCSR04.Gnd
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include <uc/system.h>
#include <uc/usart.h>
#include <boards/arduinoUNO.h>
#include <peripherals/HCSR04.h>
#include <systick.h>
 
 
 
#define TRIGGER_PIN  PIN_6
#define ECHO_PIN     PIN_7
#define LED_PIN      PIN_4


int main( void ) {

    int16_t distance;

    system_init();
    systick_init();
    usart_init(bitrate_115200);
    ultrasonic_init();

    usart_print("====================================================\n");
    usart_print("=  aavrlib HCSR04 ultrasonic peripheral test       =\n");
    usart_print("====================================================\n\n");
    usart_print("This test: \n" \
                " - Prints the distance from the HCSR04 sensor to the\n" \
                " detected obstacle in cm.\n" \
                " - Prints the peripheral error if any." \
                " - Switches the pin 4 of the arduino UNO board with \n" \
                " a period of 1000ms\n\n");


    PIN_CONF_OUT(TRIGGER_PIN);
    PIN_CONF_IN(ECHO_PIN);
    PIN_CONF_OUT(LED_PIN);
    PIN_WRITE_HIGH(LED_PIN);

    while(1) {
        distance = ultrasonic_measure(PORT(TRIGGER_PIN), REAL_PIN(TRIGGER_PIN), PORT(ECHO_PIN), REAL_PIN(ECHO_PIN));
     
        if (distance >= 0) {
            usart_print("\nDistance: ");
            usart_printnumber32(distance);
            usart_print(" cm");
        }
        else {
            usart_print("\ntimedout... !! [");
            usart_printsignumber32((uint32_t)distance);
            usart_print("]");
        }
        
        delay_ms(1000);
        PIN_SWITCH(LED_PIN);
    }

    return 0;
}
