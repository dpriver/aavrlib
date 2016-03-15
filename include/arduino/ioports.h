#include <avr/io.h>


// Arduino pins convenience macros
// Really, PORTxn is the corresponding PIN for the IOPORT value register, but, 
// since all 3 IOPORTS registers (PORTx, PINx, DDRx) use the same bit for the 
// same pin, it works... (by the time) 
// if this changes in the future, a fix would be mandatory


// Digital IOport A
#define PIN0	(1 << PORTD0)
#define PIN1	(1 << PORTD1)
#define PIN2	(1 << PORTD2)
#define PIN3	(1 << PORTD3)
#define PIN4	(1 << PORTD4)
#define PIN5	(1 << PORTD5)
#define PIN6	(1 << PORTD6)
#define PIN7	(1 << PORTD7)

// Digital IOPort B
#define PIN8	(1 << PORTB0)
#define PIN9	(1 << PORTB1)
#define PIN10	(1 << PORTB2)
#define PIN11	(1 << PORTB3)
#define PIN12	(1 << PORTB4)
#define PIN13	(1 << PORTB5)

// Analog IOPort
#define PINA0	(1 << PORTC0)
#define PINA1	(1 << PORTC1)
#define PINA2	(1 << PORTC2)
#define PINA3	(1 << PORTC3)
#define PINA4	(1 << PORTC4)
#define PINA5	(1 << PORTC5)


#define PWM_0	PIN6


// _MODE values
// SET can be used for both _CONFIG_MODE and _VALUE_MODE
#define SET		= (

// _CONFIG_MODE values
#define INPUT 	|= (
#define OUTPUT 	&= ~(

//	_VALUE_MODE values
#define HIGH	|= (
#define LOW		$= ~(

// _PORT values
#define PORT_A	DDRD
#define PORT_B	DDRB


// Configure and set values for digital I/O pins
// for example:
// 	pins 0, 3, 5 as output    
//	DIGITAL_CONFIG(OUTPUT, PORT_A, PIN0 | PIN3 | PIN5);

// 	pins 8, 12, 13 as input    
//	DIGITAL_CONFIG(OUTPUT, PORT_B, PIN8 | PIN12 | PIN13);

// 	pins 0, 3 as 1, and 11 as 0
//	DIGITAL_VALUE(HIGH, PORT_A, PIN0 | PIN3);
//	DIGITAL_VALUE(LOW, PORT_B, PIN11);

// Of course, unless included in the mask, or invoked in SET mode, the other
// port pins keep their previous value and configuration.

#define DIGITAL_CONFIG(_CONFIG_MODE, _PORT,  pinmask) \
	_PORT _CONFIG_MODE pinmask )


#define DIGITAL_VALUE(_VALUE_MODE, _PORT, pinmask)
	_PORT _VALUE_MODE pinmask )

