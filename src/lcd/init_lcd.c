#include "lcd.h"

void init_lcd(){
	
	// DB7 DB6 DB5 DB4

	// delay >15ms
	// 0x3 send   function set

	// delay >4.1ms
	// 0x3 send   function set

	// delay >100us
	// 0x3 send   function set

	// 0x2 send   function set (set interface to 4 bits)

	// 0x2 send    function set display lines and caracter font  2lines, 5x8font
	// 0x4 send

	// 0x0 send    display off
	// 0x8 send

	// 0x0 send    display clear
	// 0x1 send

	// 0x0 send    entry mode set cursor moving direction rigth and no shift
	// 0x6 send

	delay_ms(50);
	// puertos digitales 2,3,4,5,11 y 12 como salida
	DIGITAL_CONF_REG_A |= DIGITAL_CONF_2 | DIGITAL_CONF_3 | DIGITAL_CONF_4 | DIGITAL_CONF_5;
	DIGITAL_CONF_REG_B |= DIGITAL_CONF_11 | DIGITAL_CONF_12;

	DIGITAL_PORT_B &= ~_BV(DIGITAL_12) & ~_BV(DIGITAL_11);

	// Set 4bit mode
	lcd_send_4bits(0x03);
	delay_ms(6);
	lcd_send_4bits(0x03);
	delay_ms(6);
	lcd_send_4bits(0x03);
	delay_ms(2);
	lcd_send_4bits(0x02);

	lcd_send(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_1LINE | LCD_2LINE | LCD_5x8DOTS, LCD_COMMAND);

	lcd_send(LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKON, LCD_COMMAND);

	lcd_send(LCD_CLEARDISPLAY, LCD_COMMAND);
  	delay_ms(3);

  	lcd_send(LCD_ENTRYMODESET |  LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT, LCD_COMMAND );


	}