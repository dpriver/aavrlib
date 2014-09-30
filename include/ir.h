/*====================================================================================================================================
 * Daniel Pinto Rivero	09-08-2014 Cáceres, Spain
 * ir.h
 * Library with all the functions needed to work with infrared
 *=====================================================================================================================================*/
#ifndef _IR
#define _IR

#include <stdint.h>
// Configuro Eint0 para reaccionar a un cambio de el sensor de IR (Eint0 está conectado a digital_2)
// Se activa la interrupción mediante "low level", guardando una marca de tiempo y el valor correspondiente


// 
typedef void (*completion_handler)(uint16_t address, uint8_t command);
enum{IDLE=0x00, START, DATA, COMPLETED};

volatile struct{
	uint8_t status;
	uint32_t last_lecture_time;
	uint32_t data;
	uint32_t values[40];
	uint8_t val_index;
	uint8_t index;
	completion_handler command_handler;
}IR_receiver;

void init_IR_receiver(completion_handler handler);

#define IR_set_completion_handler(handler) IR_receive.command_handler = handler;
#define IR_get_data() (uint8_t)(IR_receiver.data >> 8);
#define IR_get_address() (uint16_t)(IR_receiver.data >> 16);
#define IR_data_ready() (IR_receiver.status == COMPLETED);

#endif