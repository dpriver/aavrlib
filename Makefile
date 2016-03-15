#====================================================================================================================================
#  Daniel Pinto Rivero	09-08-2014 Cáceres, Spain
#  libaavr project makefile 
#=====================================================================================================================================

LIB=aavr
LIB_TARGET=$(LIB:%=$(LIB_BIN_DIR)/lib%.a)

#-------------------------------------------------------------
# Directories
#-------------------------------------------------------------
export AVR_DIR_NAME=uc
export ARDUINO_DIR_NAME=arduino
export PERIPH_DIR_NAME=peripherals
export TEST_DIR_NAME=test

export PROJECT_DIR := $(shell pwd)

export SRC_DIR := $(PROJECT_DIR)/src

export BIN_DIR=$(PROJECT_DIR)/bin
export LIB_BIN_DIR=$(BIN_DIR)/lib
export TEST_BIN_DIR=$(BIN_DIR)/test

export HEAD_DIR=$(PROJECT_DIR)/include

export OBJ_DIR=$(PROJECT_DIR)/temp
export LIB_OBJ_DIR=$(OBJ_DIR)/lib
export TEST_OBJ_DIR=$(OBJ_DIR)/test


#-------------------------------------------------------------
# Installation prefix
#-------------------------------------------------------------
PREFIX=/usr/local/lib
LIB_INSTALL_DIR=$(PREFIX)/aavrlib

#-------------------------------------------------------------
# Programs
#-------------------------------------------------------------
export CC=avr-gcc
export AS=avr-as
export AR=avr-ar
export RANLIB=avr-ranlib
export STRIP=avr-strip
export OBJC=avr-objcopy
export ISP=avrdude

#-------------------------------------------------------------
# Configuration
#-------------------------------------------------------------
export MCU=atmega328p
export FREQ=16000000
export VARIABLES=F_CPU=$(FREQ)
export CDEFINES=$(VARIABLES:%=-D%)
export CFLAGS=-Os -flto -fuse-linker-plugin -Wpedantic -I$(HEAD_DIR) -Wall -std=gnu99 -mmcu=$(MCU) -c $(CDEFINES)
export LDFLAGS=-Os -flto -fuse-linker-plugin -L$(LIB_BIN_DIR)
#export CFLAGS=-O0 -Wpedantic -I$(HEAD_DIR) -Wall -std=gnu99 -mmcu=$(MCU) -c $(CDEFINES)
#export LDFLAGS=-O0 -L$(LIB_BIN_DIR)
export LDLIBS=
export STRIPFLAGS=--strip-debug

ISPPORT=/dev/ttyACM0
ISPCONF=/etc/avrdude.conf
ISPFLAGS=-c arduino -p $(MCU) -P $(ISPPORT) -b 115200 -C $(ISPCONF)


#-------------------------------------------------------------
# Rules
#-------------------------------------------------------------

#-------------------------------------------------------------
# The expected rules to be manually used are
#	- all			-> compile everything (aavr library and tests)
#	- force_all		-> force the compilation of everything"
#	- lib 			-> compile aavr library
#	- tests 		-> compile tests (and avr for dependancy, just the same as "all")
#	- clean 		-> remove binary and temporary files
#	- read 			-> read the loaded program in the avr device
#	- write_test_% 	-> load the especified program test in the avr device
#-------------------------------------------------------------

help:
	@echo "========= RULES ========================================================================"
	@echo "- help			-> prints this help"
	@echo "- all			-> compile everything (aavr library and tests)"
	@echo "- force_all		-> force the compilation of everything"
	@echo "- lib			-> compile aavr library"
	@echo "- tests			-> compile tests (and avr for dependancy, just the same as \"all\")"
	@echo "- clean			-> remove binary and temporary files"
	@echo "- read			-> read the loaded program in the avr device"
	@echo "- write_test_%		-> load the especified program test "test_%" in the avr device\n"


all: lib tests

force_all: clean all

lib:
	@$(MAKE) -C src lib --no-print-directory
	@echo "\tARCHIVING " $(LIB_TARGET)
	@$(STRIP) $(STRIPFLAGS) -g $(LIB_OBJ_DIR)/*
	@$(AR) rcsv $(LIB_TARGET) $(LIB_OBJ_DIR)/*
	@$(RANLIB) $(LIB_TARGET)

tests:
	@$(MAKE) -C src tests

clean: clean_bin clean_temp

clean_bin:
	@echo "========= cleanup ========"
	@echo "removing binaries..."
	@rm -rf $(BIN_DIR)
	@mkdir $(BIN_DIR)

clean_temp:
	@echo "removing temporary files"
	@rm -rf $(OBJ_DIR)
	@mkdir $(OBJ_DIR)

read:
	@echo "Reading device flash"
	@$(ISP) $(ISPFLAGS) -U flash:r:$(TARGET)_backup.hex:i

write_test_%: $(BIN_DIR)/test/test_%
	@echo "writing program '$<' to device flash"
	@sudo $(ISP) $(ISPFLAGS) -U flash:w:$<.hex
	#@sudo putty -load arduino_serial &

open_serial:
	@sudo putty -load arduino_serial &

install: lib
	@sudo mkdir $(LIB_INSTALL_DIR)
	@sudo mkdir $(LIB_INSTALL_DIR)/lib
	@sudo cp $(LIB_TARGET) $(LIB_INSTALL_DIR)/lib
	@sudo cp -r $(HEAD_DIR) $(LIB_INSTALL_DIR)

uninstall:
	@sudo rm -r $(LIB_INSTALL_DIR)
