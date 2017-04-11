/*******************************************************************************
 *  HCSR04.c
 *
 *  HC-SR04 ultrasonic sensor
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

#include <stdint.h>
#include <util/delay.h>

#include "peripherals/HCSR04.h"
#include "systick.h"
#include "ioport.h"


void ultrasonic_init() {
        
}


int16_t ultrasonic_measure(ioport_t trig_port, uint8_t trig_pin, 
        ioport_t echo_port, uint8_t echo_pin) {
    
    time_t time1, time2, time_interval;
    //uint16_t time;
    time_t timeout;

    IOPIN_WRITE_HIGH(trig_port, trig_pin);
    _delay_us(13);
    IOPIN_WRITE_LOW(trig_port, trig_pin);

    // wait for echo to be set (timeout is needed)
    start_timeout(1, &timeout);
    //while ( !IOPORT_READ(*echo_port, echo_pin) ) {
    while( !IOPIN_READ(echo_port, echo_pin) ) {
        if (timeout_expired(&timeout)) {
            return -1;
        }
    }
    
    get_uptime(&time1);
    
    // wait for echo to be clear (timeout is needed)
    // the measure range is 2cm to 400cm, 
    // wich corresponds to 116ns to 23200ns
    // For that, a pulse longer than 25ms is likely to be an error
    start_timeout(30, &timeout);
    //while (IOPORT_READ(*echo_port, echo_pin)){
    while( IOPIN_READ(echo_port, echo_pin) ) {
        if (timeout_expired(&timeout)) {
            return -2;
        }
    }
    
    get_uptime(&time2);
    
    time_sub(&time2, &time1, &time_interval);
    
    return (((uint16_t)time_interval.ms << 10) + (uint16_t)time_interval.us) >> 6;
}
