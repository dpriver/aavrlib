/*******************************************************************************
 *	ir_nec.c
 *
 *  infrared NEC protocol
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
 
 
#include <stdint.h>
#include "ir_nec.h"
 
#define DATA_BIT(index) 0x80000000 >> index

#define EQUALS(value, intervale) ( (value >= intervale*0.8) && (value <= intervale*1.2) )
#define NOT_EQUALS(value, intervale) ( (value < intervale*0.8) || (value > intervale*1.2) )
#define PULSE_TIME 562
 
#define PACKET_PULSES  66
#define REPEAT_PULSES 3
 
 
#define ADDR_BEGIN 3
#define ADDR_END ADDR_BEGIN+32

#define DATA_BEGIN ADDR_END+1
#define DATA_END ADDR_END+32
 
#define FRAME_END DATA_END+1

#define FRAME_REPEAT_END 3

 
#define TOKEN_START 9000
#define TOKEN_PACKET 4500
#define TOKEN_REPEAT 2250
#define TOKEN_END PULSE_TIME

#define TOKEN_DATA PULSE_TIME
#define TOKEN_DATA_0 PULSE_TIME
#define TOKEN_DATA_1 PULSE_TIME*3


#define TOKEN_D_REP 9000
#define TOKEN_U_REP 2000
#define MIN_REP_TIME 80000
 
 
#define NEXT_STATUS_IDLE(stat) stat = IDLE;
#define NEXT_STATUS_START_D(stat) stat = START_D;
#define NEXT_STATUS_START_U(stat) stat = START_U;
#define NEXT_STATUS_DATA_D(stat) stat = DATA_D;
#define NEXT_STATUS_DATA_U(stat) stat = DATA_U;
#define NEXT_STATUS_COMPLETED(stat) stat = COMPLETED;
#define SUCCESS()
#define ERROR(cadena)
 
 
int8_t get_packet(uint8_t* raw, ir_nec_packet* packet) {
    int i;

    packet->addr = 0;
    packet->data = 0;
    
    for (i = ADDR_BEGIN ; i < ADDR_END ; i++) {
        if (EQUALS(raw[i], 562) && EQUALS(raw[i+1], 562) &&
            EQUALS(raw[ADDR_END-(i-ADDR_BEGIN)], 562) && 
            EQUALS(raw[ADDR_END-(i+1-ADDR_BEGIN)], 562)) {
            // Addr[i-ADDR_BEGIN] is a 0
        } else if (EQUALS(raw[i], 562) && EQUALS(raw[i+1], 1687) &&
                EQUALS(raw[ADDR_END-(i-ADDR_BEGIN)], 562) && 
                EQUALS(raw[ADDR_END-(i+1-ADDR_BEGIN)], 1687)) {
            // Addr[i-ADDR_BEGIN] is a 1
            packet->addr |= (0x80 >> (i-ADDR_BEGIN));
        } else {
            // Addr is malformed
            return -1;
        }
    }
   
    for (i = DATA_BEGIN ; i < DATA_END ; i++) {
        if (EQUALS(raw[i], 562) && EQUALS(raw[i+1], 562) &&
            EQUALS(raw[DATA_END-(i-DATA_BEGIN)], 562) && 
            EQUALS(raw[DATA_END-(i+1-DATA_BEGIN)], 562)) {
            // Data[i-ADDR_BEGIN] is a 0
        } else if (EQUALS(raw[i], 562) && EQUALS(raw[i+1], 1687) &&
                EQUALS(raw[DATA_END-(i-DATA_BEGIN)], 562) && 
                EQUALS(raw[DATA_END-(i+1-DATA_BEGIN)], 1687)) {
            // Data[i-ADDR_BEGIN] is a 1
            packet->data |= (0x80 >> (i-DATA_BEGIN));
        } else {
            // Data is malformed
            return -1;
        }
    }
    
    return 0;
}
 
 
int8_t translate(uint8_t* raw, uint8_t n_pulses, ir_nec_packet* packet) {
    int ret_value = 0;
    
    // check frame
    if ( (n_pulses == PACKET_PULSES) && EQUALS(raw[0], 9000) && 
        EQUALS(raw[1], 4500) && EQUALS(raw[FRAME_END], 562)) { // packet frame

        packet->repeat = 0;
        ret_value = get_packet(raw, packet);
        
    } else if ( (n_pulses == REPEAT_PULSES) && EQUALS(raw[0], 9000) && 
        EQUALS(raw[1], 2250) && EQUALS(raw[FRAME_END], 562)) { // repeat frame
            
        packet->repeat = 1;
        ret_value = 0;
        
    } else { // Bad frame
        
        ret_value = -1;
        
    }

   return ret_value; 
}

