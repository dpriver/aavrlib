/*******************************************************************************
 *	interrupt.c
 *
 *  interrupt management
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

#include <avr/interrupt.h>
#include "uc/interrupt.h"
#include "uc/usart.h"

#define N_INTERRUPTS 25


void default_ISR(interrupt_t interrupt) {
    usart_print("\nERROR: not implemented int");
    usart_printnumber32(interrupt);
}

isr_function isr[N_INTERRUPTS] = {
    default_ISR, default_ISR, default_ISR, default_ISR, default_ISR, 
    default_ISR, default_ISR, default_ISR, default_ISR, default_ISR, 
    default_ISR, default_ISR, default_ISR, default_ISR, default_ISR, 
    default_ISR, default_ISR, default_ISR, default_ISR, default_ISR, 
    default_ISR, default_ISR, default_ISR, default_ISR, default_ISR
    };


void interrupt_attach(interrupt_t interrupt, isr_function new_isr) {
    isr[interrupt] = new_isr;
}

void interrupt_detach(interrupt_t interrupt) {
    isr[interrupt] = default_ISR;
}


// ISR vectors

ISR(INT0_vect, ISR_BLOCK) {
    isr[INT0_int](INT0_int);
}

ISR(INT1_vect, ISR_BLOCK) {
    isr[INT1_int](INT1_int);    
}

ISR(PCINT0_vect, ISR_BLOCK) {
    isr[PCINT0_int](PCINT0_int);
}

ISR(PCINT1_vect, ISR_BLOCK) {
    isr[PCINT1_int](PCINT1_int);
}

ISR(PCINT2_vect, ISR_BLOCK) {
    isr[PCINT2_int](PCINT2_int);
}

ISR(WDT_vect, ISR_BLOCK) {
    isr[WDT_int](WDT_int);
}

ISR(TIMER2_COMPA_vect, ISR_BLOCK) {
    isr[TIMER2_COMPA_int](TIMER2_COMPA_int);
}

ISR(TIMER2_COMPB_vect, ISR_BLOCK) {
    isr[TIMER2_COMPB_int](TIMER2_COMPB_int);
}

ISR(TIMER2_OVF_vect, ISR_BLOCK) {
    isr[TIMER2_OVF_int](TIMER2_OVF_int);
}

ISR(TIMER1_CAPT_vect, ISR_BLOCK) {
    isr[TIMER1_CAPT_int](TIMER1_CAPT_int);
}

ISR(TIMER1_COMPA_vect, ISR_BLOCK) {
    isr[TIMER1_COMPA_int](TIMER1_COMPA_int);
}

ISR(TIMER1_COMPB_vect, ISR_BLOCK) {
    isr[TIMER1_COMPB_int](TIMER1_COMPB_int);
}

ISR(TIMER1_OVF_vect, ISR_BLOCK) {
    isr[TIMER1_OVF_int](TIMER1_OVF_int);
}

ISR(TIMER0_COMPA_vect, ISR_BLOCK) {
    isr[TIMER0_COMPA_int](TIMER0_COMPA_int);
}

ISR(TIMER0_COMPB_vect, ISR_BLOCK) {
    isr[TIMER0_COMPB_int](TIMER0_COMPB_int);
}

ISR(TIMER0_OVF_vect, ISR_BLOCK) {
    isr[TIMER0_OVF_int](TIMER0_OVF_int);
}

ISR(SPI_STC_vect, ISR_BLOCK) {
    isr[SPI_STC_int](SPI_STC_int);
}

ISR(USART_RX_vect, ISR_BLOCK) {
    isr[USART_RX_int](USART_RX_int);
}

ISR(USART_UDRE_vect, ISR_BLOCK) {
    isr[USART_UDRE_int](USART_UDRE_int);
}

ISR(USART_TX_vect, ISR_BLOCK) {
    isr[USART_TX_int](USART_TX_int);
}

ISR(ADC_vect, ISR_BLOCK) {
    isr[ADC_int](ADC_int);
}

ISR(EE_READY_vect, ISR_BLOCK) {
    isr[EE_READY_int](EE_READY_int);
}

ISR(ANALOG_COMP_vect, ISR_BLOCK) {
    isr[ANALOG_COMP_int](ANALOG_COMP_int);
}

ISR(TWI_vect, ISR_BLOCK) {
    isr[TWI_int](TWI_int);
}

ISR(SPM_READY_vect, ISR_NOBLOCK) {
    isr[SPM_READY_int](SPM_READY_int);
}
