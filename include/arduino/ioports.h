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
#define PIN8	(1 << (PORTB0+8))
#define PIN9	(1 << (PORTB1+8))
#define PIN10	(1 << (PORTB2+8))
#define PIN11	(1 << (PORTB3+8))
#define PIN12	(1 << (PORTB4+8))
#define PIN13	(1 << (PORTB5+8))

// Analog IOPort
#define PINA0	(1 << PORTC0)
#define PINA1	(1 << PORTC1)
#define PINA2	(1 << PORTC2)
#define PINA3	(1 << PORTC3)
#define PINA4	(1 << PORTC4)
#define PINA5	(1 << PORTC5)


DIGITAL_CONFIG_OUTPUT(pinmask_16b) \
	DDRD |= (uint8_t)(pinmask_16b); \
	DDRB |= (uint8_t)((pinmask_16b) >> 8)

DIGITAL_CONFIG_INPUT(pinmask_16b) \
	DDRD &= (uint8_t)(~(pinmask_16b)); \
	DDRB &= (uint8_t)(~(pinmask_16b) >> 8)


// Le pasas una lista de pines y los configura como pines de salida
DIGITAL_B_CONFIG_OUTPUT(pinmask) \
	DDRB |= pinmask


DIGITAL_A_CONFIG_OUTPUT(pinmask) \
	DDRD |= pinmask

ANALOG_CONFIG_OUTPUT()


DIGITAL_B_CONFIG_INPUT(pinmask) \
	DDRB &= ~(pinmask)

DIGITAL_A_CONFIG_INPUT(pinmask) \
	DDRD &= ~(pinmask)
	
ANALOG_CONFIG_INPUT()


DIGITAL_B_CONFIG(pinmask) \
	DDRB = pinmask

DIGITAL_A_CONFIG() \
	DDRD = pinmask

ANALOG_CONFIG()


DIGITAL_A_SET_VALUE_HIGH()

DIGITAL_B_SET_VALUE_HIGH()


DIGITAL_A_SET_VALUE_LOW()

DIGITAL_B_SET_VALUE_LOW()


DIGITAL_A_SET_VALUE()

DIGITAL_B_SET_VALUE()
