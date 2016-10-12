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


/**
 * @file twi.h
 * @author Dennis Pinto Rivero
 * @date 2016
 * @brief TWI/I2C functionality implementation
 */

#ifndef __TWI
#define __TWI

#include <stdbool.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/twi.h>


/*==============================================================================
 *      TWI constants and types
 *==============================================================================
 */

/**
 * @brief TWI/I2C posible working modes
 */
typedef enum {
    TWI_DISABLED = 0,   //!< TWI/I2C disabled 
    TWI_MASTER,         //!< TWI/I2C working as master device
    TWI_SLAVE           //!< TWI/I2C working as slave device
} twi_operation_mode;

/**
 * @brief TWI/I2C operation states
 */
typedef enum {
    TWI_SUCCESS = 0,    //!< TWI/I2C operation finished succesfully
    TWI_ERROR = -1      //!< TWI/I2C operation finished in error
} twi_state;

/**
 * @brief TWI/I2C posible operations
 */
typedef enum {
    TWI_WRITE = TW_WRITE,   //!< TWI/I2C write operation
    TWI_READ = TW_READ      //!< TWI/I2C read operation
} twi_operation_t;




/*==============================================================================
 *      TWI functions
 *==============================================================================
 */ 
 
/**
 * @brief Init TWI/I2C subsystem as a master device
 */
void TWI_master_init();


/**
 * @brief Init TWI/I2C subsystem as a slave device
 * 
 * @param addr The slave address of this device
 */
void TWI_slave_init(uint8_t addr);


/**
 * @brief Check if there was an error in the last TWI operation
 * 
 * @param error_code The TWI error code
 * @return Returns a boolean value to indicate if there was an error
 */
bool TWI_has_error(uint8_t *error_code);


/**
 * @brief To do a TWI start operation
 * 
 * @return Returns the finish state of the TWI operation
 */
twi_state TWI_do_start();


/**
 * @brief To do a TWI send address operation
 * 
 * @param slave_addr The slave device address
 * @param twi_operation The TWI operation to perform (write or read)
 * @return Returns the finish state of the TWI operation
 */
twi_state TWI_do_send_addr(uint8_t slave_addr, twi_operation_t twi_operation);


/**
 * @brief To do a TWI write operation
 * 
 * @param byte The byte to send through TWI
 * @return Returns the finish state of the TWI operation
 */
twi_state TWI_do_write(uint8_t byte);


/**
 * @brief To do a TWI read operation
 * 
 * @param byte The variable to store the read byte
 * @return Returns the finish state of the TWI operation
 */
twi_state TWI_do_read(uint8_t *byte);


/**
 * @brief Send data though TWI as master
 * 
 * @param slave_addr The slave device address
 * @param data A pointer to the data array to send thought TWI
 * @param data_length The number of bytes to send
 * @return Returns the finish state of the TWI operation
 */
twi_state TWI_send(uint8_t slave_addr, const uint8_t* data, uint8_t data_length);


/**
 * @brief Receive data through TWI as master
 * 
 * @param slave_addr The slave device address
 * @param data A pointer to store the data received from TWI
 * @param data_length The number of bytes to receive
 * @return Returns the finish state of the TWI operation
 */
twi_state TWI_receive(uint8_t slave_addr, uint8_t* data, uint8_t data_length);


/**
 * @brief Release the TWI channel so other devices can use it.
 */
void TWI_release();


#endif /* __TWI */
