/*******************************************************************************
 *	lcd_1602a.c
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



#ifndef __LCD_1602A
#define __LCD_1602A

#define LCD_POS_ROW1 (0x0)
#define LCD_POS_ROW2 (0x40)


/* LCD COMMANDS PARAMETERS */
#define LCD_DIR_RIGHT (0x4)
#define LCD_DIR_LEFT  (0x0)

//#define LCD_CGRAM_CHAR_ADDR(c) (c - 'A' + (0x41))


/* LCD COMMANDS */
#define LCD_CLEAR               (0x1)
#define LCD_HOME                (0x2)

#define LCD_CURSOR_MOVE(dir)   (0x10 | (dir))
#define LCD_DISPLAY_SHIFT(dir) (0x18 | (dir))

#define LCD_CGRAM_ADDR(addr)    (0x40 | (addr))
#define LCD_DDRAM_ADDR(addr)    (0x80 | (addr))
#define LCD_READ_STATUS         (0x100)
//#define LCD_WRITE_CHAR(c)       (0x200 | LCD_CGRAM_CHAR_ADDR(c))
#define LCD_WRITE_CHAR(c)       (0x200 | (c))
#define LCD_READ_RAM            (0x300)


void lcd_1602a_init();
void lcd_1602a_command(uint16_t command);
void lcd_1602a_print(char *string, uint8_t position);

#endif /* __LCD_1602A */
