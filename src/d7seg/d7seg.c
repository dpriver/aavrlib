#include "d7seg.h"
#include "spi.h"
#include "systick.h"


// Estructura para mantener la información a mostrar
volatile static struct{
	uint8_t character_buff[4];
	uint8_t last_sync_char;
	uint8_t curr_sync_char;
}d7seg_display = { {D7SEG_NULL,D7SEG_NULL,D7SEG_NULL,D7SEG_NULL},
			 	  0,
			 	  0
			 	};

void advance_char(){
	d7seg_display.last_sync_char = d7seg_display.curr_sync_char;
	if(d7seg_display.curr_sync_char < 3)
		d7seg_display.curr_sync_char++;
	else
		d7seg_display.curr_sync_char = 0;
}

void display_handler(uint8_t this_id){
	// enviar por puerto serie el siguiente valor
	uint8_t ant_sel_bit, curr_sel_bit, caracter;

	caracter = d7seg_display.character_buff[d7seg_display.curr_sync_char];
	spi_send_block( &caracter, 1);

	ant_sel_bit = 4 + d7seg_display.last_sync_char;
	curr_sel_bit = 4 + d7seg_display.curr_sync_char;
	PORTD &= ~_BV(ant_sel_bit);  //anterior display a 0
	PORTD |= _BV(curr_sel_bit);   // siguiente display a 1
	advance_char();
}

void d7seg_init(fps_rate fps){
	// "display enable" output ports
	DDRD |= _BV(DDD4) | _BV(DDD5) | _BV(DDD6) | _BV(DDD7);
	add_process(display_handler, 4);
}

// funcion para modificar la informacion a mostrar
void d7seg_print(uint8_t value[4]){
	d7seg_display.character_buff[0] = value[0]; 
	d7seg_display.character_buff[1] = value[1];
	d7seg_display.character_buff[2] = value[2];
	d7seg_display.character_buff[3] = value[3];
}