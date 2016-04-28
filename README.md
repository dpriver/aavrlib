# AAVRLIB
![](https://travis-ci.org/Kuronogard/aavrlib.svg?branch=master)

AVR microcontrollers code library.

## About
This library, whose original name comes from "Arduino AVR Library", was aimed to program the Arduino included microcontrollers in pure C. Specifically, the atmega328p packaged in the Arduino UNO.

By now, the objective is to create a general AVR library, with functionality to handle whatever variety of boards, in particular the Arduino ones. 

### Suported μcontrollers
* atmega328p


### Suported boards
* Arduino UNO


### Functionality
* digital and analog I/O
* timers (ctc, pwm,...)
* spi
* usart

### Peripherals
* None


## Compilation
To compile the project, cmake is used, so the following commands should be executed in the project directory
```bash
mkdir build
cd build

cmake ..
make
```
