/*******************************************************************************
 *	MPU-60x0.c
 *
 *  MPU-60X0 gyroscope-accelerometer sensor
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

#include <util/twi.h>
#include "uc/twi.h"
#include "peripherals/MPU-60X0.h"


/*
 * Configure to use FIFO and maybe some interrupts
 * 
 */
void mpu_60x0_init(void) {
    
    TWI_master_init();
}

/* Read the gyro registers */
uint8_t mpu_60x0_read_gyro(mpu_60x0_gyro_data* data) {
    uint8_t twi_res;
    
    // start a transmission to
    twi_res = TWI_receive(MPU_60X0_I2C_ADDRESS, (uint8_t *)data, 6);
    TWI_release();
    
    return twi_res;
}

/* Read the accel registers */
uint8_t mpu_60x0_read_accel(mpu_60x0_accel_data* data) {
    uint8_t twi_res;

    twi_res = TWI_receive(MPU_60X0_I2C_ADDRESS, (uint8_t *)data, 6);
    TWI_release();
    
    return twi_res;
}

/* Read the temp registers */
uint8_t mpu_60x0_read_temp(mpu_60x0_temp_data* data) {
    uint8_t twi_res;

    twi_res = TWI_receive(MPU_60X0_I2C_ADDRESS, (uint8_t *)data, 2);
    TWI_release(); 
    
    return twi_res;
}
