/*******************************************************************************
 *	test_infrared.c
 *
 *  infrared NEC protocol test
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

#include <uc/usart.h>
#include <boards/arduinoUNO.h>
#include <systick.h>
#include <peripherals/infrared.h>

uint8_t packet_count;
uint8_t packet_address;
uint8_t packet_command;


void ir_callback(uint16_t address, uint8_t command);

int main( void ) {
    
    uint16_t* ir_buffer = 0; 
    uint8_t buff_length;
    uint8_t i;
    
    systick_init();
    usart_init();
    init_IR_receiver(ir_callback);
    
    while(1) {
        delay_ms(5000);
    }
    
    return 0;
}


void ir_callback(uint16_t address, uint8_t command) {
    usart_print("\nReceived [");
    usart_printnumber8(address);
    usart_print("]: ");
    usart_printnumber8(command);
}
