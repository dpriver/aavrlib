#include "lcd.h"

void lcd_send(uint8_t value, send_type type){

	// data write or command send mode
	DIGITAL_PORT_B = (DIGITAL_PORT_B & ~_BV(DIGITAL_12)) | (type << DIGITAL_12);


	// primeros 4 bits
	DIGITAL_PORT_A = (DIGITAL_PORT_A & 0xc3) | (value >> 2);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_11);
	delay_us(1);
	DIGITAL_PORT_B |= _BV(DIGITAL_11);
	delay_us(1);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_11);
	delay_us(100);

	// siguientes 4 bits
	DIGITAL_PORT_A = (DIGITAL_PORT_A & 0xc3) | (value << 2);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_11);
	delay_us(1);
	DIGITAL_PORT_B |= _BV(DIGITAL_11);
	delay_us(1);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_11);
	delay_us(100);
}

void lcd_send_4bits(uint8_t value){
	DIGITAL_PORT_A = (DIGITAL_PORT_A & 0xc3) | (value << 2);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_11);
	delay_us(1);
	DIGITAL_PORT_B |= _BV(DIGITAL_11);
	delay_us(1);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_11);
	delay_us(100);
}