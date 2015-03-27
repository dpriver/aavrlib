/*====================================================================================================================================
 * Daniel Pinto Rivero	09-08-2014 Cáceres, Spain
 * ir.h
 * Library with all the functions needed to work with infrared
 *
 * Compilation variables:
 * IR_DEBUG       -> debug compilation
 * IR_FALL_MODE   -> fall-rise signal capture only
 *=====================================================================================================================================*/
#ifndef _IR
#define _IR

#include <stdint.h>
// Configuro Eint0 para reaccionar a un cambio de el sensor de IR (Eint0 está conectado a digital_2)
// Se activa la interrupción mediante "low level", guardando una marca de tiempo y el valor correspondiente



typedef void (*completion_handler)(uint16_t address, uint8_t command);

#ifdef IR_FALL_MODE
enum{IDLE=0x00, START, DATA, COMPLETED};
#else
enum{IDLE, START_D, START_U, DATA_D, DATA_U, COMPLETED};
#endif

#ifdef IR_DEBUG
#define IR_ERROR_NUM_VALUES 40
#endif

volatile struct{
	uint32_t last_lecture_time;
	uint32_t data;
	uint8_t status;
	uint8_t index;
	uint8_t passed_min_time;
	completion_handler command_handler;
}IR_receiver;

#ifdef IR_DEBUG
volatile struct{
	uint32_t vueltas_micro[IR_ERROR_NUM_VALUES];
	uint32_t mili[IR_ERROR_NUM_VALUES];
	uint32_t micro[IR_ERROR_NUM_VALUES];
	uint32_t diff[IR_ERROR_NUM_VALUES];
	uint8_t fails[IR_ERROR_NUM_VALUES];
	uint8_t fails_post[IR_ERROR_NUM_VALUES];
	uint8_t index;
	uint8_t num_fails;
}IR_error;
#endif

void init_IR_receiver(completion_handler handler);

#define IR_set_completion_handler(handler) IR_receive.command_handler = handler;
#define IR_get_data() (uint8_t)(IR_receiver.data >> 8);
#define IR_get_address() (uint16_t)(IR_receiver.data >> 16);
#define IR_data_ready() (IR_receiver.status == COMPLETED);

#endif    // _IR