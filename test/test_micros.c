/*******************************************************************************
 *  test_micros.c
 *
 *  test for the microsecond timing functionality
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
 *******************************************************************************/
 
 
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

//#include "boards/arduinoUNO.h"
#include "uc/system.h"
#include "uc/usart.h"
#include "systick.h"
#include "ioport.h"

int main(void){

    int32_t micros_ini, micros_end, micros_diff = 0;
    //int32_t micros_diff_prev = 0;

    system_init();
    usart_init(bitrate_115200);
    systick_init();

    //sart_print("beginning test...");
    //usart_print("\n");

    IOPIN_CONF_OUT(IOPORT_D, 4);
    IOPIN_WRITE_LOW(IOPORT_D, 4);

    while(1) {

        //micros_ini = get_micros();
        //micros_end = get_micros(),
        //micros_diff = micros_end - micros_ini;
        
        //usart_print("\n: ");
        //usart_printsignumber32(micros_diff);
        
        micros_ini = get_micros();
        //micros_diff_prev = 0;
        do {
            micros_end = get_micros();
            micros_diff = micros_end - micros_ini;
            
            //usart_print("\n: ");
            //usart_printnumber32(micros_end);
            //usart_print(" - ");
            //usart_printnumber32(micros_ini);
            //usart_print(" = ");
            //usart_printnumber32(micros_diff);
            //usart_print(" ----> ");
            //usart_printsignumber32(micros_diff - micros_diff_prev);
            
            //micros_diff_prev = micros_diff;
        } while (micros_diff < 1000000);
    
    
        
        IOPIN_SWITCH(IOPORT_D, 4);
    }
  
    while(1);
  
    return 0;
}
