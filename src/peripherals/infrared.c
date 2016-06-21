/*******************************************************************************
 *	infrared.c
 *
 *  infrared receiver
 *
 *
 *  This file is part of aavrlib
 * 
 *  Copyright (C) 2015  Dennis Pinto Rivero
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/


#include <avr/interrupt.h>
#include "uc/interrupt.h"
#include "systick.h"
#include "peripherals/infrared.h"

#define IR_DEBUG

#ifdef IR_DEBUG
#include "uc/usart.h"
#endif

#define TRUE 1
#define FALSE 0
#define NULL 0

#ifdef IR_DEBUG
#define IR_ERROR_NUM_VALUES 40
#endif

#define DATA_BIT(index) 0x80000000 >> index
#define EQUALS(value, intervale) ( (value >= intervale*0.5) && (value <= intervale*1.5) )

#define PULSE_TIME 562

#define TOKEN_D_START 9000
#define TOKEN_U_START 4500
#define TOKEN_D_DATA PULSE_TIME
#define TOKEN_U_0 PULSE_TIME
#define TOKEN_U_1 PULSE_TIME*3
#define TOKEN_D_REP 9000
#define TOKEN_U_REP 2000
#define MIN_REP_TIME 80000


#ifdef IR_DEBUG 
    #define NEXT_STATUS_IDLE() IR_receiver.status = IDLE;
    #define NEXT_STATUS_START_D() IR_receiver.status = START_D;
    #define NEXT_STATUS_START_U() IR_receiver.status = START_U;
    #define NEXT_STATUS_DATA_D() IR_receiver.status = DATA_D;
    #define NEXT_STATUS_DATA_U() IR_receiver.status = DATA_U;
    #define NEXT_STATUS_COMPLETED() IR_receiver.status = COMPLETED;
    #define SUCCESS() dump_lecture();
    #define ERROR(cadena) \
            usart_print("\nERROR: "); \
            usart_print(cadena); \
            dump_lecture();
#else
    #define NEXT_STATUS_IDLE() IR_receiver.status = IDLE;
    #define NEXT_STATUS_START_D() IR_receiver.status = START_D;
    #define NEXT_STATUS_START_U() IR_receiver.status = START_U;
    #define NEXT_STATUS_DATA_D() IR_receiver.status = DATA_D;
    #define NEXT_STATUS_DATA_U() IR_receiver.status = DATA_U;
    #define NEXT_STATUS_COMPLETED() IR_receiver.status = COMPLETED;
    #define SUCCESS()   usart_print("\n[Recibido]");
    #define ERROR(cadena) usart_print(cadena);
#endif

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

enum{IDLE, START_D, START_U, DATA_D, DATA_U, COMPLETED};

volatile struct{
	uint32_t last_lecture_time;
	uint32_t data;
	uint8_t status;
	uint8_t index;
	uint8_t passed_min_time;
	completion_handler command_handler;
}IR_receiver;





#ifdef IR_DEBUG
// ============================ DEBUG ====================================
// =======================================================================

void ir_error_initialize(){
	cli();
	for(uint8_t i = 0; i < IR_ERROR_NUM_VALUES ; i++){
		IR_error.vueltas_micro[i] = 0;
		IR_error.micro[i] = 0;
		IR_error.mili[i] = 0;
		IR_error.diff[i] = 0;
		IR_error.fails[i] = FALSE;
		IR_error.fails_post[i] = FALSE;
	}
	IR_error.num_fails = 0;
	IR_error.index = 0;
	sei();
}

void print_status(uint8_t status){
	switch(status){
		case IDLE:
			usart_print("IDLE");
			break;
		case START_D:
			usart_print("START_D");
			break;
		case START_U:
			usart_print("START_U");
			break;
		case DATA_D:
			usart_print("DATA_D");
			break;
		case DATA_U:
			usart_print("DATA_U");
			break;
		case COMPLETED:
			usart_print("COMPLETED");
			break;
	}
}

void print_data(){

	for(int i = 0 ; i < 16 ; i++){
		if(IR_receiver.data & DATA_BIT(i) )
			usart_print("1");
		else
			usart_print("0");
	}
	usart_print(" ");
	for(int i = 16 ; i < 24 ; i++){
		if(IR_receiver.data & DATA_BIT(i) )
			usart_print("1");
		else
			usart_print("0");
	}
	usart_print(" ");
	for(int i = 24 ; i < 32 ; i++){
		if(IR_receiver.data & DATA_BIT(i) )
			usart_print("1");
		else
			usart_print("0");
	}
}

void dump_lecture(){
	usart_print("\n========== DUMP ============");
	usart_print("\nSTATUS: ");
	print_status(IR_receiver.status);
	usart_print("\nDATA  : ");
	print_data();
	usart_print("\nposition    micro      mili       ciclos_us      dif");
	for(uint32_t i = 0; i < IR_ERROR_NUM_VALUES ; i++){
		usart_print("\n");
		usart_printnumber32(i);
		usart_print(": ");
		usart_printnumber32(IR_error.micro[i]);
		usart_print(" ");
		usart_printnumber32(IR_error.mili[i]);
		usart_print(" ");
		usart_printnumber32(IR_error.vueltas_micro[i]);
		usart_print(" --> [");
		usart_printnumber32(IR_error.diff[i]);
		usart_print("]");
		if(IR_error.fails[i])
			usart_print("  FAIL");
		if(IR_error.fails_post[i])
			usart_print("  FAIL_POST");
	}
	usart_print("\nNUM. FAILS: ");
	usart_printnumber32(IR_error.num_fails);
	//usart_print("\nTiempo ISR: ");
	//usart_printnumber32((uint32_t)system_tick.tiempoISR);
	usart_print("\n============================");
}

// =======================================================================
// =======================================================================
#endif



void nec_protocol_isr(interrupt_t interrupt) {
	// obtener tiempo
	uint32_t timevalue, intervale;


	timevalue = get_micros();

	// determinar el significado del intervalo recibido
	// comparando con la última marca de tiempo
	if(timevalue > IR_receiver.last_lecture_time)
		intervale = timevalue - IR_receiver.last_lecture_time;
	else
		intervale = MAX_MICROS_COUNT - IR_receiver.last_lecture_time + timevalue;

	if(IR_receiver.passed_min_time)
		IR_receiver.last_lecture_time = timevalue;

#ifdef IR_DEBUG
    usart_print("\nintervale: ");
    usart_printnumber32(intervale);

	IR_error.diff[IR_error.index] = intervale;
#endif

	switch(IR_receiver.status){
		case IDLE:
			if(EQUALS(intervale, TOKEN_D_START)){
				NEXT_STATUS_START_D();
			}
			break;
		case START_D:
			if(EQUALS(intervale, TOKEN_U_START)){
				IR_receiver.data = 0;
				IR_receiver.index = 0;
				NEXT_STATUS_START_U();
			}
			else if(EQUALS(intervale, TOKEN_U_REP)){
				if( !((IR_receiver.data >> 8) & (IR_receiver.data & 0x000000FF)) ){	// Ya se han leído todos los datos y la trama es correcta
					NEXT_STATUS_COMPLETED();
					SUCCESS();
					IR_receiver.passed_min_time = FALSE;
					if(IR_receiver.command_handler != NULL)		// Si todo es correcto y existe un completion_handler, se le invoca
						IR_receiver.command_handler((uint16_t)(IR_receiver.data >> 16), (uint8_t)(IR_receiver.data >> 8));
				}
			}
			else{
				ERROR("START mal formado");
				NEXT_STATUS_IDLE();
			}
			break;
		case START_U:
			if(EQUALS(intervale, TOKEN_D_DATA)){
				NEXT_STATUS_DATA_D();
			}
			else{
				ERROR("START DOWN mal formado");
				NEXT_STATUS_IDLE();
			}
			break;
		case DATA_D:
			if(EQUALS(intervale, TOKEN_U_0)){		// Almaceno un 0
				IR_receiver.index++;
			}
			else if(EQUALS(intervale, TOKEN_U_1)){	// Almaceno un 1
				IR_receiver.data |= DATA_BIT(IR_receiver.index);
				IR_receiver.index++;
			}
			else{
				ERROR("DATA UP mal formado");
				NEXT_STATUS_IDLE();
				break;
			}
			if(IR_receiver.index < 32){  // Aún quedan datos por leer
				NEXT_STATUS_DATA_U();
			}
			else if( !((IR_receiver.data >> 8) & (IR_receiver.data & 0x000000FF)) ){	// Ya se han leído todos los datos y la trama es correcta
				NEXT_STATUS_COMPLETED();
				SUCCESS();
				IR_receiver.passed_min_time = FALSE;
				if(IR_receiver.command_handler != NULL)		// Si todo es correcto y existe un completion_handler, se le invoca
					IR_receiver.command_handler((uint16_t)(IR_receiver.data >> 16), (uint8_t)(IR_receiver.data >> 8));
			}
			else{	// Ya se han leido todos los datos pero la trama es incorrecta
				ERROR("TRAMA mal formada");
				NEXT_STATUS_IDLE();
			}
			break;
		case DATA_U:
			if(EQUALS(intervale, TOKEN_D_DATA)){
				NEXT_STATUS_DATA_D();
			}
			else{
				ERROR("DATA DOWN mal formado");
				NEXT_STATUS_IDLE();
			}
			break;
		case COMPLETED:
			if(!IR_receiver.passed_min_time){
				if(intervale > MIN_REP_TIME){
					IR_receiver.passed_min_time = TRUE;
					IR_receiver.last_lecture_time = timevalue;
				}
				break;
			}
			if(EQUALS(intervale, TOKEN_D_START)){
				NEXT_STATUS_START_D();
			}
			break;
	}
    
#ifdef IR_DEBUG
    if(IR_error.index >= IR_ERROR_NUM_VALUES)
        ir_error_initialize();
    else
        IR_error.index++;
#endif
}



void init_IR_receiver(completion_handler handler){

	IR_receiver.status = IDLE;
	IR_receiver.last_lecture_time = 0;
	IR_receiver.command_handler = handler;
	IR_receiver.passed_min_time = TRUE;

#ifdef IR_DEBUG
	ir_error_initialize();
#endif

    interrupt_attach(INT0_int, nec_protocol_isr);

	EICRA = 0x01;

	EIMSK = 0x01;
	PCICR = 0x00;
}
