#include "spi.h"
#include "delay.h"
#include <avr/interrupt.h>
#include <util/atomic.h>

uint8_t caracteres[10] = {0,1,2,3,4,5,6,7,8,9};


int main(void)
{
	sei();
	DDRB = _BV(DDB0);


	PORTB |= _BV(PORTB0);
	spi_send_block(caracteres, 10);

	while(1) {
		PORTB |= _BV(PORTB0);
		delay_ms(250);
		PORTB &= ~_BV(PORTB0);
		delay_ms(250);
	}

	return 0;
}