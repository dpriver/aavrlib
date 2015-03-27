/*
System tick library



*/
#ifndef _SYSTICK
#define _SYSTICK



#include "timer.h"
#include "common.h"

#define MAX_PROCESSES 10
#define MAX_MICROS_COUNT (UINT16_MAX*1000) + 999

typedef void (*process_handler)(uint8_t own_id);

volatile struct{
	uint16_t current_tick;
	uint16_t next_handler_tick[ MAX_PROCESSES ];
	uint16_t handler_time[MAX_PROCESSES];
	process_handler handler[MAX_PROCESSES];
	uint16_t tiempoISR;
}system_tick;

void init_system_tick();
uint32_t micros();
uint8_t add_process(process_handler handler, uint16_t milisecs);
void rem_process(uint8_t identifier);
process_handler process_active(uint8_t process_id);


#endif