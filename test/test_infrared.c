/*******************************************************************************
 *	test_infrared.c
 *
 *  infrared NEC protocol test
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

#include <avr/interrupt.h>
#include <uc/usart.h>
#include <uc/system.h>
#include <boards/arduinoUNO.h>
#include <systick.h>
#include <peripherals/infrared.h>

uint8_t packet_count;
uint8_t packet_address;
uint8_t packet_command;


#define LED_PIN     PIN_4
#define IR_PIN      PIN_2  

void ir_callback(uint8_t address, uint8_t command);

int main( void ) {
    
    system_init();
    systick_init();
    usart_init(bitrate_115200);
    ir_receiver_init(ir_callback, nec_decode);
    
    usart_print("====================================================\n");
    usart_print("=  aavrlib infrared peripheral test                =\n");
    usart_print("====================================================\n\n");
    usart_print("This test: \n" \
                " - Prints the value received from a NEC infrared remote\n" \
                " - Switches the pin 4 of the arduino UNO board with \n" \
                " a period of 1000ms\n\n");
    
    PIN_CONF_OUT(LED_PIN);
    PIN_CONF_IN(IR_PIN);
    PIN_WRITE_HIGH(LED_PIN);
    
    while(1) {
        delay_ms(500);
        PIN_SWITCH(LED_PIN);
    }
    
    return 0;
}


void ir_callback(uint8_t address, uint8_t command) {
    usart_print("\nReceived [");
    usart_printnumber8(address);
    usart_print("]: ");
    usart_printnumber8(command);
}
