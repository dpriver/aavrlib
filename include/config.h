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

#include "ioport.h"

// A board header file can be used
#include "boards/arduinoUNO.h"


/*====================================================================
 *   TIMERS
 *====================================================================*/
/*
 * All the library implementations that depend on timers are listed here.
 * 
 * Note that libraries with the same assigned timer should not be used in the same program.
 * Doing so may result in unpredictable results, such as compile or run time errors. Please, if you
 * try to do so, don't feel confident if the compiler ends succesfully, without checking the
 * correctness of the generated code or the program behaviour.
 */
#define _SOFTPWM_S_TIMER TIMER1
#define _SOFTPWM_L_TIMER TIMER2
#define _SYSTICK_TIMER   TIMER0

/*====================================================================
 *   INFRARED
 *====================================================================*/
// uncomment if IR NEC "extended" protocol is used.
// If the ir_NEC library is not used, this definition can be ignored
#define IR_NEC_EXTENDED



// Configuration for the case when a board has been defined and included
// PIN definitions from the board header file should be used
#ifdef __USE_BOARD

/*====================================================================
 *   SPI configuration
 *====================================================================*/
    #define _SPI_BUFF_SIZE (1<<8)

/*====================================================================
 *   LCD_11602A peripheral configuration
 *====================================================================*/
    #define _RS_PIN          PIN_2
    #define _RW_PIN          PIN_3
    #define _E_PIN           PIN_4
    #define _DATA_PIN_LOW    PIN_9

    
/*====================================================================
 *   Usable definitions (DO NOT EDIT, AUTOMATICALLY CONFIGURED)
 *====================================================================*/
    // SPI
    #define SPI_BUFF_SIZE _SPI_BUFF_SIZE
 
    // LCD_11602A peripheral    
    #define RS_PIN          REAL_PIN(_RS_PIN)
    #define RW_PIN          REAL_PIN(_RW_PIN)
    #define E_PIN           REAL_PIN(_E_PIN)
    #define DATA_PIN_LOW    REAL_PIN(_DATA_PIN_LOW)

    #define RS_PORT         PORT(_RS_PIN)
    #define RW_PORT         PORT(_RW_PIN)
    #define E_PORT          PORT(_E_PIN)
    #define DATA_PORT       PORT(_DATA_PIN_LOW)
    
    
// Configurations for the case when NO board is defined
// Definitions from ioport.h or avr/io.h should be used
#else

/*====================================================================
 *   SPI configuration
 *====================================================================*/
    #define _SPI_BUFF_SIZE (1<<8)

/*====================================================================
 *   LCD_11602A peripheral configuration
 *====================================================================*/*/
    #define _RS_PIN          // Not configured
    #define _RW_PIN          // Not configured
    #define _E_PIN           // Not configured
    #define _DATA_PIN_LOW    // Not configured

    #define _RS_PORT    // Not configured
    #define _RW_PORT    // Not configured
    #define _E_PORT     // Not configured
    #define _DATA_PORT  // Not configured


/*====================================================================
 *   Usable definitions (DO NOT EDIT, AUTOMATICALLY CONFIGURED)
 *====================================================================*/
    // SPI
    #define SPI_BUFF_SIZE _SPI_BUFF_SIZE
 
    // LCD_11602A peripheral
    #define RS_PIN          _RS_PIN
    #define RW_PIN          _RW_PIN
    #define E_PIN           _E_PIN
    #define DATA_PIN_LOW    _DATA_PIN_LOW

    #define RS_PORT         _RS_PORT
    #define RW_PORT         _RW_PORT
    #define E_PORT          _E_PORT
    #define DATA_PORT       _DATA_PORT

#endif



#endif /* __CONFIG */
