
#include "arduino/arduinoUNO.h"
#include "uc/usart.h"
#include "uc/timers.h"
#include "uc/analog.h"
#include <avr/interrupt.h>
#include <stdint.h>

#define ADC_MASK (0x0)


void delay();

int main( void ) {
	uint8_t analog_read = 0;
	timers_init();
	usart_init();
	adc_init(adc_presc_128, adc_ref_vcc, adc_channel_a0, ADC_MASK);
	//timer1_systick_init();
	//sei();
	
	IOPORT_CONFIG(INPUT, PORT_A, PIN_A0);
	IOPORT_CONFIG(OUTPUT, PORT_B, PIN_7);
	
	
	//DDRD |= (1 << DDD7);
	//PORTD |= (1 << PORTD7);

	while(1) {
		IOPORT_VALUE(HIGH, PORT_B_V, PIN_7);
		analog_read = adc_single_read();
		usart_print("Readed value: ");
		usart_printnumber8(analog_read);
		usart_print("\n");

		delay(1);
		IOPORT_VALUE(LOW, PORT_B_V, PIN_7);
		delay(1);
	}
	
	while(1);
	return 0;
}


// bad delay... only for this test
void delay(uint16_t ms) {
	//uint16_t t;
	uint16_t i, j;
	
	for(i = 0 ; i < 100 ; i++){
		for(j = 0 ; j < 6000 ; j++) {
			//for(k = 0 ; k < 99999 ; k++);
		}
	}
	//t = get_uptime_sec() + ms;
	
	//while(get_uptime_sec() != t);
}

