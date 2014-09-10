#ifndef _SPI_
#define _SPI_

// Values to SPI_TEST:
#define NO_TEST 1
#define TEST_74HC595N 2

#define NULL 0

#ifndef SPI_TEST
	#warning "SPI to default value, 0 -NO_TEST"
	#define SPI_TEST NO_TEST
#elif (SPI_TEST != NO_TEST) && (SPI_TEST != TEST_74HC595N)
	#warning "SPI_TEST value is unknow, redefined to 0 -NO_TEST"
	#undef SPI_TEST
	#define SPI_TEST NO_TEST
#endif


#include <avr/io.h>
#include <stdint.h>
#if SPI_TEST == TEST_74HC595N
	#include "delay.h"
#endif


typedef void (*transsmision_end_handler)(void);

void spi_send_block(uint8_t caracteres[], uint8_t length);
void spi_send_burst(uint8_t caracters[], uint8_t length, transsmision_end_handler end_handler);


// Clock in master is stablished to max freq "clk/2"
#define spi_setup_master_with_int() \
	DDRB |= _BV(DDB2) | _BV(DDB3) | _BV(DDB5); \
	SPCR = _BV(SPIE) | _BV(SPE) | _BV(MSTR); \
	SPSR |= _BV(SPI2X);

#define spi_setup_master() \
	DDRB |= _BV(DDB2) | _BV(DDB3) | _BV(DDB5); \
	SPCR = _BV(SPE) | _BV(MSTR); \
	SPSR |= _BV(SPI2X);

#define spi_setup_slave() \
	DDRB &= ~_BV(DDB3) & ~_BV(DDR2) & ~_BV(DDR5); \
	SPCR = _BV(SPIE) | _BV(SPE) | _BV(SPR0) | _BV(SPR1);

#if SPI_TEST == NO_TEST

	#define spi_begin_transmission() \
		PORTB &= ~_BV(PORTB2);

	#define spi_end_transmission() \
		PORTB |= _BV(PORTB2); \
		SPCR &= ~_BV(SPE);

	#define spi_sendbyte(byte) \
		SPDR = byte;

#elif SPI_TEST == TEST_74HC595N

	#define spi_begin_transmission()

	#define spi_end_transmission() \
		PORTB |= _BV(PORTB2); \
		SPCR &= ~_BV(SPE);
	
	#define spi_sendbyte(byte) \
		PORTB |= _BV(PORTB2); \
		delay_cycle(); \
		PORTB &= ~_BV(PORTB2); \
		SPDR = byte;

#endif


#define spi_receivebyte() \
		spi_sendbyte(0xff);

#define spi_finished_transmission() \
		(SPSR & _BV(SPIF))

#define spi_readbyte(variable) \
	variable = SPDR;

// This macros can be useful in specific situations but not for common use.
// for example, i used it to test this spi module with a 74hc595n which needs to pull down and up PORTB2 (conected to
// 74hc595n's storage register clk input) between each data transmision.
// In normal situations is hardly recommended to use the provided functions spi_send_block() and spi_send_burst()







#endif