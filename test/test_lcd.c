#include "systick.h"
#include "lcd.h"
#include <avr/interrupt.h>

/*
    Wait for abour 20mS
    Send the first init value (0x30)
    Wait for about 10mS
    Send second init value (0x30)
    Wait for about 1mS
    Send third init value (0x30)
    Wait for 1mS
    Select bus width (0x30 - for 8-bit and 0x20 for 4-bit)
    Wait for 1mS

*/

int main(void){

	init_system_tick();
	sei();
	init_lcd();

	lcd_send(0x81, LCD_DATA);

	DIGITAL_CONF_REG_B |= _BV(DIGITAL_CONF_10);
	//DDRB |= _BV(DDB2);

	while(1){
		DIGITAL_PORT_B |= _BV(DIGITAL_10);
		//PORTB |= _BV(PORTB2);
		delay_ms(250);
		DIGITAL_PORT_B &= ~_BV(DIGITAL_10);
		//PORTB &= ~_BV(PORTB2);
		delay_ms(250);
	}
	return 0;
}