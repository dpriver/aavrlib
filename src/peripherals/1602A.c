/*******************************************************************************
 *	1602A.c
 *
 *  LCD 1602a peripheral
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


#include <util/delay.h>
#include <avr/io.h>


#include "peripherals/1602A.h"
#include "ioport.h"
#include "config.h"

#include "uc/usart.h"



/*
#define CONFIRM_DATA() \
    E_PORT_V |= _BV(E_PIN); \
    _delay_us(250); \
    E_PORT_V &= ~_BV(E_PIN); \
    _delay_us(250)

#define CLEAR_DATA() \
    DATA_PORT_V &= ~(0xf << DATA_PIN_LOW)
    
#define SET_DATA(value) \
    DATA_PORT_V = (DATA_PORT_V & ~(0xF << DATA_PIN_LOW)) | (value << DATA_PIN_LOW)

#define READ_DATA() \
    (DATA_PORT_V & 0xF)

#define CLEAR_CONTROL() \
    RS_PORT_V &= ~_BV(RS_PIN); \
    RW_PORT_V &= ~_BV(RW_PIN); \
    E_PORT_V  &= ~_BV(E_PIN); \
*/

#define CONFIRM_DATA() \
    IOPIN_WRITE_HIGH(E_PORT, E_PIN); \
    _delay_us(250); \
    IOPIN_WRITE_LOW(E_PORT, E_PIN); \
    _delay_us(250);

#define CLEAR_DATA() \
    IOPORT_WRITE_LOW(DATA_PORT, 0xf << DATA_PIN_LOW)

#define SET_DATA(value) \
    IOPORT_WRITE(DATA_PORT, 0xf << DATA_PIN_LOW, (value) << DATA_PIN_LOW)
    
#define READ_DATA() \
    IOPORT_READ(DATA_PORT, 0xf)
    
#define CLEAR_CONTROL() \
    IOPIN_WRITE_LOW(RS_PORT, RS_PIN); \
    IOPIN_WRITE_LOW(RW_PORT, RW_PIN); \
    IOPIN_WRITE_LOW(E_PORT, E_PIN)


void lcd_1602a_init() {

    // Set pins as output
    IOPIN_CONF_OUT(RS_PORT, RS_PIN);
    IOPIN_CONF_OUT(RW_PORT, RW_PIN);
    IOPIN_CONF_OUT(E_PORT, E_PIN);
    IOPORT_CONF_OUT(DATA_PORT, 0xf << DATA_PIN_LOW);
    IOPORT_WRITE_HIGH(DATA_PORT, 0xf << DATA_PIN_LOW);
    
    usart_print("DATA_PIN_LOW: ");
    usart_printnumber32(DATA_PIN_LOW);
    
    // Set values to 0
    CLEAR_CONTROL();
    CLEAR_DATA();
    
    /* Wait for more than 15ms */
    _delay_ms(20);

    /* Set values RS RW D7 D6 D5 D4 */
    /*            0  0  0  0  1  1  */
    
    SET_DATA(0x3);
    CONFIRM_DATA();
    
    /* Wait for more than 4ms */
    _delay_ms(5);
    CONFIRM_DATA();
    
    /* Wait for more than 100us */
    _delay_ms(1);
    CONFIRM_DATA();
   
   /* Wait more than 4 ms */
   _delay_ms(5);
    // Set 4 bit interface
    /* Set values RS RW D7 D6 D5 D4 */
    /*            0  0  0  0  1  0  */
    SET_DATA(0x2);
    CONFIRM_DATA();


    // Set number of lines and character font
    /* Set values RS RW D7 D6 D5 D4   D7 D6 D5 D4 */
    /*            0  0  0  0  1  0    1  1  0  0  */
    CONFIRM_DATA();

    SET_DATA(0xC);
    CONFIRM_DATA();

    // Display OFF
    /* Set values RS RW D7 D6 D5 D4   D7 D6 D5 D4 */
    /*            0  0  0  0  0  0    1  0  0  0  */
    SET_DATA(0);
    CONFIRM_DATA();

    SET_DATA(0x8);
    CONFIRM_DATA();
    
   
   // clear screen
    /* Set values RS RW D7 D6 D5 D4   D7 D6 D5 D4 */
    /*            0  0  0  0  0  0    0  0  0  1  */
    //D7_PORT_V &= ~D7_PIN;
    SET_DATA(0);
    CONFIRM_DATA();

    //D4_PORT_V |= D4_PIN;
    SET_DATA(0x1);
    CONFIRM_DATA();
    
   _delay_ms(2);
   
   // mode set
    /* Set values RS RW D7 D6 D5 D4   D7 D6 D5 D4 */
    /*            0  0  0  0  0  0    0  1  1  0  */
    //D4_PORT_V &= ~D4_PIN;
    SET_DATA(0);
    CONFIRM_DATA();

    //D5_PORT_V |= D5_PIN;
    SET_DATA(0x6);
    CONFIRM_DATA();
    
   
   // display ON
    /* Set values RS RW D7 D6 D5 D4   D7 D6 D5 D4 */
    /*            0  0  0  0  0  0    1  1  0  1  */
    //D5_PORT_V &= ~D5_PIN;
    SET_DATA(0);
    CONFIRM_DATA();

    //D7_PORT_V |= D7_PIN;
    //D6_PORT_V |= D6_PIN;
    //D4_PORT_V |= D4_PIN;
    SET_DATA(0xD);
    CONFIRM_DATA();
    
    //D7_PORT_V &= ~D7_PIN;
    //D6_PORT_V &= ~D6_PIN;
    //D4_PORT_V &= ~D4_PIN;
    CLEAR_DATA();
}



void lcd_1602a_print(char *string, uint8_t position) {
    int i = 0;
    
    LCD_1602A_SET_TARGET_DISP_MEM(position);
    while (string[i] != '\0') {
        LCD_1602A_WRITE_CHAR(string[i]);
        i++;
    }
    
}


uint8_t lcd_1602a_command(uint16_t command) {

    uint8_t data;
    CLEAR_DATA();
    CLEAR_CONTROL();
    
    usart_print("\nlcd command: ");
    usart_printnumber32(command);
    
    /* This have to be changed....
     */
    if (command & RS_COMM_MASK) { //RS Data input
        IOPIN_WRITE_HIGH(RS_PORT, RS_PIN);
    }

    if (command & RW_COMM_MASK) { //RW Read operation
        IOPIN_WRITE_HIGH(RW_PORT, RW_PIN);
        
#warning "[TODO] 1602a lcd command: read operation not implemented"
        IOPIN_WRITE_HIGH(E_PORT, E_PIN);
        _delay_us(250);
        // read value
        data = READ_DATA() << 4;
        IOPIN_WRITE_LOW(E_PORT, E_PIN);
        _delay_us(250);
        
        IOPIN_WRITE_HIGH(E_PORT, E_PIN);
        _delay_us(250);
        // read value
        data |= READ_DATA();
        IOPIN_WRITE_LOW(E_PORT, E_PIN);
        _delay_us(250);
        
        return data;
        
    } 
    else { // Write operation
    
        //if (command & D7_COMM_MASK) { //D7
            //D7_PORT_V |= D7_PIN;
        //}
        //if (command & D6_COMM_MASK) { //D6
            //D6_PORT_V |= D6_PIN;
        //}
        //if (command & D5_COMM_MASK) { //D5
            //D5_PORT_V |= D5_PIN;
        //}
        //if (command & D4_COMM_MASK) { //D4
            //D4_PORT_V |= D4_PIN;
        //}
        SET_DATA((command >> 4) & 0xF);
        CONFIRM_DATA();

        //if (command & D3_COMM_MASK) { //D3
            //D7_PORT_V |= D7_PIN;
        //}
        //if (command & D2_COMM_MASK) { //D2
            //D6_PORT_V |= D6_PIN;
        //}
        //if (command & D1_COMM_MASK) { //D1
            //D5_PORT_V |= D5_PIN;
        //}
        //if (command & D0_COMM_MASK) { //D0
            //D4_PORT_V |= D4_PIN;
        //}
        SET_DATA(command & 0xF);
        CONFIRM_DATA();
        
        return 0;
    }
}
