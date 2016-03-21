#include "systick.h"
#include "delay.h"
#include <avr/interrupt.h>


int main(void)
{
	DDRB = 0xff;
	init_system_tick();
	sei();

	while(1){
		PORTB = 0x1;
		delay_ms(250 );
		delay_ms(250 );
		PORTB = 0x2;
		delay_ms(250 );
		delay_ms(250 );
	}

	return 0;
}
