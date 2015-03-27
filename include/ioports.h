
#ifndef _IOPORTS_
#define _IOPORTS_

#include <avr/io.h>

/*
avr atmega manual specifies the following prohibitions

DDxn 	PORTxn 	DDxn(t+1) 	PORTxn(t+1)
0		0		1			1			"tri-state" to "output high" 		->	illegal
0		1		1			0			"input with pullup" to "output low" ->  illegal

In the first case, {DDxn, PORTxn} must pass through 01 or 10 ("input with pullup" or "output low")
In the second case, {DDxn, PORTxn} must pass through 00 or 11 ("tri-state" or "output high")

At reset, all ports are tri-stated {DDxn, PORTxn}=00
*/



#endif