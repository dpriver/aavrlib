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

#define MPU_60X0_I2C_ADDRESS    (0x34 << 1)


/* Chip Registers */
#define MPU_60X0_SAMPLE_RATE_DIVIDER_REG    (25)
#define MPU_60X0_CONFIG_REG                 (26)
#define MPU_60X0_GYRO_CONFIG_REG            (27)
#define MPU_60X0_ACCEL_CONFIG_REG           (28)
#define MPU_60X0_FIFO_ENABLE_REG            (35)
#define MPU_60X0_I2C_MASTER_CTL_REG         (36)
#define MPU_60X0_I2C_SLAVE0_CTL_REG         (37)
#define MPU_60X0_I2C_SLAVE1_CTL_REG         (40)
#define MPU_60X0_I2C_SLAVE2_CTL_REG         (43)
#define MPU_60X0_I2C_SLAVE3_CTL_REG         (46)
#define MPU_60X0_I2C_SLAVE4_CTL_REG         (49)
#define MPU_60X0_I2C_MASTER_STATUS_REG      (54)
#define MPU_60X0_INT_CONFIG_REG             (55)
#define MPU_60X0_INT_ENABLE_REG             (56)
#define MPU_60X0_INT_STATUS_REG             (58)
#define MPU_60X0_ACCEL_DATA_REG             (59)
#define MPU_60X0_GYRO_DATA_REG              (65)
#define MPU_60X0_TEMP_DATA_REG              (67)
#define MPU_60X0_EXTERN_DATA_REG            (73)
#define MPU_60X0_I2C_SLAVE0_DATA_REG        (99)
#define MPU_60X0_I2C_SLAVE1_DATA_REG        (100)
#define MPU_60X0_I2C_SLAVE2_DATA_REG        (101)
#define MPU_60X0_I2C_SLAVE3_DATA_REG        (102)
#define MPU_60X0_I2C_MASTER_DELAY_CTL_REG   (103)
#define MPU_60X0_SIG_PATH_RESET_REG         (104)
#define MPU_60X0_USER_CTL_REG               (106)
#define MPU_60X0_POWER1_REG                 (107)
#define MPU_60X0_POWER2_REG                 (108)
#define MPU_60X0_FIFO_COUNT_REG             (114)
#define MPU_60X0_FIFO_DATA_REG              (116)
#define MPU_60X0_WHO_AM_I_REG               (117)



typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t z;
} mpu_60x0_gyro_data;

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t z;  
} mpu_60x0_accel_data;

typedef struct {
    uint16_t temp;
} mpu_60x0_temp_data;



/* Configure all the chip registers to use the on-chip FIFO so this driver can 
 * burst read the FIFO register instead of reading all the registers 
 * secuentially */
void mpu_60x0_init(void);

uint8_t mpu_60x0_read_gyro(mpu_60x0_gyro_data* data);

/* Read the accel registers */
uint8_t mpu_60x0_read_accel(mpu_60x0_accel_data* data);

/* Read the temp registers */
uint8_t mpu_60x0_read_temp(mpu_60x0_temp_data* data);


#endif /* __MPU_60X0 */
