/*******************************************************************************
 *	test_usart.c
 *
 *  System tick test
 *  Print via USART the system uptime each second while switching the led 4 of
 *  the arduinoUNO board.
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

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include <uc/system.h>
#include <uc/usart.h>
#include <boards/arduinoUNO.h>
#include <systick.h>


int main( void ) {
    
    system_init();
    systick_init();
    usart_init(bitrate_115200);
    
 
    IOPORT_CONFIG(OUTPUT, PORT_B, _BV(PIN_4));
    IOPORT_VALUE(LOW,  PORT_B, _BV(PIN_4));
    
    IOPORT_CONFIG(OUTPUT, PORT_B, _BV(PIN_0) | _BV(PIN_1));
    
    
    while(1) {
		usart_print("caracter\n");
		delay_ms(100);
    }
    
    return 0;
}
