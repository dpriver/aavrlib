/*====================================================================================================================================
 * Daniel Pinto Rivero	09-08-2014 Cáceres, Spain
 * program to play with ir receiver before making the lib functions
 *=====================================================================================================================================*/

#include <stdint.h>
#include "systick.h"
#include <avr/interrupt.h>

#include "delay.h"
#include "usart.h"
#include "ir.h"


void comm_handler(uint16_t address, uint8_t command){
	switch(command){
		case 0:
			usart_print("\nON/OFF");
			break;
		case 128:
			usart_print("\nVOL+");
			break;
		case 64:
			usart_print("\nfunc/stop");
			break;
		case 32:
			usart_print("\n|<<");
			break;
		case 160:
			usart_print("\n>||");
			break;
		case 96:
			usart_print("\n>>|");
			break;
		case 16:
			usart_print("\nv");
			break;
		case 144:
			usart_print("\nVOL-");
			break;
		case 80:
			usart_print("\n^");
			break;
		case 48:
			usart_print("\n0");
			break;
		case 176:
			usart_print("\nEQ");
			break;
		case 112:
			usart_print("\nst/rept");
			break;
		case 8:
			usart_print("\n1");
			break;
		case 136:
			usart_print("\n2");
			break;
		case 72:
			usart_print("\n3");
			break;
		case 40:
			usart_print("\n4");
			break;
		case 168:
			usart_print("\n5");
			break;
		case 104:
			usart_print("\n6");
			break;
		case 24:
			usart_print("\n7");
			break;
		case 152:
			usart_print("\n8");
			break;
		case 88:
			usart_print("\n9");
			break;
		default:
			usart_print("\nUNKNOWN: ");
			usart_printnumber32(command);
			break;
	}
}

int main(void){

	init_system_tick();
	usart_init();
	sei();

	// pin del sensor
	DIGITAL_CONF_REG_B = _BV(DIGITAL_CONF_8) | _BV(DIGITAL_CONF_10) | _BV(DIGITAL_CONF_11) | _BV(DIGITAL_CONF_12);

	// led test
	usart_print("Led_test:");
	DIGITAL_PORT_B |= _BV(DIGITAL_12);
	delay_ms(250);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_12);
	DIGITAL_PORT_B |= _BV(DIGITAL_11);
	delay_ms(250);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_11);
	DIGITAL_PORT_B |= _BV(DIGITAL_10);
	delay_ms(250);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_10);
	DIGITAL_PORT_B |= _BV(DIGITAL_8);
	delay_ms(250);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_8);
	DIGITAL_PORT_B |= _BV(DIGITAL_9);
	delay_ms(250);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_9);
	delay_ms(250);
	DIGITAL_PORT_B |= _BV(DIGITAL_8);
	DIGITAL_PORT_B |= _BV(DIGITAL_9);
	DIGITAL_PORT_B |= _BV(DIGITAL_10);
	DIGITAL_PORT_B |= _BV(DIGITAL_11);
	DIGITAL_PORT_B |= _BV(DIGITAL_12);
	delay_ms(500);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_8);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_9);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_10);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_11);
	DIGITAL_PORT_B &= ~_BV(DIGITAL_12);	
	usart_print("................Completed.\n");
	delay_ms(1000);

	init_IR_receiver(comm_handler);
	
	
	DIGITAL_PORT_B |= _BV(DIGITAL_12); // 12

	while(1){
		for(int i = 0 ; i<3 ; i++){
			DIGITAL_PORT_B |= _BV(DIGITAL_10);
			delay_ms(500);
			DIGITAL_PORT_B &= ~_BV(DIGITAL_10);
			delay_ms(500);
			//usart_print("\nmicros: ");
			//usart_printnumber32(micros());
		}
/*		cli();
		usart_print("\n======================================\nIntervale values:");
		for(int i = 0; i<79 ; i+=2){
			usart_print("\n -");
			usart_printnumber32(IR_receiver.values[i]);
			usart_print("\t -");
			usart_printnumber32(IR_receiver.values[i+1]);
			IR_receiver.values[i] = 0;
			IR_receiver.values[i+1] = 0;
		}
		IR_receiver.val_index = 0;
		sei();
*/
	}
}

/*

#define VALUES 40
int main(){
	//uint8_t valor[40];
	uint32_t times[VALUES];
	uint16_t micro[VALUES];
	uint16_t mili[VALUES];
	uint32_t timestamp = 0, us;

	init_system_tick();
	usart_init();
	sei();

	//while( (DIGITAL_VALUE_B & _BV(DIGITAL_11)) );

	for(int i = 0; i< VALUES ; i++){
		//while( (DIGITAL_VALUE_B & _BV(DIGITAL_11)) );
		times[i] = micros();
		//valor[i] = (DIGITAL_VALUE_B & _BV(DIGITAL_11)) ? 111 : 000;
		micro[i] = TCNT1 >> 1;
		mili[i] = system_tick.current_tick;
		//while( !(DIGITAL_VALUE_B & _BV(DIGITAL_11)) );
		delay_ms(1);
	}

	usart_print("Valores\n===============================\n");
	for(int i = 0; i< VALUES ; i++){
		//usart_print("\n------------------valor: ");
		//usart_printnumber(valor[i]);
		usart_print("\ntimes: ");
		usart_printnumber32(times[i]);
		usart_print("\nmilis: ");
		usart_printnumber32(mili[i]);
		usart_print("\nmicros: ");
		usart_printnumber32(micro[i]);
	}

	return 0;
}
*/