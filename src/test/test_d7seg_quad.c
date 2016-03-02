#include "d7seg.h"
#include "spi.h"
#include "delay.h"
#include "systick.h"
#include <avr/interrupt.h>
#include <avr/io.h>


void buff_add(uint8_t cola[4], uint8_t valor){
	cola[0] = cola[1];
	cola[1] = cola[2];
	cola[2] = cola[3];
	cola[3] = valor;
}


int main(void){
	uint8_t texto[4] = {D7SEG_NULL, D7SEG_NULL, D7SEG_NULL, D7SEG_NULL};

	sei();
	DDRD |= _BV(DDD2);
	//PORTD |= _BV(PORTD4) | _BV(PORTD5) | _BV(PORTD6) | _BV(PORTD7);

	init_system_tick();
	d7seg_init(fps_60);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_0);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_1);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_2);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_3);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_4);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_5);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_6);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_7);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_8);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_9);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_A);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_B);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_C);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_D);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_E);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_F);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_NULL);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_NULL);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_NULL);
	d7seg_print(texto);
	delay_ms(150);

	buff_add(texto,D7SEG_NULL);
	d7seg_print(texto);
	delay_ms(150);

	while(1) {
		PORTD |= _BV(PORTD2);
		delay_ms(250);
		PORTD &= ~_BV(PORTD2);
		delay_ms(250);
	};
	
	PORTD |= _BV(PORTD2);
	return 0;
}