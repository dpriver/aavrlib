/*******************************************************************************
 *	test_lcd_1602A.h
 *
 *  1602A LCD peripheral test
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

#include <util/delay.h>

#include <uc/system.h>
#include <uc/usart.h>
#include <boards/arduinoUNO.h>
#include <peripherals/1602A.h>
#include <systick.h>
#include <config.h>


#define PIN_LED PIN_7



#define CONFIRM_DATA() \
    IOPIN_WRITE_HIGH(E_PORT, E_PIN); \
    _delay_us(250); \
    IOPIN_WRITE_LOW(E_PORT, E_PIN); \
    _delay_us(250);

#define CLEAR_DATA() \
    IOPORT_WRITE_LOW(DATA_PORT, 0xf << DATA_PIN_LOW)

#define SET_DATA(value) \
    IOPORT_WRITE(DATA_PORT, 0xf << DATA_PIN_LOW, value << DATA_PIN_LOW)
    
#define READ_DATA() \
    IOPORT_READ(DATA_PORT, 0xf)
    
#define CLEAR_CONTROL() \
    IOPIN_WRITE_LOW(RS_PORT, RS_PIN); \
    IOPIN_WRITE_LOW(RW_PORT, RW_PIN); \
    IOPIN_WRITE_LOW(E_PORT, E_PIN)
    


int main ( void ) {
  
    system_init();
    systick_init();
    usart_init(bitrate_9600);
    lcd_1602a_init();
    
    usart_print("====================================================\n");
    usart_print("=  aavrlib 1602A LCD peripheral test               =\n");
    usart_print("====================================================\n\n");
    usart_print("This test: \n" \
                " - Prints a text to the 1602A LCD peripheral\n" \
                " - Switches the pin 4 of the arduino UNO board with \n" \
                " a period of 1000ms\n\n");
            
    
    delay_ms(40);
    PIN_CONF_OUT(PIN_LED);
    PIN_WRITE_HIGH(PIN_LED);

    lcd_1602a_print("Hello World ", LCD_ROW1_POS(3));

    delay_ms(3000);
    usart_print("Print 'Works!!' to LCD\n");
    lcd_1602a_print("    Works!!", LCD_ROW2_POS(0));
    
    while(1) {
        delay_ms(500);
        PIN_SWITCH(PIN_LED);
    }
    


   return 0; 
}
