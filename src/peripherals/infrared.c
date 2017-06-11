/*******************************************************************************
 *	infrared.c
 *
 *  infrared receiver
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


#include <avr/interrupt.h>
#include "uc/interrupt.h"
#include "systick.h"
#include "peripherals/infrared.h"
//#include "uc/usart.h"




/*==============================================================================
 *   Infrared structures
 *============================================================================*/

struct {
    decode_protocol decode;
    
    uint32_t last_lecture;
} ir_data;


/*==============================================================================
 *   Infrared ISR
 *============================================================================*/

INTERRUPT(__vector_ir_receiver_isr) {
	uint32_t timevalue, intervale;

    // TODO: Disable IR interrupt so it does never get nested
    
    timevalue = get_micros();

    

    if(timevalue > ir_data.last_lecture)
		intervale = timevalue - ir_data.last_lecture;
	else
		intervale = MAX_MICROS_COUNT - ir_data.last_lecture + timevalue;
        
    //time[debug_index] = timevalue;
    //diff[debug_index] = intervale;

    ir_data.decode(intervale);
    ir_data.last_lecture = timevalue;
}



/*==============================================================================
 *   Infrared functions
 *============================================================================*/

void ir_receiver_init(decode_protocol decode){

    //int i;
    //debug_index = 0;
    //for(i = 0 ; i < DEBUG_VALS; i++) {
    //    milis[i] = 0;
    //    micros[i] = 0;
    //    diff[i] = 0;
    //    time[i] = 0;
    //}
    
    ir_data.decode = decode;
    
    ir_data.last_lecture = 0;
    
    interrupt_attach(INT0_int, __vector_ir_receiver_isr);

	EICRA = (EICRA | _BV(ISC01)) & ~_BV(ISC00);
	//EICRA = (EICRA | _BV(ISC00)) & ~_BV(ISC01);
    EIMSK |= _BV(INT0);
    
    // configure pin 2 as input
    DDRD |= _BV(PORTD2);
}
