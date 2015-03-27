#include "systick.h"

uint8_t add_process(process_handler handler, uint16_t milisecs){
	uint8_t process_index = 0;

	while( system_tick.handler[process_index] && (process_index < MAX_PROCESSES) ){
		process_index++;
	}

	if(process_index > MAX_PROCESSES){
		return 255;
	}

	system_tick.handler[process_index] = handler;
	system_tick.handler_time[process_index] = milisecs;
	system_tick.next_handler_tick[process_index] = system_tick.current_tick + milisecs;
 
	return process_index;
}