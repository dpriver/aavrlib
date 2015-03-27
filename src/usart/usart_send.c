#include "usart.h"

void usart_printnumber32(uint32_t number){
	uint8_t digits[10] = {'0','0','0','0','0','0','0','0','0','0'};
	uint8_t index = 9;

	for(; number > 0 ; index--, number/=10)
		digits[index] = (number % 10) + '0';

	for(index = 0 ; index < 10 ; index++)
		usart_send(digits[index]);
}

void usart_printnumber(uint8_t number){
	uint8_t digits[3] = {'0','0','0'};
	uint8_t index = 2;


	for(; number > 0 ; index--, number/=10)
		digits[index] = (number % 10) + '0';

	usart_send(digits[0]);
	usart_send(digits[1]);
	usart_send(digits[2]);
}

void usart_print(char* string){
	while(*string != '\0'){
		usart_send(*string);
		string++;
	}
}

void usart_send(uint8_t data_byte){
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data_byte;
}