#include "systick.h"

void rem_process(uint8_t identifier){
	system_tick.handler[identifier] = NULL;
}