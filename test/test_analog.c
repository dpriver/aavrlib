/*******************************************************************************
 *	test_analog.c
 *
 *  analog test
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
 * PIN_4 -> LED  -> OHM -> GND
 * 5V    -> OHM |-> OHM -> GND
 *              |-> PIN_A0
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "uc/system.h"
#include "uc/usart.h"
#include "uc/analog.h"
#include "systick.h"
#include "boards/arduinoUNO.h"


#define ADC_MASK (0x0)


int main( void ) {
	uint8_t analog_read = 0;
    
	system_init();
    systick_init();
	usart_init(bitrate_115200);
	adc_init(adc_presc_128, adc_ref_vcc, adc_channel_a0, ADC_MASK);
    
    usart_print("====================================================\n");
    usart_print("=  aavrlib analog test                             =\n");
    usart_print("====================================================\n\n");
    usart_print("This test: \n" \
                " - Prints the analog value read from the A0 pin of\n" \
                " the arduino UNO board.\n" \
                " - Switches the pin 4 of the arduino UNO board with \n" \
                " a period of 500ms\n\n");
    
	PIN_CONF_IN(PIN_A0);
	PIN_CONF_OUT(PIN_4);
    PIN_WRITE_HIGH(PIN_4);
    
	while(1) {
		analog_read = adc_single_read();
		usart_print("Readed value: ");
		usart_printnumber8(analog_read);
		usart_print("\n");

		delay_ms(500);
		PIN_SWITCH(PIN_4);
	}
	
	return 0;
}
