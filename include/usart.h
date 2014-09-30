/*=============================================================================
 *
 * USART library header
 *==============================================================================*/

#ifndef _USART
#define _USART

#include "common.h"
#include <stdint.h>

// BAUD = Fose/16/(UBBR0+1)
// setting of baud rate UBRR0=103=0x67 9600 baud rate
// setting of baud rate UBRR0=3=0x03   250k baud rate
// setting the frame format 1bit-stop 8bit-data
// enable transmitter or receiver

#define usart_init() \
	UBRR0H = 0x00; \
	UBRR0L = 0x01; \
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); \
	UCSR0B = _BV(TXEN0);

void usart_send(uint8_t data_byte);
void usart_printnumber(uint8_t number);
void usart_printnumber32(uint32_t number);
void usart_print(char* string);



#endif