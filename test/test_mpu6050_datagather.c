/*******************************************************************************
 *  test_mpu6050.c
 *
 *  test fo the mpu6050 munted on the GY521 board
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
 *******************************************************************************/

#include <util/delay.h>
#include <util/twi.h>
#include <boards/arduinoUNO.h>
#include <uc/system.h>
#include <uc/usart.h>
#include <peripherals/MPU-60X0.h>
#include <systick.h>
#include <time.h>

#define GYROX_OFFSET (-9)
#define GYROY_OFFSET (11)
#define GYROZ_OFFSET (-14)
//#define ACCELX_OFFSET (1057 - 2048)
//#define ACCELY_OFFSET (15)
//#define ACCELZ_OFFSET (-142)

#define ACCELX_OFFSET (0)
#define ACCELY_OFFSET (-24)
#define ACCELZ_OFFSET (-105)

#define ABS(a) ( ((a) < 0) ? -(a) : (a))

int main( void ) {
    //mpu_60x0_gyro_data gyro_data;
    //mpu_60x0_accel_data accel_data;
    //mpu_60x0_temp_data temp_data;
    mpu_60x0_data mpu_data[100];
    uint8_t twi_error;
    int16_t read_values = 0;
    
    system_init();
    systick_init();
    usart_init();
    
    delay_ms(100);
    if ((twi_error = mpu60x0_init()) != 0) {
        usart_print("#MPU6050 is not working... CODE: ");
        usart_printnumber8(twi_error);
        return 0;
    }
    else {
        usart_print("# MPU6050 TEST\n#\n");
        usart_print("# Initialized mpu6050\n");
        usart_print("# Gyro and Accel Sensibility: ");
        usart_printnumber8(MPU60X0_SENS_RANGE);
        usart_print("\n# DLPF: ");
        usart_printnumber8(MPU60X0_DLPF);
        usart_print("\n# Sample Rate Divider: ");
        usart_printnumber8(MPU60X0_SMP_DIV);
    }

    
    
    //usart_print("System initialized\n======================\n");
    //usart_print("    MPU6050 test\n=======================\n");

    
    // wait 30 seconds to stabilice the sensors
    delay_ms(30000);

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
        
    
    usart_print("\n#\n# TIME      GYROx       GYROy       GYROx       ACCELx");
    usart_print("      ACCELy      ACCELz\n");
    
    time_t time;
    //uint16_t time_ms = 0;
    
    get_uptime(&time);
    
    // gather data for 10 seconds
    uint16_t end_time = time.ms + 10000;
    while(time.ms < end_time) {
        uint16_t i = 0;
        
        read_values = mpu60x0_read_fifo(mpu_data, 100);
        
        if (read_values < 0 ) {
            usart_print("Error ");
            usart_printsignumber32(read_values);
            usart_print("\n");
            continue;     
        }    
        //else {
            //usart_print("\n");
            //usart_printnumber32(read_values);
            //usart_print(" values read");
        //}
    
        //twi_error = mpu60x0_read_gyro(&gyro_data);
        //if (twi_error != 0) {
            //usart_print("Error");
        //}
        //twi_error = mpu60x0_read_accel(&accel_data);
        //if (twi_error != 0) {
            //usart_print("Error");
        //}
        //twi_error = mpu60x0_read_temp(&temp_data);
        //if (twi_error != 0) {
            //usart_print("Error");
        //}
        
        for (i = 0 ; i < read_values ; i++) {
            usart_print("\n");
            usart_printnumber32(time.ms);
            
            usart_print(" ");
            usart_printsignumber32(mpu_data[i].gyro.x - GYROX_OFFSET);
            usart_print(" ");
            usart_printsignumber32(mpu_data[i].gyro.y - GYROY_OFFSET);
            usart_print(" ");
            usart_printsignumber32(mpu_data[i].gyro.z - GYROZ_OFFSET);
            
            usart_print(" ");
            usart_printsignumber32(mpu_data[i].accel.x - ACCELX_OFFSET);
            usart_print(" ");
            usart_printsignumber32(mpu_data[i].accel.y - ACCELY_OFFSET);
            usart_print(" ");
            usart_printsignumber32(mpu_data[i].accel.z - ACCELZ_OFFSET);
            
            //usart_print(" ");
            //usart_printnumber32(time.ms);
            //time_ms += 4; 
        }        

        
        //usart_print(" ");
        //usart_printsignumber32(temp_data.temp);
        
        //delay_ms(1000);
        get_uptime(&time);
    }
    
    while(1);
    
    
    return 0;
}
