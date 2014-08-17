#include "delay.h"
#include <avr/interrupt.h>


int main(void)
{
	DDRB = 0xff;

	sei();

	while(1){
		PORTB = 0xff;
		delay_ms_1( (uint16_t)1000 );
		PORTB = 0x00;
		delay_ms_1( (uint16_t)1000 );
	}

	return 0;
}