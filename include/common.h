// Common definitions

#ifndef _COMMON
#define _COMMON

#include <avr/io.h>

/*========================================
 * Special values
 *========================================*/
#define NULL 0x00
#define TRUE 0xFF
#define FALSE 0x00

#define MAX_UINT

/*========================================
 * Arduino Pins
 *========================================*/

 // Digital ports configuration registers
#define DIGITAL_CONF_REG_A DDRD
#define DIGITAL_CONF_REG_B DDRB

 // Flags
#define DIGITAL_CONF_0 DDD0
#define DIGITAL_CONF_1 DDD1
#define DIGITAL_CONF_2 DDD2
#define DIGITAL_CONF_3 DDD3
#define DIGITAL_CONF_4 DDD4
#define DIGITAL_CONF_5 DDD5
#define DIGITAL_CONF_6 DDD6
#define DIGITAL_CONF_7 DDD7
#define DIGITAL_CONF_8 DDB0
#define DIGITAL_CONF_9 DDB1
#define DIGITAL_CONF_10 DDB2
#define DIGITAL_CONF_11 DDB3
#define DIGITAL_CONF_12 DDB4
#define DIGITAL_CONF_13 DDB5

// Digital ports
#define DIGITAL_PORT_A PORTD 
#define DIGITAL_PORT_B PORTB
#define DIGITAL_VALUE_A PIND
#define DIGITAL_VALUE_B PINB

// Flags
#define DIGITAL_0 PORTD0
#define DIGITAL_1 PORTD1
#define DIGITAL_2 PORTD2
#define DIGITAL_3 PORTD3
#define DIGITAL_4 PORTD4
#define DIGITAL_5 PORTD5
#define DIGITAL_6 PORTD6
#define DIGITAL_7 PORTD7
#define DIGITAL_8 PORTB0
#define DIGITAL_9 PORTB1
#define DIGITAL_10 PORTB2
#define DIGITAL_11 PORTB3
#define DIGITAL_12 PORTB4
#define DIGITAL_13 PORTB5

// Analog port configuration register
#define ANALOG_CONF_REG DDRC

// Flags
#define ANALOG_CONF_0 DDC0
#define ANALOG_CONF_1 DDC1
#define ANALOG_CONF_2 DDC2
#define ANALOG_CONF_3 DDC3
#define ANALOG_CONF_4 DDC4
#define ANALOG_CONF_5 DDC5

// Analog port
#define ANALOG_PORT PORTC
#define ANALOG_VALUE PINC

// Flags
#define ANALOG_0 PORTC0
#define ANALOG_1 PORTC1
#define ANALOG_2 PORTC2
#define ANALOG_3 PORTC3
#define ANALOG_4 PORTC4
#define ANALOG_5 PORTC5


#endif