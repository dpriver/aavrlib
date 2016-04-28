// softPWM test

#include <arduino/arduinoUNO.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/power.h>
#include <uc/timers.h>
#include <uc/softPWM_short.h>
#include <uc/usart.h>
#include <uc/analog.h>
#include <avr/interrupt.h>

#define FREQ_CNT (20)
#define DUTY_HALF (FREQ_CNT/2)
#define ADC_MASK (0x0)

//void timer0_fast_pwm(uint8_t freq_cnt, uint8_t duty_cnt);

void delay();

int main( void ) {
    
    uint8_t analog_read = 0;
    uint8_t duty_count = 0;
    
    cli();
	timers_init();
    usart_init();
    softPWM_init();
    adc_init(adc_presc_128, adc_ref_vcc, adc_channel_a0, ADC_MASK);
    
    sei();
    usart_print("system init.");
    IOPORT_CONFIG(OUTPUT, PORT_C, PIN_13);
    IOPORT_VALUE(LOW, PORT_C_V, PIN_13);
    
    IOPORT_CONFIG(INPUT, PORT_A, PIN_A0);
	//DDRD |= _BV(DDD3) | _BV(DDD6) | _BV(DDD5); 
	//IOPORT_CONFIG(OUTPUT, PORT_B, PIN_5 | PIN_3);
	//PORTD |= _BV(PORTD3);
	//IOPORT_VALUE(HIGH, PORT_B_V, PIN_3);    

    softPWM_add_signal(PIN_4, &PORT_B, &PORT_B_V, 0, 124);
    
    softPWM_start();
    
    //timer2_ctc(0x7, 255, 130);
    
	while(1) {
        analog_read = adc_single_read();
        duty_count = analog_read %124;
        
		usart_print("Readed value: ");
		usart_printnumber8(analog_read);
		usart_print("\tAssigned value: ");
        usart_printnumber8(duty_count);
        usart_print("\n");
        
        softPWM_set_pulse_width(0, duty_count);
        
        delay();
    }
	
	return 0;
}


// bad delay... only for this test
void delay() {
	//uint16_t t;
	uint16_t i, j;
	
	for(i = 0 ; i < 100 ; i++){
		for(j = 0 ; j < 6000 ; j++) {
			//for(k = 0 ; k < 99999 ; k++);
		}
	}
	//t = get_uptime_sec() + ms;
	
	//while(get_uptime_sec() != t);
}

/*
SOFTPWM_TOP_ISR() {

    usart_print(" - TOP\n");
    // change to next pwm signal

    IOPORT_VALUE(HIGH, PORT_B_V, PIN_4);
}

SOFTPWM_DUTY_ISR() {
    usart_print(" - DUTY\n");

    IOPORT_VALUE(LOW, PORT_B_V, PIN_4);
}
*/
