#ifndef _SPI_
#define _SPI_

#include <avr/io.h>
#include <stdint.h>


void spi_send_block(const uint8_t caracteres[], uint8_t length);
void spi_send_burst(const uint8_t caracters[], uint8_t length, uint8_t burst_length);


#define spi_setup_master() \
	DDRB |= _BV(DDB2) | _BV(DDB3) | _BV(DDB5); \
	SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0) | _BV(SPR1);

#define spi_setup_slave() \
	DDRB &= ~_BV(DDB3) & ~_BV(DDR2) & ~_BV(DDR5); \
	SPCR = _BV(SPIE) | _BV(SPE) | _BV(SPR0);


#define spi_sendbyte(byte) \
	PORTB &= ~_BV(PORTB2); \
	SPDR = byte; \
	while( !(SPSR & _BV(SPIF)) ); \
	PORTB |= _BV(PORTB2);

#define spi_receivebyte(variable) \
	PORTB &= ~_BV(PORTB2); \
	SPDR = 0xff; \
	while( !(SPSR & _BV(SPIF)) ); \
	PORTB |= _BV(PORTB2); \
	spi_readbyte(variable);	

#define spi_readbyte(variable) \
	variable = SPDR;







#endif