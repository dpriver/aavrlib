/*******************************************************************************
 *	usart.h
 *
 *  usart
 *
 *
 *  This file is part of aavrlib
 * 
 *  Copyright (C) 2015  Dennis Pinto Rivero
 *  Copyright (C) 2016  Germán Castaño Roldán
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


/**
 * @file usart.h
 * 
 * @brief USART functionality
 */

// BAUD = Fose/16/(UBBR0+1)
// setting of baud rate UBRR0=103=0x67 9600 baud rate
// setting of baud rate UBRR0=3=0x03   250k baud rate
// setting the frame format 1bit-stop 8bit-data
// enable transmitter or receiver


#ifndef _USART
#define _USART

#include <avr/io.h>
#include <avr/power.h>
#include <stdint.h>
#include "uc/interrupt.h"


typedef enum{
  bitrate_300 = 3332,
  bitrate_600 = 1665,
  bitrate_1200 = 832,
  bitrate_1800 = 554,
  bitrate_2400 = 416,
  bitrate_3600 = 276,
  bitrate_4800 = 207,
  bitrate_7200 = 137,
  bitrate_9600 = 103,
  bitrate_14400 = 68,
  bitrate_19200 = 51,
  bitrate_28800 = 34,
  bitrate_38400 = 25,
  bitrate_57600 = 16,
  bitrate_115200 = 8,
  bitrate_230400 = 3,//error 8.5%
  bitrate_500K = 1,
  bitrate_1M = 0
}usart_bitrate_t;


#define USART_PENDING_BYTE() (UDR0)

#define IS_BYTE_PENDING() (UCSR0A &  (1 <<RXC0))

/**
 * @brief Init usart functionality
 * 
 * This function must be called once before using any other usart functions
 */
void usart_init(usart_bitrate_t bitrate);


/**
 * @brief Enable USART receive interrupt trigger
 * 
 * @param recv_handler The ISR function to be invoqued for USART_RX 
 * interrupt. recv_handler must read the pending value 
 * (i.e. Using UART_PENDING_BYTE()) in order to clean the receive flag.
 * If not, the interrupt would be triggered again just after finishing.
 */
void usart_set_recv_handler(isr_function recv_handler);


/**
 * @brief Disable UART receive interrupt trigger
 * 
 */
void usart_rem_recv_handler();


/**
 * @brief Send a byte of data via USART
 * 
 * @param data_byte The byte to send
 */
void usart_send(uint8_t data_byte);


/**
 * @brief Print an 8 bit unsigned number
 * 
 * @param number The number to print
 */
void usart_printnumber8(uint8_t number);


/**
 * @brief Print an 32 bit unsigned number
 * 
 * @param number The number to print
 */
void usart_printnumber32(uint32_t number);


/**
 * @brief Print an 32 bit signed number
 * 
 * @param number The number to print
 */
void usart_printsignumber32(int32_t number);


/**
 * @brief Print a string ended in '\0'
 * 
 * @param string The string to print
 */
void usart_print(const char* string);



#endif
