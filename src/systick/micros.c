#include "systick.h"
#include <avr/interrupt.h>

uint32_t micros(){
	return (uint32_t)system_tick.current_tick * 1000 + (TCNT1 >> 1);
}