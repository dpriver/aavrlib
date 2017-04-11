/*******************************************************************************
 *	spi.h
 *
 *  spi
 *
 *
 *  This file is part of aavrlib
 * 
 *  Copyright (C) 2015  Dennis Pinto Rivero
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

// avr defines
#include <avr/interrupt.h>
#include <avr/power.h>
#include <stdint.h>

#include "uc/interrupt.h"
#include "uc/spi.h"
#include "common.h"
#include "config.h"
#include "ioport.h"

/*
 * For master transmitt:
 * - Pull down the specific SS pin
 * - 
 */

/* SPI Functionality
 * 
 * When in Master mode, SS can be configured:
 * 1. As output to drive the SS signal of the slave device
 *  - Keep it high to maintain the slave device pasive
 *  - Pull it down to activate the slave and start a transmission
 * 2. As input to allow another master to force it to slave mode
 */

/*
 * When the SS pin in driven low while in master mode, then SPIF flag 
 * is automatically set to 1. (Triggering an interrupt if corresponds)
 */

/*
 * The SPIF bit is cleared:
 * 1. When entering the SPI_STC ISR
 * 2. By reading SPSR and then SPDR
 */



/*
 * send_pending is the number of written bytes pending to send. 
 *  - Increased at spi_write
 *  - Decreased at __vector_spi_isr
 * 
 * recv_pending is the number of received bytes pending to read.
 *  - Increased at __vector_spi_isr
 *  - Decreased at spi_read
 */
 
volatile static struct{
	uint8_t send_buffer[SPI_BUFF_SIZE];
    uint8_t recv_buffer[SPI_BUFF_SIZE];
	uint8_t send_pending;
    uint8_t send_first_index;
    uint8_t send_last_index;
    uint8_t recv_pending;
    uint8_t recv_first_index;
    uint8_t recv_last_index;;
}spi_attr;



#define RECV_FULL()     (spi_attr.recv_pending == SPI_BUFF_SIZE)
#define RECV_EMPTY()    (spi_attr.recv_pending == 0)

#define SEND_FULL()     (spi_attr.send_pending == SPI_BUFF_SIZE)
#define SEND_EMPTY()    (spi_attr.send_pending == 0)

#define ADVANCE_INDEX(index)  index = (index == SPI_BUFF_SIZE-1)? 0 : index+1; 


INTERRUPT(__vector_spi_stc_isr) {
    
    // Save the new received byte
    spi_attr.recv_buffer[spi_attr.recv_last_index] = SPDR;
    if (RECV_FULL()) {  // if full, overwrite the first byte
        // Both indexes have to advance
        // There are the same number of bytes pending
        ADVANCE_INDEX(spi_attr.recv_last_index);
        ADVANCE_INDEX(spi_attr.recv_first_index);
    }
    else {
        spi_attr.recv_pending++;
        ADVANCE_INDEX(spi_attr.recv_last_index);     
    }

    // A new transmission has finished, so there is 1 send pending 
    // byte less
    ADVANCE_INDEX(spi_attr.send_first_index);
    spi_attr.send_pending--;
    
    // if there are some more pending bytes to send
    if (spi_attr.send_pending > 0) {    
        SPDR = spi_attr.send_buffer[spi_attr.send_first_index];
    }
}


uint8_t spi_received_bytes() {
    uint8_t pending;
    uint8_t oldSREG = SREG;
    
    cli();
    pending = spi_attr.recv_pending;
    SREG = oldSREG;
    
    return pending;
}


uint8_t spi_send_pending() {
    uint8_t pending;
    uint8_t oldSREG = SREG;
    
    cli();
    pending = spi_attr.send_pending;
    SREG = oldSREG;
    
    return pending;
}


void spi_write(uint8_t *bytes, uint8_t length) {
    uint8_t i;
    uint8_t oldSREG = SREG;
    
    cli();
    
    for (i = 0; i < length ; i++) {
        spi_attr.send_buffer[spi_attr.send_last_index] = bytes[i];
        ADVANCE_INDEX(spi_attr.send_last_index);
    }
    
    // If the send buffer is empty, SPDR contains invalid data, so
    // it has to fill it.
    // Also, if in master mode, it means that there is no transmission 
    // running, so this starts it.
    if (SEND_EMPTY()) {
        SPDR = spi_attr.send_buffer[spi_attr.send_first_index];
    }
   
    spi_attr.send_pending += length;
    
    SREG = oldSREG;
}


void spi_read(uint8_t *bytes, uint8_t length) {
    uint8_t i;
    uint8_t oldSREG = SREG;
    
    cli();
    
    for (i = 0; i < length ; i++) {
        bytes[i] = spi_attr.recv_buffer[spi_attr.recv_first_index];
        ADVANCE_INDEX(spi_attr.recv_first_index);
    }
    
    spi_attr.recv_pending -= length;
    
    SREG = oldSREG;
}


void spi_master_init() {
    spi_attr.send_pending = 0;
    spi_attr.recv_pending = 0;
    spi_attr.recv_first_index = SPI_BUFF_SIZE-1;
    spi_attr.recv_last_index = 0;
    spi_attr.send_first_index = SPI_BUFF_SIZE-1;
    spi_attr.send_last_index = 0;
    
    power_spi_enable();
    
    // Configure SPI pins as outputs
    // The user defined pins in master mode are MOSI, MISO, SCK and SS
    IOPORT_CONF_OUT(SPI_PORT, SPI_MOSI | SPI_SCK | SPI_SS);
    IOPORT_CONF_IN(SPI_PORT, SPI_MISO);
    
	// Enble, MSB first, slave mode, Leading edge rising, 
    // Sample at leading and setup at trailing, freq at fosc/4
    // interrupt
    SPCR = _BV(SPE) | _BV(SPIE) | _BV(MSTR);
	
    // Normal speed
    SPSR = 0;

    // install ISR
    interrupt_attach(SPI_STC_int, __vector_spi_stc_isr);
}


void spi_slave_init() {
    // init SPI control variables
    spi_attr.send_pending = 0;
    spi_attr.recv_pending = 0;
    spi_attr.recv_first_index = SPI_BUFF_SIZE-1;
    spi_attr.recv_last_index = 0;
    spi_attr.send_first_index = SPI_BUFF_SIZE-1;
    spi_attr.send_last_index = 0;
    
    power_spi_enable();
    
    // Configure SPI pins as outputs
    // The user defined pins in master mode are MOSI, MISO, SCK and SS
    IOPORT_CONF_IN(SPI_PORT, SPI_MOSI | SPI_SCK | SPI_SS);
    IOPORT_CONF_OUT(SPI_PORT, SPI_MISO);
    
	// Enble, MSB first, master mode, Leading edge rising, 
    // Sample at leading and setup at trailing, freq at fosc/4
    // interrupt
    SPCR = _BV(SPE) | _BV(SPIE);
	
    // Normal speed
    SPSR = 0;

    // install ISR
    interrupt_attach(SPI_STC_int, __vector_spi_stc_isr);
}
