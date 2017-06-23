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
 * PIN_2 -> IRled.out
 * 5V    -> IRled.Vcc
 * GND   -> IRled.Gnd
 */

#include <avr/interrupt.h>
#include <uc/usart.h>
#include <uc/system.h>
#include <uc/interrupt.h>
#include <boards/arduinoUNO.h>
#include <systick.h>
#include <peripherals/infrared.h>
#include <ir_NEC.h>
#include <ir_RAW.h>
#include <config.h>

uint8_t packet_count;
uint8_t packet_address;
uint8_t packet_command;


#define LED_PIN     PIN_4
#define IR_PIN      PIN_2  

// In IR NEC "extended" mode, the address width is 16bits
// This is defined in config.h
#ifdef IR_NEC_EXTENDED
    #define ADDR_TYPE uint16_t
#else
    #define ADDR_TYPE uint8_t
#endif

void ir_raw_success_callback(uint32_t *buffer, uint8_t n);
void ir_success_callback(ADDR_TYPE address, uint8_t command);
void ir_fail_callback(uint8_t error, uint32_t data);

int main( void ) {
    
    uint32_t ir_buffer[71];
    
    system_init();
    systick_init();
    usart_init(bitrate_9600);
    ir_nec_init(ir_success_callback, ir_fail_callback);
    ir_raw_init(ir_buffer, 71, ir_raw_success_callback);
    ir_receiver_init(ir_raw_decode, CINTVECT(IR_PIN));
    
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
    PIN_ENABLE_CINTERRUPT(IR_PIN);
    
    ENABLE_CINTERRUPTS();
    
    while(1) {
        delay_ms(500);
        PIN_SWITCH(LED_PIN);
    }
    
    return 0;
}


void ir_fail_callback(uint8_t error, uint32_t data) {
    usart_print("\nIR NEC decode faillure: ");
    switch (error) {
        case IR_NEC_INVALID_PULSE_ERROR:
            usart_print("Bad pulse.");
            break;
        case IR_NEC_INVALID_SPACE_ERROR:
            usart_print("Bad space.");
            break;
        case IR_NEC_INVALID_TAIL_ERROR:
            usart_print("Bad tail.");
            break;
        case IR_NEC_REDUNDANCY_ERROR:
            usart_print("Redundancy check error.");
            break;
    }
    
    usart_print("\n raw: ");
    usart_printnumber32( data );
    usart_print("\n redundancy: ");
    usart_printnumber32( ((data >> 8) & (data) & 0x000000FF) );
}

void ir_success_callback(ADDR_TYPE address, uint8_t command) {
    usart_print("\nReceived [");
    usart_printnumber32(address);
    usart_print("]: ");
    usart_printnumber8(command);
}

void ir_raw_success_callback(uint32_t *buffer, uint8_t n) {
    uint8_t i = 0;
    
    usart_print("\n\nReceived: ");
    
    for ( i = 0; i < n ; i++) {
        usart_print("\n - : ");
        usart_printnumber32(buffer[i]);
        ir_nec_decode(buffer[i]);
    }
}
