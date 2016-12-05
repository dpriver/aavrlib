#!/bin/bash


program=../build/bin/test/${1}

echo "loading program ${program}"

sudo avrdude -c arduino -p atmega328p -P /dev/cu.usbmodem1411 -b 115200 -C /etc/avrdude/avrdude.conf -U flash:w:${program}

sudo putty -load arduino &> /dev/null
