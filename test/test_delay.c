/*******************************************************************************
 *	test_systick.c
 *
 *  systick test
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
#include <uc/usart.h>
#include <util/systick.h>


int main( void ) {
    
    uint16_t min;
    uint16_t ms;
    uint16_t us;
    
    uint8_t led_state;
    
    
    systick_init();
    usart_init();
    
    
    IOPORT_CONFIG(OUTPUT, PORT_B, PIN_4);
    IOPORT_VALUE(LOW,  PORT_B_V, PIN_4);
    
    led_state = 0;
    
    while(1) {
        
        if (led_state) {
            IOPORT_VALUE(LOW,  PORT_B_V, PIN_4);
            led_state = 0;
        }
        else {
            IOPORT_VALUE(HIGH, PORT_B_V, PIN_4);
            led_state = 1;
        }
        
        get_uptime(&min, &ms, &us);
        usart_print("\nuptime => min: ");
        usart_printnumber32((uint32_t)min);
        usart_print("  ms: ");
        usart_printnumber32((uint32_t)ms);
        usart_print("  us: ");
        usart_printnumber32((uint32_t)us);
        
        delay_ms(1000);
        
    }
    
    
    return 0;
}
