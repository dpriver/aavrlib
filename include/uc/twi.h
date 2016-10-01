/*******************************************************************************
 *	twi.h
 *
 *  TWI/I2C related definitions and functions
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


#ifndef __TWI
#define __TWI

#include <avr/io.h>
#include <stdint.h>
#include <util/twi.h>



#define TWI_WRITE TW_WRITE
#define TWI_READ  TW_READ

void TWI_master_init();

void TWI_slave_init(uint8_t addr);

int8_t TWI_do_start();

int8_t TWI_do_send_addr(uint8_t slave_addr, uint8_t twi_operation);

int8_t TWI_do_write(uint8_t byte);

int8_t TWI_do_read(uint8_t *byte);

// send data as master
int8_t TWI_send(uint8_t slave_addr, const uint8_t* data, uint8_t data_lenght);

// Receive data as master
int8_t TWI_receive(uint8_t slave_addr, uint8_t* data, uint8_t data_lenght);


int8_t TWI_release();



#endif /* __TWI */
