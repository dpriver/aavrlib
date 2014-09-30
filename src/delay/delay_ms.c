/*====================================================================================================================================
 * Daniel Pinto Rivero	09-08-2014 Cáceres, Spain
 * delay.c 
 * Library with diferent delay implementations
 *=====================================================================================================================================*/

/*
 * This delay function uses system tick
 * Creates a process that is gonna be called each 'ms' miliseconds, and the first time it's called, removes itshelf
 * The delay function iterates while the process remains active
 */

 /*
 * KNOWN BUGS AND ISSUES
 * For the time, only 255ms delays can be made
 */

#include "delay.h"
#include "timer.h"
#include "systick.h"


void delay_handler(uint8_t this_id){
	rem_process(this_id);
}

void delay_ms(uint16_t ms){
	int process_id;

	// agregar el proceso
	process_id = add_process(delay_handler, ms);

	// mientras el proceso siga activo
	while( process_active(process_id) );
}