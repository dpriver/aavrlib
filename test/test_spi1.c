#include "spi.h"
#include "delay.h"
#include <avr/interrupt.h>


int main(void)
{
	uint8_t caracteres[10] = {0,1,2,3,4,5,6,7,8,9};
	sei();
	DDRB = _BV(DDB0);

	spi_setup_master();
	for(int i = 0; i< 256 ; i++) {
		PORTB |= _BV(PORTB0);
		spi_sendbyte((uint8_t)i);
		delay_ms_1((uint16_t)500);
		PORTB &= ~_BV(PORTB0);
	}

//	PORTB |= _BV(PORTB0);
//	spi_send_block(caracteres, 10);
//	PORTB &= ~_BV(PORTB0);
	return 0;
}