#include "ir.h"
#include <avr/interrupt.h>



void init_IR_receiver(){
	for(int i ; i < NUM_VALUES; i++)
		IR_receiver.values[i] = 0;

	IR_receiver.status = IDLE;
	IR_receiver.last_lecture_time = 0;
	IR_receiver.index = 0;


	EICRA = 0x00;
	EIMSK = 0x01;
	PCICR = 0x00;
}



ISR(INT0_vect, ISR_BLOCK){
	// obtener tiempo
	uint32_t timevalue, interval;

	timevalue = micros();

	// determinar el significado del intervalo recibido
	// comparando con la última marca de tiempo
	IR_receiver.values[index] = timevalue - IR_receiver.last_lecture_time;
	index++;
}