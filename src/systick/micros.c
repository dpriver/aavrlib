#include "systick.h"
#include <avr/interrupt.h>


// Here i try to correct a race condition in which current_tick and TCNT1
// finish with weird values resulting in 1ms-less fault
// it's based on a bug-fix for a similar problem in SAM arquitecture:
// http://forum.arduino.cc/index.php/topic,162787.0/topicseen.html

// I was trying to evade this kind of iterative looking-for-a-proper-value
// solution, but after 2 days of trial-error and study, i can't find something
// better, and this seems to work... (without a lot of cpu time, which is nice...)
uint32_t micros(){
	uint16_t current_tick, tick_2, current_count, count_2;
	//uint8_t extra;
	//uint8_t extra_2;
	uint8_t oldSREG = SREG;

	sei();
	tick_2 = system_tick.current_tick;
	count_2 = TCNT1;
//	extra_2 = (TIFR1 & _BV(OCF1A)) && (current_count < 0xFFFF);

	do{
		current_tick = tick_2;
		current_count = count_2;
		//extra = extra_2;
		tick_2 = system_tick.current_tick;
		count_2 = TCNT1;
		//extra_2 = (TIFR1 & _BV(OCF1A)) && (current_count < 0xFFFF);
	} while ( (current_tick!=tick_2) /*|| (extra!=extra_2) || tick_2 < current_tick*/);

/*
	if( extra ){
		current_tick++;
	}
*/

	SREG = oldSREG;
	return (uint32_t)current_tick*1000 + (uint32_t)(current_count>>1);
}

/*
// Original SAM solution
uint32_t micros(void )
{
    uint32_t ticks, ticks2;
    uint32_t pend, pend2;
    uint32_t count, count2;

    ticks2  = SysTick->VAL;
    pend2   = !!((SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)||((SCB->SHCSR & SCB_SHCSR_SYSTICKACT_Msk)))  ;
    count2  = GetTickCount();

    do {
        ticks=ticks2;
        pend=pend2;  
        count=count2;
        ticks2  = SysTick->VAL;
        pend2   = !!((SCB->ICSR & SCB_ICSR_PENDSTSET_Msk)||((SCB->SHCSR & SCB_SHCSR_SYSTICKACT_Msk)))  ;
        count2  = GetTickCount();
    } while ((pend != pend2) || (count != count2) || (ticks < ticks2));

    return ((count+pend) * 1000) + (((SysTick->LOAD  - ticks)*(1048576/(F_CPU/1000000)))>>20) ;
} 


*/