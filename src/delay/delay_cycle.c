#include "delay.h"
#include "timer.h"

void delay_cycle(){			// A non-interrupt-dependant delay for testing purposes
	uint32_t counter1, counter2;
    for (counter1 = 0; counter1 < 10; counter1++) {
        for (counter2 = 0; counter2 < 6000; counter2++) {
         /* Do nothing */ 
        }
    }
}