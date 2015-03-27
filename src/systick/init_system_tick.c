
#include "systick.h"
#include <avr/interrupt.h>

// Iniciar timer para lanzar una interrupción cada milisegundo
// y la estructura de system_tick
void init_system_tick(){
	// structure initialization
	for(int i = 0; i< MAX_PROCESSES ; i++)
		system_tick.handler[i] = NULL;
	system_tick.current_tick = 0;
	// timer configuration  F_CPU / (prescale*ocr) = freq
	timer1_setup_compA(match_disconected, (uint16_t)1998);
	timer1_en_int_compA();
	timer1_setup_mode_CTC(prescale_8);
}

// No me hace ninguna gracia que todos los procesos asignados a system tick se ejecuten en modo interrupción... Debería hacerla ISR_NOBLOCK, porque tal y como estña, facilmente podría joderse...
ISR(TIMER1_COMPA_vect, ISR_BLOCK){

	system_tick.current_tick++;
	system_tick.tiempoISR = micros();

	for(int i = 0; i< MAX_PROCESSES ; i++){
		if( system_tick.handler[i] && (system_tick.next_handler_tick[i] == system_tick.current_tick) ){
			system_tick.handler[i](i);
			system_tick.next_handler_tick[i] = system_tick.handler_time[i] + system_tick.current_tick;
		}
	}

	system_tick.tiempoISR = micros() - system_tick.tiempoISR; 
}

