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

#include "uc/usart.h"
#include <util/twi.h>
#include <util/delay.h>
#include "uc/twi.h"
#include "peripherals/MPU-60X0.h"
#include "uc/usart.h"


#define BIAS_ACCELX -304
#define BIAS_ACCELY -20
#define BIAS_ACCELZ -90

#define BIAS_GYROX 13
#define BIAS_GYROY -85
#define BIAS_GYROZ -112

int8_t mpu60x0_read_reg(uint8_t reg, uint8_t *data, uint8_t length) {
    int8_t twi_res;
    
    if (length == 0) {
        return 0;
    }
    
    twi_res = TWI_send(MPU60X0_I2C_ADDR, &reg, 1);
    if (twi_res != 0)
        return twi_res;

    twi_res = TWI_receive(MPU60X0_I2C_ADDR, data, length);
    TWI_release();
    
    return twi_res;
}

int8_t mpu60x0_write_reg(uint8_t reg, uint8_t *data, uint8_t length) {
    uint8_t i = 0;
    
    if (TWI_do_start() != 0)
        return -1;
    
    if (TWI_do_send_addr(MPU60X0_I2C_ADDR, TWI_WRITE) != 0)
        return -1;
        
    if (TWI_do_write(reg) != 0)
        return -1;
        
    while( i < length) {
        if (TWI_do_write(data[i]) != 0)
            return -1;
        i++;
    }
    TWI_release();
    
    return 0;
}

int8_t mpu60x0_reset() {
    uint8_t data;
    
    // fifo and sensor path reset
    data = 0x05;
    if (mpu60x0_write_reg(MPU60X0_REG_USER_CTL, &data, 1) != 0)
        return -1;

    // fifo enable
    data = 0x40;
    if (mpu60x0_write_reg(MPU60X0_REG_USER_CTL, &data, 1) != 0)
        return -1;
    if (mpu60x0_read_reg(MPU60X0_REG_USER_CTL, &data, 1) != 0)
        return -1;
    if (data != 0x40)
        return 8;
        
    return 0;
}

/*
 * Configure to use FIFO and maybe some interrupts
 * 
 */
int8_t mpu60x0_init(uint8_t gyro_scale_range, uint8_t accel_scale_range, 
                    uint8_t smp_div) {
    uint8_t aux;
    
    TWI_master_init();
    
    /* Check the chip's identity */
    mpu60x0_read_reg(MPU60X0_REG_WHO_AM_I, &aux, 1);
    if (aux != MPU60X0_I2C_ADDR) {
        return -1;  /* Failed to verify the chip's identity */
    }
    
    
    /* MPU6050 configuration
     *
     * The default value for all the registers is 0x00 except for:
     * Register 117 (WHO_AM_I) = 0x68
     * Register 107 (POWER1) = 0x40 
     */

    uint8_t data;

    // reset registers to defaults
    data = 0x80;
    mpu60x0_write_reg(MPU60X0_REG_POWER1, &data, 1);

    _delay_ms(100);


    data = 0x01;
    if (mpu60x0_write_reg(MPU60X0_REG_POWER1, &data, 1) != 0)
        return -1;
    if (mpu60x0_read_reg(MPU60X0_REG_POWER1, &data, 1) != 0)
        return -1;
    if (data != 0x01)
        return 1;

    // Digital Low Pass Filter (DLPF)
    data = MPU60X0_DLPF & 0x7;
    if (mpu60x0_write_reg(MPU60X0_REG_CONFIG, &data, 1) != 0)
        return -1;
    if (mpu60x0_read_reg(MPU60X0_REG_CONFIG, &data, 1) != 0)
        return -1;
    if (data != (MPU60X0_DLPF & 0x7))
        return 3;

    // sample rate
    if (mpu60x0_write_reg(MPU60X0_REG_SAMPLE_RATE, &smp_div, 1) != 0) 
        return -1;
    if (mpu60x0_read_reg(MPU60X0_REG_SAMPLE_RATE, &data, 1) != 0)
        return -1;
    if (data != smp_div)
        return 2;

    // gyroscope scale range
    if (mpu60x0_write_reg(MPU60X0_REG_GYRO_CONF, &gyro_scale_range, 1) != 0) 
        return -1;
    if (mpu60x0_read_reg(MPU60X0_REG_GYRO_CONF, &data, 1) != 0)
        return -1;
    if (data != gyro_scale_range)
        return 4;
        
    // accelerometer scale range
    if (mpu60x0_write_reg(MPU60X0_REG_ACCEL_CONF, &accel_scale_range, 1) != 0)
        return -1;
    if (mpu60x0_read_reg(MPU60X0_REG_ACCEL_CONF, &data, 1) != 0)
        return -1;
    if (data != accel_scale_range)
        return 5;
    
    // fifo enabled for gyro and accel
    data = 0x78;
    if (mpu60x0_write_reg(MPU60X0_REG_FIFO_EN, &data, 1) != 0)
        return -1;
    if (mpu60x0_read_reg(MPU60X0_REG_FIFO_EN, &data, 1) != 0)
        return -1;
    if (data != 0x78)
        return 6;

    //// fifo and sensor path reset
    //data = 0x05;
    //if (mpu60x0_write_reg(MPU60X0_REG_USER_CTL, &data, 1) != 0)
        //return -1;

    //// fifo enable
    //data = 0x40;
    //if (mpu60x0_write_reg(MPU60X0_REG_USER_CTL, &data, 1) != 0)
        //return -1;
    //if (mpu60x0_read_reg(MPU60X0_REG_USER_CTL, &data, 1) != 0)
        //return -1;
    //if (data != 0x40)
        //return 8;
    
    return 0;
}



/* Read the fifo */
int16_t mpu60x0_read_fifo(mpu_60x0_data *data, uint16_t length) {
    uint16_t fifo_count = 0;
    uint8_t i = 0;

    // get the number of data values in fifo

    if (mpu60x0_read_reg(MPU60X0_REG_FIFO_COUNT, (uint8_t *)&fifo_count, 2) != 0) {
        return -1;
    }
    
    fifo_count = (fifo_count << 8) | (fifo_count >> 8);
    fifo_count /= 12;
    
    // adjust the length of the data to read
    length = (length < fifo_count)? length : fifo_count;

    if (mpu60x0_read_reg(MPU60X0_REG_FIFO_DATA, (uint8_t *)data, 12*length) != 0) {
        return -2;
    }

    while (i < length) {
     
        data[i].gyro.x = (data[i].gyro.x << 8) | ((uint16_t)data[i].gyro.x >> 8);
        data[i].gyro.y = (data[i].gyro.y << 8) | ((uint16_t)data[i].gyro.y >> 8);
        data[i].gyro.z = (data[i].gyro.z << 8) | ((uint16_t)data[i].gyro.z >> 8);

        data[i].accel.x = (data[i].accel.x << 8) | ((uint16_t)data[i].accel.x >> 8);
        data[i].accel.y = (data[i].accel.y << 8) | ((uint16_t)data[i].accel.y >> 8);
        data[i].accel.z = (data[i].accel.z << 8) | ((uint16_t)data[i].accel.z >> 8);
        
        i++;
    }
    
    return length;
}

/* Read the gyro registers */
uint8_t mpu60x0_read_gyro(mpu_60x0_gyro_data* data) {
    uint8_t twi_res;

    twi_res = mpu60x0_read_reg(MPU60X0_REG_GYRO_DATA, (uint8_t *)data, 6);
    
    data->x = (data->x << 8) | ((uint16_t)data->x >> 8);
    data->y = (data->y << 8) | ((uint16_t)data->y >> 8);
    data->z = (data->z << 8) | ((uint16_t)data->z >> 8);
    
    return twi_res;
}

/* Read the accel registers */
uint8_t mpu60x0_read_accel(mpu_60x0_accel_data* data) {
    uint8_t twi_res;

    twi_res = mpu60x0_read_reg(MPU60X0_REG_ACCEL_DATA, (uint8_t *)data, 6);
    
    data->x = (data->x << 8) | ((uint16_t)data->x >> 8);
    data->y = (data->y << 8) | ((uint16_t)data->y >> 8);
    data->z = (data->z << 8) | ((uint16_t)data->z >> 8);
    
    return twi_res;
}

/* Read the temp registers */
uint8_t mpu60x0_read_temp(mpu_60x0_temp_data* data) {
    uint8_t twi_res;

    twi_res = mpu60x0_read_reg(MPU60X0_REG_TEMP_DATA, (uint8_t *)data, 2);
    
    data->temp = (data->temp << 8) | ((data->temp >> 8) & 0xFF);
    data->temp = data->temp/340 + 36;
    
    return twi_res;
}

uint8_t mpu60x0_get_gyro_bias(mpu_60x0_bias *data) {
    uint8_t twi_res;
    
    twi_res = mpu60x0_read_reg(MPU60X0_REG_GYRO_BIASX, (uint8_t *)data, 6);

 
    data->x = (data->x << 8) | ((uint16_t)data->x >> 8);
    data->y = (data->y << 8) | ((uint16_t)data->y >> 8);
    data->z = (data->z << 8) | ((uint16_t)data->z >> 8);
    
    return twi_res;
}

uint8_t mpu60x0_get_accel_bias(mpu_60x0_bias *data) {
    uint8_t twi_res;
    
    twi_res = mpu60x0_read_reg(MPU60X0_REG_ACCEL_BIASX, (uint8_t *)data, 6);
    
    data->x = (data->x << 8) | ((uint16_t)data->x >> 8);
    data->y = (data->y << 8) | ((uint16_t)data->y >> 8);
    data->z = (data->z << 8) | ((uint16_t)data->z >> 8);
    
    return twi_res;   
    
}

/*
 * Accel bias is specified in +-8G format, and gyro bias in +-1000dps format.
 * because of that, It is convenient to read the data for calibration in 
 * AFS_SEL = 2.
 */


/*
 * Input is LSB in +-8G format
 */
uint8_t mpu60x0_set_accel_bias(int16_t x_bias, int16_t y_bias, int16_t z_bias) {
    uint8_t curr_bias[6];
    uint8_t data[6];
    uint8_t i2c_status;
    
    mpu60x0_read_reg(MPU60X0_REG_ACCEL_BIASX, (uint8_t*)curr_bias, 6);
    
    
    // high byte is first in mpu60x0
    // preserve first bit of the 3 low bytes
    data[0] = (uint16_t)x_bias >> 8;
    data[1] = (x_bias & 0xFE) | (curr_bias[1] & 0x1);
    data[2] = (uint16_t)y_bias >> 8;
    data[3] = (y_bias & 0xFE) | (curr_bias[3] & 0x1);
    data[4] = (uint16_t)z_bias >> 8;
    data[5] = (z_bias & 0xFE) | (curr_bias[5] & 0x1);

    i2c_status = mpu60x0_write_reg(MPU60X0_REG_ACCEL_BIASX, data, 6);
    
    return i2c_status;
}

/*
 * Input is LSB in +-1000dps format
 */
uint8_t mpu60x0_set_gyro_bias(int16_t x_bias, int16_t y_bias, int16_t z_bias) {
    uint8_t data[6];
    uint8_t i2c_status;
    
    // high byte is first in mpu60x0
    data[0] = (uint16_t)x_bias >> 8;
    data[1] = x_bias & 0xff;
    data[2] = (uint16_t)y_bias >> 8;
    data[3] = y_bias & 0xff;
    data[4] = (uint16_t)z_bias >> 8;
    data[5] = z_bias & 0xff;

    i2c_status = mpu60x0_write_reg(MPU60X0_REG_GYRO_BIASX, data, 6);
    
    return i2c_status;
}

