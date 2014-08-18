#include "spi.h"
#include "delay.h"
#include <avr/interrupt.h>
#include <util/atomic.h>

uint8_t caracteres[10] = {0,1,2,3,4,5,6,7,8,9};


void finish(){

	while(1) {
		PORTB |= _BV(PORTB0);
		delay_ms_1((uint16_t)500);
		PORTB &= ~_BV(PORTB0);
		delay_ms_1((uint16_t)500);
	}
}

int main(void)
{
	sei();
	DDRB = _BV(DDB0);


	PORTB |= _BV(PORTB0);
	spi_send_burst(caracteres, 10, finish);

	while(1);

	return 0;
}