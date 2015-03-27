#include "ir.h"
#include "systick.h"
#include "usart.h"
#include "delay.h"
#include "common.h"
#include <avr/interrupt.h>

enum{ADC0=0x00, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7};

void config_adc(uint8_t port){
	ADMUX = _BV(REFS0) | port;
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	ADCSRB = 0x00;
	DIDR0 = 0x00;
}


uint16_t readAnalog(){
	uint8_t low, high;
	ADCSRA |= _BV(ADSC);
	while( (ADCSRA & _BV(ADSC)) );
	low = ADCL;
	high = ADCH;
	return (uint16_t) ((high << 8) | low);
}


// envío una señal por el puerto conectado al led IR a ~38 KHz
void start_ir_send(){
	// configurar timer a PWM generando un pulso a una frecuencia de 38KHz, es decir, cada
	// 13us debe cambiar
	OCR0A = 180;
	OCR0B = 70;
	TCCR0B = _BV(WGM02) | _BV(CS00);  // prescaler = 1024
	TCCR0A = _BV(COM0B1) | _BV(WGM00);
}

void start_ir_send_2(){
	uint32_t last, current;

	last = 0;
	cli();
	while(TRUE){
		DIGITAL_PORT_A |= _BV(DIGITAL_6);
		delay_us(10);
		DIGITAL_PORT_A &= ~_BV(DIGITAL_6);
		delay_us(10);
		//current = micros();
		//usart_print("\nintervale: ");
		//usart_printnumber(current-last);
		//last = current;
	}
	sei();
}


int main(void){
	init_system_tick();
	usart_init();
	DIGITAL_CONF_REG_A |= _BV(DIGITAL_5);

	config_adc(ADC0);
	start_ir_send();
	/*
	while(TRUE){
		DIGITAL_PORT_A |= _BV(DIGITAL_6);
		delay_us(10);
		DIGITAL_PORT_A &= ~_BV(DIGITAL_6);
		delay_us(10);
		//usart_print("a");
	}
	*/
	for(;;){
		usart_print("\n");
		usart_printnumber32((uint32_t)readAnalog());
		delay_us(200);
	}
}