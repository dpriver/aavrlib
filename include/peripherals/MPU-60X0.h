/*******************************************************************************
 *	MPU-60x0.h
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

#ifndef __MPU_60X0
#define __MPU_60X0


#define MPU60X0_SENS_RANGE  (3)
#define MPU60X0_DLPF        (5)
#define MPU60X0_SMP_DIV     (2)

#define MPU60X0_I2C_ADDR    (0x68)


/* MPU60X0 Register */
#define MPU60X0_REG_ACCEL_BIASX     (0x06)
#define MPU60X0_REG_ACCEL_BIASY     (0x08)
#define MPU60X0_REG_ACCEL_BIASZ     (0x0A)
#define MPU60X0_REG_GYRO_BIASX      (0x13)
#define MPU60X0_REG_GYRO_BIASY      (0x15)
#define MPU60X0_REG_GYRO_BIASZ      (0x17)
#define MPU60X0_REG_SELF_TEST       (13)
#define MPU60X0_REG_SAMPLE_RATE     (25)
#define MPU60X0_REG_CONFIG          (26)
#define MPU60X0_REG_GYRO_CONF       (27)
#define MPU60X0_REG_ACCEL_CONF      (28)
#define MPU60X0_REG_FIFO_EN         (35)
#define MPU60X0_REG_I2C_MASTER_CTL  (36)
#define MPU60X0_REG_I2C_SLAVE0_CTL  (37)
#define MPU60X0_REG_I2C_SLAVE1_CTL  (40)
#define MPU60X0_REG_I2C_SLAVE2_CTL  (43)
#define MPU60X0_REG_I2C_SLAVE3_CTL  (46)
#define MPU60X0_REG_I2C_SLAVE4_CTL  (49)
#define MPU60X0_REG_MASTER_STATUS   (54)
#define MPU60X0_REG_INT_CONF        (55)
#define MPU60X0_REG_INT_EN          (56)
#define MPU60X0_REG_INT_STATUS      (58)
#define MPU60X0_REG_I2C_SLAVE0_DATA     (99)
#define MPU60X0_REG_I2C_SLAVE1_DATA     (100)
#define MPU60X0_REG_I2C_SLAVE2_DATA     (101)
#define MPU60X0_REG_I2C_SLAVE3_DATA     (102)
#define MPU60X0_REG_I2C_MASTER_DELAY    (103)
#define MPU60X0_REG_SIG_PATH_RST    (104)
#define MPU60X0_REG_USER_CTL        (106)
#define MPU60X0_REG_POWER1          (107)
#define MPU60X0_REG_POWER2          (108)
#define MPU60X0_REG_FIFO_COUNT      (114)
#define MPU60X0_REG_FIFO_DATA       (116)
#define MPU60X0_REG_WHO_AM_I        (117)

#define MPU60X0_REG_ACCEL_DATA      (59)
#define MPU60X0_REG_GYRO_DATA       (67)
#define MPU60X0_REG_TEMP_DATA       (65)
#define MPU60X0_REG_EXTERN_DATA     (73)



typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} mpu_60x0_gyro_data;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;  
} mpu_60x0_accel_data;


typedef struct {
    mpu_60x0_accel_data accel;
    mpu_60x0_gyro_data gyro;
} mpu_60x0_data;

typedef struct {
    int16_t temp;
} mpu_60x0_temp_data;



/* Configure all the chip registers to use the on-chip FIFO so this driver can 
 * burst read the FIFO register instead of reading all the registers 
 * secuentially */
int8_t mpu60x0_init(void);

int8_t mpu60x0_read_reg(uint8_t reg, uint8_t *data, uint8_t length);

int8_t mpu60x0_write_reg(uint8_t reg, uint8_t *data, uint8_t length);

int16_t mpu60x0_read_fifo(mpu_60x0_data *data, uint16_t length);

uint8_t mpu60x0_read_gyro(mpu_60x0_gyro_data* data);

/* Read the accel registers */
uint8_t mpu60x0_read_accel(mpu_60x0_accel_data* data);

/* Read the temp registers */
uint8_t mpu60x0_read_temp(mpu_60x0_temp_data* data);


#endif /* __MPU_60X0 */
