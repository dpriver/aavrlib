
#include "delay.h"

/* Delay for the given number of microseconds.  Assumes a 8 or 16 MHz clock. */
void delay_us(uint16_t us)
{
        // calling avrlib's delay_us() function with low values (e.g. 1 or
        // 2 microseconds) gives delays longer than desired.
        //delay_us(us);
        // for the 16 MHz clock on most Arduino boards

        // for a one-microsecond delay, simply return.  the overhead
        // of the function call yields a delay of approximately 1 1/8 us.
        if (--us == 0)
                return;

        // the following loop takes a quarter of a microsecond (4 cycles)
        // per iteration, so execute it four times for each microsecond of
        // delay requested.
        us <<= 2;

        // account for the time taken in the preceeding commands.
        us -= 2;

        // busy wait
        __asm__ __volatile__ (
                "1: sbiw %0,1" "\n\t" // 2 cycles
                "brne 1b" : "=w" (us) : "0" (us) // 2 cycles
        );
}