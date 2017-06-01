/*******************************************************************************
 *	test_digital_out.c
 *
 *  digital output test. Using functionality from arduinoUNO.h
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


#include <boards/arduinoUNO.h>
#include <config.h>

#include <uc/system.h>
#include <uc/usart.h>
#include <systick.h>


#define PORT_A_MASK (MPIN_A3 | MPIN_A4 | MPIN_A5)
#define PORT_B_MASK (MPIN_2 | MPIN_3 | MPIN_4 | MPIN_5 | MPIN_6 | MPIN_7)
#define PORT_C_MASK (MPIN_8 | MPIN_9 | MPIN_10 | MPIN_11 | MPIN_12 | MPIN_13)

int main( void ) {
    
    system_init();
    systick_init();
    usart_init(bitrate_9600);
    
    usart_print("====================================================\n");
    usart_print("=  aavrlib digital output test (arduinoUNO.h)      =\n");
    usart_print("====================================================\n\n");
    usart_print("This test: \n" \
                " - Prints a pattern on the digital IO pins.\n\n");
    
    
    // Conf all the used pins as output
    PORT_CONF_OUT(PORT(PIN_A0), PORT_A_MASK);
    PORT_CONF_OUT(PORT(PIN_0), PORT_B_MASK);
    PORT_CONF_OUT(PORT(PIN_8), PORT_C_MASK);
    
    // Write all high
    PORT_WRITE_HIGH(PORT(PIN_A0), PORT_A_MASK);
    PORT_WRITE_HIGH(PORT(PIN_0), PORT_B_MASK);
    PORT_WRITE_HIGH(PORT(PIN_8), PORT_C_MASK);
    
    delay_ms(1000);
    
    // write all low
    PORT_WRITE_LOW(PORT(PIN_A0), PORT_A_MASK);
    PORT_WRITE_LOW(PORT(PIN_0), PORT_B_MASK);
    PORT_WRITE_LOW(PORT(PIN_8), PORT_C_MASK);    
    
    
    delay_ms(1000);
    
    // write high alternatively
    PORT_WRITE_HIGH(PORT(PIN_A0), MPIN_A3 | MPIN_A5);
    PORT_WRITE_HIGH(PORT(PIN_0), MPIN_3 | MPIN_5 | MPIN_7);
    PORT_WRITE_HIGH(PORT(PIN_8), MPIN_10 | MPIN_12);
   
    delay_ms(500);
    PORT_WRITE_HIGH(PORT(PIN_A0), MPIN_A4);
    PORT_WRITE_HIGH(PORT(PIN_0), MPIN_2 | MPIN_4 | MPIN_6);
    PORT_WRITE_HIGH(PORT(PIN_8), MPIN_8 | MPIN_9 | MPIN_11 | MPIN_13);
    
    // write low one by one
    PIN_WRITE_LOW(PIN_2);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_2);
    PIN_WRITE_LOW(PIN_3);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_3);
    PIN_WRITE_LOW(PIN_4);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_4);
    PIN_WRITE_LOW(PIN_5);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_5);
    PIN_WRITE_LOW(PIN_6);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_6);
    PIN_WRITE_LOW(PIN_7);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_7);
    PIN_WRITE_LOW(PIN_8);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_8);
    PIN_WRITE_LOW(PIN_A5);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_A5);
    PIN_WRITE_LOW(PIN_A4);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_A4);
    PIN_WRITE_LOW(PIN_A3);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_A3);
    PIN_WRITE_LOW(PIN_9);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_9);
    PIN_WRITE_LOW(PIN_10);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_10);
    PIN_WRITE_LOW(PIN_11);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_11);
    PIN_WRITE_LOW(PIN_12);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_12);
    PIN_WRITE_LOW(PIN_13);
    delay_ms(300);
    PIN_WRITE_HIGH(PIN_13);
      
    delay_ms(500);
    // write all low
    PORT_WRITE_LOW(PORT(PIN_A0), PORT_A_MASK);
    PORT_WRITE_LOW(PORT(PIN_0), PORT_B_MASK);
    PORT_WRITE_LOW(PORT(PIN_8), PORT_C_MASK); 
      
    PIN_WRITE_HIGH(PIN_2);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_2);
    PIN_WRITE_HIGH(PIN_3);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_3);
    PIN_WRITE_HIGH(PIN_4);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_4);
    PIN_WRITE_HIGH(PIN_5);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_5);
    PIN_WRITE_HIGH(PIN_6);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_6);
    PIN_WRITE_HIGH(PIN_7);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_7);
    PIN_WRITE_HIGH(PIN_8);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_8);
    PIN_WRITE_HIGH(PIN_A5);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_A5);
    PIN_WRITE_HIGH(PIN_A4);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_A4);
    PIN_WRITE_HIGH(PIN_A3);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_A3);
    PIN_WRITE_HIGH(PIN_9);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_9);
    PIN_WRITE_HIGH(PIN_10);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_10);
    PIN_WRITE_HIGH(PIN_11);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_11);
    PIN_WRITE_HIGH(PIN_12);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_12);
    PIN_WRITE_HIGH(PIN_13);
    delay_ms(300);
    PIN_WRITE_LOW(PIN_13);
      
      
      
      
    while(1) {
        delay_ms(500);
        PORT_SWITCH(PORT(PIN_A0), PORT_A_MASK);
        PORT_SWITCH(PORT(PIN_0), PORT_B_MASK);
        PORT_SWITCH(PORT(PIN_8), PORT_C_MASK);
    }
}
