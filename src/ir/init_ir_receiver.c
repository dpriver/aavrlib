#include "ir.h"
#include <avr/interrupt.h>
#include "systick.h"
#include "common.h"

#ifdef IR_DEBUG
#include "usart.h"
#endif

#define DATA_BIT(index) 0x80000000 >> index
#define EQUALS(value, intervale) ( (value >= intervale*0.8) && (value <= intervale*1.2) )

#define PULSE_TIME 562

#ifdef IR_FALL_MODE

#define TOKEN_START 13500
#define TOKEN_0 PULSE_TIME*2    // 1 down + 1 up
#define TOKEN_1 PULSE_TIME*4    // 1 down + 3 up
#define TOKEN_REP 11350
#define MIN_REP_TIME 160000

#else

#define TOKEN_D_START 9000
#define TOKEN_U_START 4500
#define TOKEN_D_DATA PULSE_TIME
#define TOKEN_U_0 PULSE_TIME
#define TOKEN_U_1 PULSE_TIME*3
#define TOKEN_D_REP 9000
#define TOKEN_U_REP 2000
#define MIN_REP_TIME 80000

#endif


#ifdef IR_DEBUG //    DEBUG MACROS
 #ifdef IR_FALL_MODE

#define NEXT_STATUS_IDLE() IR_receiver.status = IDLE;
#define NEXT_STATUS_START() \
		IR_receiver.status = START; \
		ir_error_initialize();
#define NEXT_STATUS_DATA() IR_receiver.status = DATA;
#define NEXT_STATUS_COMPLETED() IR_receiver.status = COMPLETED;
#define SUCCESS() dump_lecture();
#define ERROR() \
		IR_error.fails_post[IR_error.index] = TRUE; \
		IR_error.num_fails++; \
		dump_lecture();

 #else

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

 #endif
#else     //            NORMAL MACROS
 #ifdef IR_FALL_MODE

#define NEXT_STATUS_IDLE() IR_receiver.status = IDLE;
#define NEXT_STATUS_START() IR_receiver.status = START;
#define NEXT_STATUS_DATA() IR_receiver.status = DATA;
#define NEXT_STATUS_COMPLETED() IR_receiver.status = COMPLETED;
#define SUCCESS()
#define ERROR()

 #else

#define NEXT_STATUS_IDLE() IR_receiver.status = IDLE;
#define NEXT_STATUS_START_D() IR_receiver.status = START_D;
#define NEXT_STATUS_START_U() IR_receiver.status = START_U;
#define NEXT_STATUS_DATA_D() IR_receiver.status = DATA_D;
#define NEXT_STATUS_DATA_U() IR_receiver.status = DATA_U;
#define NEXT_STATUS_COMPLETED() IR_receiver.status = COMPLETED;
#define SUCCESS()
#define ERROR(cadena)
 
 #endif
#endif



#ifdef IR_DEBUG
// ============================ DEBUG ====================================
// =======================================================================
uint32_t micros_prueba(){
	uint8_t oldSREG = SREG;
	
	cli();
	IR_error.mili[IR_error.index] = system_tick.current_tick;
	IR_error.micro[IR_error.index] = TCNT1;

	if( (TIFR1 & _BV(OCF1A)) && (IR_error.micro[IR_error.index] < 0xFFFF)){
		IR_error.mili[IR_error.index]++;
		IR_error.num_fails++;
		IR_error.fails[IR_error.index] = TRUE;
		DIGITAL_PORT_B |= _BV(DIGITAL_8);
	}
	IR_error.micro[IR_error.index] = IR_error.micro[IR_error.index]>>1;
	SREG = oldSREG;
	return (uint32_t)IR_error.mili[IR_error.index]*1000 + (uint32_t)IR_error.micro[IR_error.index];
}

uint32_t micros_prueba_2(){
	uint16_t current_tick, tick_2, current_count, count_2;
	uint8_t extra, extra_2;
	uint8_t oldSREG = SREG;
	IR_error.vueltas_micro[IR_error.index] = 0;

	sei();
	tick_2 = system_tick.current_tick;
	count_2 = TCNT1;
	extra_2 = (TIFR1 & _BV(OCF1A)) && (count_2 < 0xFFFF);


	do{
		current_tick = tick_2;
		current_count = count_2;
		extra = extra_2;
		tick_2 = system_tick.current_tick;
		count_2 = TCNT1;
		extra_2 = (TIFR1 & _BV(OCF1A)) && (current_count < 0xFFFF);
		IR_error.vueltas_micro[IR_error.index]++;
	} while ( (current_tick!=tick_2) || (extra!=extra_2)  || tick_2 < current_tick);


	if( extra ){
		current_tick++;
		IR_error.num_fails++;
		IR_error.fails[IR_error.index] = TRUE;
	}

	IR_error.mili[IR_error.index] = current_tick;
	IR_error.micro[IR_error.index] = current_count>>1;	

	SREG = oldSREG;
	return (uint32_t)current_tick*1000 + (uint32_t)(current_count>>1);
}

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

 #ifdef IR_FALL_MODE
void print_status(uint8_t status){
	switch(status){
		case IDLE:
			usart_print("IDLE");
			break;
		case START:
			usart_print("START");
			break;
		case DATA:
			usart_print("DATA");
			break;
		case COMPLETED:
			usart_print("COMPLETED");
			break;
	}
}
 #else
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
 #endif

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
	usart_print("\nTiempo ISR: ");
	usart_printnumber32((uint32_t)system_tick.tiempoISR);
	usart_print("\n============================");
}

// =======================================================================
// =======================================================================
#endif




void init_IR_receiver(completion_handler handler){

	IR_receiver.status = IDLE;
	IR_receiver.last_lecture_time = 0;
	IR_receiver.command_handler = handler;
	IR_receiver.passed_min_time = TRUE;

#ifdef IR_DEBUG
	ir_error_initialize();
#endif

#ifdef IR_FALL_MODE
	EICRA = 0x02;
#else
	EICRA = 0x01;
#endif

	EIMSK = 0x01;
	PCICR = 0x00;
}


#ifdef IR_FALL_MODE
// =============================== FALL MODE ==================================
// ============================================================================
ISR(INT0_vect, ISR_NOBLOCK){
	// obtener tiempo
	uint32_t timevalue, intervale;
	uint8_t oldSREG = SREG;

#ifdef IR_DEBUG
	timevalue = micros_prueba_2();
#else
	timevalue = micros();
#endif

	cli();
	// determinar el significado del intervalo recibido
	// comparando con la última marca de tiempo
	if(timevalue > IR_receiver.last_lecture_time)
		intervale = timevalue - IR_receiver.last_lecture_time;
	else
		intervale = MAX_MICROS_COUNT - IR_receiver.last_lecture_time + timevalue;

#if IR_DEBUG
	IR_error.diff[IR_error.index] = intervale;
#endif

	if(IR_receiver.passed_min_time)
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
			else{
				ERROR();
				NEXT_STATUS_IDLE();
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
			else{
				ERROR();
				NEXT_STATUS_IDLE();
			}
			if(IR_receiver.index == 32){
				if( (IR_receiver.data >> 8) & (IR_receiver.data & 0x000000FF) ){
					ERROR();
					NEXT_STATUS_IDLE();	// ERROR, la trama es incorrecta
				}
				else{
					IR_receiver.passed_min_time = FALSE;
					SUCCESS();
					if(IR_receiver.command_handler != NULL){		// Si todo es correcto y existe un completion_handler, se le invoca
						sei();
						IR_receiver.command_handler((uint16_t)(IR_receiver.data >> 16), (uint8_t)(IR_receiver.data >> 8));
						cli();
					}
					NEXT_STATUS_COMPLETED(); // La trama es correcta
				}
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
			if( EQUALS(intervale, TOKEN_REP) ){
				IR_receiver.passed_min_time = FALSE;
				SUCCESS();
				if(IR_receiver.command_handler != NULL){		// SI todo es correcto y existe un completion_handler, se le invoca
					sei();
					IR_receiver.command_handler((uint16_t)(IR_receiver.data >> 16), (uint8_t)(IR_receiver.data >> 8));
					cli();
				}
			}
			else if( EQUALS(intervale, TOKEN_START) ){  // start token
				NEXT_STATUS_START();
			}
			break;
	}

#ifdef IR_DEBUG
	if( (IR_receiver.status != START) ){
		if(IR_error.index >= IR_ERROR_NUM_VALUES)
			ir_error_initialize();
		else
			IR_error.index++;
	}
#endif

	SREG = oldSREG;
}
// ============================================================================
// ============================================================================
#else
// =========================== STANDARD MODE ==================================
// ============================================================================
ISR(INT0_vect, ISR_BLOCK){
	// obtener tiempo
	uint32_t timevalue, intervale;

	#ifdef IR_DEBUG
		timevalue = micros_prueba_2();
	#else
		timevalue = micros();
	#endif


	// determinar el significado del intervalo recibido
	// comparando con la última marca de tiempo
	if(timevalue > IR_receiver.last_lecture_time)
		intervale = timevalue - IR_receiver.last_lecture_time;
	else
		intervale = MAX_MICROS_COUNT - IR_receiver.last_lecture_time + timevalue;

	if(IR_receiver.passed_min_time)
		IR_receiver.last_lecture_time = timevalue;


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
				ERROR("DATA DOWN mal formado");
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
}
// ============================================================================
// ============================================================================
#endif