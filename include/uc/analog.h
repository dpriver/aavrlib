/*******************************************************************************
 *	analog.h
 *
 *  analog comparator and converter
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
 ********************************************************************************/

#ifndef __ANALOG
#define __ANALOG

#include <stdint.h>
#include <avr/io.h>

// ADC prescaler values (determines the speed at which the conversion is made)
// single conversion: 13 ADC cycles
// burst conversions : first 25, nexts 13.5 ADC cycles
typedef enum {
	adc_presc_2 = 1,
	adc_presc_4 = 2,
	adc_presc_8 = 3,
	adc_presc_16 = 4,
	adc_presc_32 = 5,
	adc_presc_64 = 6,
	adc_presc_128 = 7
} adc_prescaler_t;

// ADC reference voltaje values (Vref)
// - aref uses the Aref input
// - vcc uses Vcc
// - internal uses an internal ref of 1.1v
typedef enum {
	adc_ref_aref = 0,
	adc_ref_vcc = 1,
	adc_ref_internal = 3
} adc_reference_t;

// ADC usable channels
// - a0-a6 external analog pins
// - temperature internal temperature sensor
// - internal internal 1.1v source Vbg
typedef enum {
	adc_channel_a0 = 0,
	adc_channel_a1 = 1,
	adc_channel_a2 = 2,
	adc_channel_a3 = 3,
	adc_channel_a4 = 4,
	adc_channel_a5 = 5,
	adc_channel_temperature = 8,
	adc_channel_internal = 14,
	adc_channel_gnd = 15
} adc_channel_t;


#define MSK_CH0 _BV(ADC0D)
#define MSK_CH1 _BV(ADC1D)
#define MSK_CH2 _BV(ADC2D)
#define MSK_CH3 _BV(ADC3D)
#define MSK_CH4 _BV(ADC4D)
#define MSK_CH5 _BV(ADC5D)


/*
 * Initialize the analog-to-digital conversor
 */
void adc_init(adc_prescaler_t prescaler, adc_reference_t ref,
		adc_channel_t channel, uint8_t pinmask);

/*
 * Change the input channel
 */
void adc_change_channel(adc_channel_t channel);

/*
 * Performs a single analog read
 */
uint8_t adc_single_read();

#endif /* __ANALOG */
