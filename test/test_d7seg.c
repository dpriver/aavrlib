#include "spi.h"
#include "delay.h"
#include "d7seg.h"
#include <avr/interrupt.h>
#include <util/atomic.h>

uint8_t caracteres[16] = { D7SEG_0,D7SEG_1,D7SEG_2,D7SEG_3,D7SEG_4,D7SEG_5,D7SEG_6,D7SEG_7, \
						   D7SEG_8,D7SEG_9,D7SEG_A,D7SEG_B,D7SEG_C,D7SEG_D,D7SEG_E,D7SEG_F };


int main(void)
{
	sei();
	DDRB = _BV(DDB0);


	PORTB |= _BV(PORTB0);
	spi_send_burst(caracteres, 16, NULL);

	while(1) {
		PORTB |= _BV(PORTB0);
		delay_ms(250);
		PORTB &= ~_BV(PORTB0);
		delay_ms(250);
	}

	return 0;
}