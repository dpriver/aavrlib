/*******************************************************************************
 *	test_systick.c
 *
 *  System tick test
 *  Print via USART the system uptime each half second while switching 
 *  the led 4 of the arduinoUNO board.
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
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include <uc/system.h>
#include <uc/usart.h>
#include <boards/arduinoUNO.h>
#include <systick.h>


int main( void ) {
    
    time_t time, time_prev;
    
    system_init();
    usart_init(bitrate_115200);
    systick_init();
    
    usart_print("====================================================\n");
    usart_print("=  aavrlib systick test                            =\n");
    usart_print("====================================================\n\n");
    usart_print("This test: \n" \
                " - Prints the system uptime each half second and the\n" \
                " difference in ms with respect to the last reading,\n" \
                " which should be a bit more than 500ms\n" \
                " - Switches the pin 4 of the arduino UNO board\n\n");
    
    delay_ms(2000);
    PIN_CONF_OUT(PIN_4);
    PIN_WRITE_LOW(PIN_4);
    time.ms = 0;
    time.us = 0;
    time_prev.ms = 0;
    time_prev.us = 0;
    
    while(1) {
        
        delay_ms(500);
        PIN_SWITCH(PIN_4);
        
        time_copy(&time, &time_prev);
        get_uptime(&time);
        usart_print("\nuptime => ms: ");
        usart_printnumber32((uint32_t)time.ms);
        usart_print("  us: ");
        usart_printnumber32((uint32_t)time.us);
        usart_print("  diff: ");
        usart_printsignumber32((uint32_t)(time.ms - time_prev.ms));
    }
    
    return 0;
}
