#include "systick.h"
#include <avr/interrupt.h>

uint32_t micros(){
	return (TCNT1 >> 1) + (system_tick.current_tick * 1000);
}