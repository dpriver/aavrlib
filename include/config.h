/*******************************************************************************
 *	config.h
 *
 *  Aavrlib default configuration
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

#ifndef __CONFIG
#define __CONFIG

#include "boards/arduinoUNO.h"


/* 
 * Timers configuration 
 * 
 * All the library implementations that depend on timers are listed here.
 * 
 * Note that libraries with the same assigned timer should not be used in the same program.
 * Doing so may result in unpredictable results, such as compile or run time errors. Please, if you
 * try to do so, don't feel confident if the compiler ends succesfully, without checking the
 * correctness of the generated code or the program behaviour.
 **/
#define _SOFTPWM_S_TIMER TIMER0
#define _SOFTPWM_L_TIMER TIMER2
#define _SYSTICK_TIMER   TIMER1


/*
 * SPI working mode
 */
//#define SPI_74HC595N
#define SPI_STANDARD


/*
 * LCD_11602a pin configuration
 */

#define RS_PIN PIN_2
#define RW_PIN PIN_3
#define E_PIN PIN_4
//#define D0_PIN PIN_5
//#define D1_PIN PIN_6
//#define D2_PIN PIN_7
//#define D3_PIN PIN_8
#define D4_PIN PIN_9
#define D5_PIN PIN_10
#define D6_PIN PIN_11
#define D7_PIN PIN_12

#define RS_PORT PORT_B
#define RW_PORT PORT_B
#define E_PORT PORT_B
//#define D0_PORT PORT_B
//#define D1_PORT PORT_B
//#define D2_PORT PORT_B
//#define D3_PORT PORT_C
#define D4_PORT PORT_C
#define D5_PORT PORT_C
#define D6_PORT PORT_C
#define D7_PORT PORT_C

#define RS_PORT_V PORT_B_V
#define RW_PORT_V PORT_B_V
#define E_PORT_V PORT_B_V
//#define D0_PORT_V PORT_B_V
//#define D1_PORT_V PORT_B_V
//#define D2_PORT_V PORT_B_V
//#define D3_PORT_V PORT_C_V
#define D4_PORT_V PORT_C_V
#define D5_PORT_V PORT_C_V
#define D6_PORT_V PORT_C_V
#define D7_PORT_V PORT_C_V




#endif /* __CONFIG */
