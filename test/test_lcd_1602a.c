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



#define PIN_LED PIN_7


int main ( void ) {
  
    system_init();
    systick_init();
    usart_init(bitrate_115200);
    lcd_1602a_init();
    
    usart_print("====================================================\n");
    usart_print("=  aavrlib 1602A LCD peripheral test               =\n");
    usart_print("====================================================\n\n");
    usart_print("This test: \n" \
                " - Prints a text to the 1602A LCD peripheral\n" \
                " - Switches the pin 4 of the arduino UNO board with \n" \
                " a period of 1000ms\n\n");
                
    PIN_CONF_OUT(PIN_LED);
    PIN_WRITE_HIGH(PIN_LED);
 
    //usart_print("Print 'Hello World' to LCD\n");
    lcd_1602a_print("a", LCD_ROW1_POS(0));
    //lcd_1602a_print("  Hello World ", LCD_ROW1_POS(0));
    delay_ms(3000);
    //usart_print("Print 'Works!!' to LCD\n");
    //lcd_1602a_print("    Works!!", LCD_ROW2_POS(0));
    
    while(1) {
        delay_ms(500);
        PIN_SWITCH(PIN_LED);
    }
    


   return 0; 
}
