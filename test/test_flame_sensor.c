#include <avr/io.h>
#include "systick.h"
#include "delay.h"
#include "common.h"
#include "usart.h"

enum{ADC0=0x00, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7};

void config_adc(uint8_t port){
	ADMUX = _BV(REFS0) | port;
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	ADCSRB = 0x00;
	DIDR0 = 0x00;
}

void config_temp_sensor(){

}

uint16_t readAnalog(){
	uint8_t low, high;
	ADCSRA |= _BV(ADSC);
	while( (ADCSRA & _BV(ADSC)) );
	low = ADCL;
	high = ADCH;
	return (uint16_t) ((high << 8) | low);
}


int main(void){

	init_system_tick();
	usart_init();

	config_adc(ADC0);

	while(TRUE){
		usart_print("\nSensor value: ");
		usart_printnumber32((uint32_t)readAnalog());
	}

}

