// returns NULL if process doesn't exist and the handler direction if it does
#include "systick.h"


process_handler process_active(uint8_t process_id){
	if(process_id >= MAX_PROCESSES){
		return NULL;
	}
	else{
		return system_tick.handler[process_id];
	}
}