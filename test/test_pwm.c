// PWM test

#include <arduino/arduinoUNO.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/power.h>
#include <uc/timers.h>

#define FREQ_CNT (20)
#define DUTY_HALF (FREQ_CNT/2)


//void timer0_fast_pwm(uint8_t freq_cnt, uint8_t duty_cnt);

int main( void ) {

	timers_init();
	
	DDRD |= _BV(DDD3) | _BV(DDD6) | _BV(DDD5); 
	//IOPORT_CONFIG(OUTPUT, PORT_A, PIN_PWM_0 | PIN3);
	PORTD |= _BV(PORTD3);
	//IOPORT_VALUE(HIGH, PORT_A, PIN3);

	//timer0_fast_pwm(prescale_1024, 255, 50);
	
	while(1);
	
	return 0;
}
