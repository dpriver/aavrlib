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
 ********************************************************************************/

#ifndef __SPI
#define __SPI


#include <avr/io.h>
#include <stdint.h>

#include "config.h"


/**
 * @brief Initialize SPI as master
 * 
 */
void spi_master_init();


/**
 * @brief Initialize SPI as slave
 *
 */
void spi_slave_init();


/**
 * @brief Get the number of received bytes ready to read
 * 
 * SPI operations are buffered. This function is used to know how many 
 * bytes remains unread in the receive buffer.
 * 
 * @return The number of received bytes on buffer
 */
uint8_t spi_received_bytes();


/**
 * @brief Get the number of bytes ready to send
 * 
 * SPI operations are buffered. This function is used to know how many 
 * written bytes are still on the send buffer.
 * 
 * @return The number of bytes on send buffer
 */
uint8_t spi_send_pending();


/**
 * @brief Write data into the SPI send buffer
 *
 * The bytes from the send buffer are sended in background, using 
 * the SPI interrupt.
 * 
 * Example of usage:
 * @code
 * ...
 * uint8_t data[N];
 * uint8_t n;
 * ...
 * if ((spi_send_pending() - SPI_BUFF_SIZE) > 0) {
 *  spi_write(data, n);
 * }
 * ...
 * @endcode
 * 
 * @return The number of received bytes on buffer
 */
void spi_write(uint8_t *bytes, uint8_t length);


/**
 * @brief Read data from the SPI receive buffer
 *
 * The bytes from the receive buffer are received in background, using 
 * the SPI interrupt.
 * 
 * Example of usage:
 * @code
 * ...
 * uint8_t data[N];
 * uint8_t n;
 * ...
 * if (spi_reseived_bytes() >= n) {
 *  spi_read(data, n);
 * }
 * ...
 * @endcode
 * 
 * @return The number of received bytes on buffer
 */
void spi_read(uint8_t *bytes, uint8_t length);


#endif /* __SPI */
