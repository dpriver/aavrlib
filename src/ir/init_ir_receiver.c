#include "ir.h"
#include <avr/interrupt.h>
#include "systick.h"
#include "common.h"
#include "usart.h"

#define DATA_BIT(index) 0x80000000 >> index

#define EQUALS(value, intervale) ( (value >= intervale*0.96) && (value <= intervale*1.04) )
#define TOKEN_START 13500  	// [12960,14040]
#define TOKEN_0 1125		// [1080,1170]
#define TOKEN_1 2250		// [2160, 2340]
#define TOKEN_REP 11350		// [10896,11804]


void dump_lecture(){
	usart_print("\n======================================\nIntervale values:");
	for(int i = 0; i<40 ; i++){
		usart_print("\n -");
		usart_printnumber32(IR_receiver.values[i]);
	}
}

#ifdef IR_DEBUG

#define NEXT_STATUS_IDLE() IR_receiver.status = IDLE; \
				DIGITAL_PORT_B &= ~_BV(DIGITAL_11); \
				DIGITAL_PORT_B |= _BV(DIGITAL_12);
#define NEXT_STATUS_START() IR_receiver.status = START; \
				DIGITAL_PORT_B &= ~_BV(DIGITAL_12); \
				DIGITAL_PORT_B |= _BV(DIGITAL_11); \
				for(int i = 0; i<40; i++) IR_receiver.values[i] = 0; \
				IR_receiver.val_index = 0;
#define NEXT_STATUS_DATA() IR_receiver.status = DATA; \
				DIGITAL_PORT_B &= ~_BV(DIGITAL_12); \
				DIGITAL_PORT_B |= _BV(DIGITAL_11);
#define NEXT_STATUS_COMPLETED() IR_receiver.status = COMPLETED; \
				DIGITAL_PORT_B &= ~_BV(DIGITAL_11); \
				DIGITAL_PORT_B |= _BV(DIGITAL_12);
#define SUCCESS() DIGITAL_PORT_B &= ~_BV(DIGITAL_9); \
				DIGITAL_PORT_B |= _BV(DIGITAL_8);
#define ERROR() DIGITAL_PORT_B &= ~_BV(DIGITAL_8); \
				DIGITAL_PORT_B |= _BV(DIGITAL_9);
#else

#define NEXT_STATUS_IDLE() IR_receiver.status = IDLE;
#define NEXT_STATUS_START() IR_receiver.status = START; \
				for(int i = 0; i<40; i++) IR_receiver.values[i] = 0; \
				IR_receiver.val_index = 0;
#define NEXT_STATUS_DATA() IR_receiver.status = DATA;
#define NEXT_STATUS_COMPLETED() IR_receiver.status = COMPLETED;
#define SUCCESS()
#define ERROR() dump_lecture();
#define MAYBE_A_MISS() if( EQUALS(intervale+1000, TOKEN_1) || EQUALS(intervale-1000, TOKEN_1) ) \
							usart_print("\nMAYBE A 1...."); \
						if( EQUALS(intervale+1000, TOKEN_0) || EQUALS(intervale-1000, TOKEN_0) ) \
							usart_print("\nMAYBE A 0....");

#define CORRECT()  if( EQUALS(intervale+1000, TOKEN_1) || EQUALS(intervale-1000, TOKEN_1) ) \
						usart_print("\nMAYBE A 1...."); \
					if( EQUALS(intervale+1000, TOKEN_0) || EQUALS(intervale-1000, TOKEN_0) ) \
						usart_print("\nMAYBE A 0....");

#endif


void init_IR_receiver(completion_handler handler){

	IR_receiver.command_handler = NULL;
	IR_receiver.status = IDLE;
	IR_receiver.last_lecture_time = 0;
	IR_receiver.command_handler = handler;


	EICRA = 0x02;
	EIMSK = 0x01;
	PCICR = 0x00;
}



ISR(INT0_vect, ISR_BLOCK){
	// obtener tiempo
	uint32_t timevalue,timevalue_test, intervale;
	//Trying to correct the tickmiss, i delay a time and compare the values,
	// if it is really big, i assume a miss	
	timevalue = micros();
	timevalue_test = micros();
	if( (timevalue_test - timevalue) > 1000){
		timevalue += 1000;
	}


	// determinar el significado del intervalo recibido
	// comparando con la última marca de tiempo
	intervale = timevalue - IR_receiver.last_lecture_time;

	if( IR_receiver.val_index < 40){
		IR_receiver.values[IR_receiver.val_index] = intervale;
		IR_receiver.val_index++;
	}

	IR_receiver.last_lecture_time = timevalue;

	switch(IR_receiver.status){
		case IDLE:
			if( EQUALS(intervale, TOKEN_START) ){  // start token
				NEXT_STATUS_START();
			}
			break;
		case START:
			if( EQUALS(intervale, TOKEN_1) ){
				IR_receiver.data = 0x80000000;
				IR_receiver.index = 1;
				NEXT_STATUS_DATA();
			}
			else if( EQUALS(intervale, TOKEN_0) ){
				IR_receiver.data = 0x00000000;
				IR_receiver.index = 1;
				NEXT_STATUS_DATA();
			}
			else if( EQUALS(intervale+1000, TOKEN_1) || EQUALS(intervale-1000, TOKEN_1) ){	// correct micros() misstick
				IR_receiver.data = 0x80000000;
				IR_receiver.index = 1;
				NEXT_STATUS_DATA();
			}
			else if( EQUALS(intervale+1000, TOKEN_0) || EQUALS(intervale-1000, TOKEN_0) ){
				IR_receiver.data = 0x00000000;
				IR_receiver.index = 1;
				NEXT_STATUS_DATA();
			}
			else{
				NEXT_STATUS_IDLE();
				ERROR();
			}
			break;
		case DATA:
			if( EQUALS(intervale, TOKEN_1) ){
				IR_receiver.data |= DATA_BIT(IR_receiver.index);
				IR_receiver.index++;
			}
			else if( EQUALS(intervale, TOKEN_0) ){
				IR_receiver.index++;
			}
			else if( EQUALS(intervale+1000, TOKEN_1) || EQUALS(intervale-1000, TOKEN_1) ){  // correct micros() misstick
				IR_receiver.data |= DATA_BIT(IR_receiver.index);
				IR_receiver.index++;
			}
			else if( EQUALS(intervale+1000, TOKEN_0) || EQUALS(intervale-1000, TOKEN_0) ){
				IR_receiver.index++;
			}
			else{
				NEXT_STATUS_IDLE();
				ERROR();
			}

			if(IR_receiver.index == 32){
				if( (IR_receiver.data >> 8) & (IR_receiver.data & 0x000000FF) ){
					NEXT_STATUS_IDLE();	// ERROR, la trama es incorrecta
					ERROR();
				}
				else{
					NEXT_STATUS_COMPLETED();
					SUCCESS();
					if(IR_receiver.command_handler != NULL);		// Si todo es correcto y existe un completion_handler, se le invoca
						IR_receiver.command_handler((uint16_t)(IR_receiver.data >> 16), (uint8_t)(IR_receiver.data >> 8));
					// La trama es correcta
				}
			}
			break;
		case COMPLETED:
			if( EQUALS(intervale, TOKEN_REP) ){
				if(IR_receiver.command_handler != NULL)		// SI todo es correcto y existe un completion_handler, se le invoca
					IR_receiver.command_handler((uint16_t)(IR_receiver.data >> 16), (uint8_t)(IR_receiver.data >> 8));
			}
			else if( EQUALS(intervale, TOKEN_START) ){  // start token
				NEXT_STATUS_START();
			}
			else{
				// Error
			}
			break;
	}
}