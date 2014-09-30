#include "lcd.h"


void lcd_byte_write(uint8_t character){
	// write mode
	PORTB |= _BV(PORTB3);

	// primeros 4 bits
	PORTB &= ~_BV(PORTB4);
	PORTD = (PORTD & 0xc3) | (character << 2);
	PORTB |= _BV(PORTB4);

	delay_ms_1(100);

	// siguientes 4 bits
	PORTB &= ~_BV(PORTB4);
	PORTD = (PORTD & 0xc3) | (character >> 2);
	PORTB |= _BV(PORTB4);

	delay_ms_1(100);
}

void lcd_send(uint8_t value, send_type type){
	DIGITAL_PORT_B = (DIGITAL_PORT_B & ~_BV(DIGITAL_11)) | (type << DIGITAL_11);
}