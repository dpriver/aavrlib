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
* long pulse software PWM (~0-100% duty at 200Hz)
* short pulse software PWM (~0-10% duty at 50Hz)

### Peripherals
* HC-SR04 ultrasonic sensor


## Dependencies
Note that this library is based on Atmel's avr library, and aimed to avr microcontrollers, so cross compile is needed.
Make sure you have installed avr-libc and avr build tools.

If that is not the case, the following commands can be used in a debian based system to install them.
```bash
sudo apt-get update
sudo apt-get install gcc-avr avr-libc
```


## Compilation
To compile the project, cmake is used, so the following commands should be executed in the project directory
```bash
mkdir build
cd build

cmake ..
make
```

## Installation
To install the library, the following command should be used in the project's build directory after compilation
```bash
make install
```

## Use
Once installed, to use this library, the flag -laavr has to be included in compiler invocation, as any other library.
