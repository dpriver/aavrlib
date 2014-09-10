#====================================================================================================================================
#  Daniel Pinto Rivero	09-08-2014 Cáceres, Spain
#  libaavr project makefile 
#  It's kind of a mess, but it took me a whole day to figure out how to make all this work...
#=====================================================================================================================================

LIB=aavr
LIB_TARGET=$(LIB:%=$(LIB_BIN_DIR)/lib%.a)

#-------------------------------------------------------------
# Directories
#-------------------------------------------------------------
PROJECT_DIR=.
SRC_DIR = $(PROJECT_DIR)/src
TEST_SRC_DIR=$(PROJECT_DIR)/test
BIN_DIR=$(PROJECT_DIR)/bin
LIB_BIN_DIR=$(BIN_DIR)/lib
TEST_BIN_DIR=$(BIN_DIR)/test
HEAD_DIR=$(PROJECT_DIR)/include
OBJ_DIR=$(PROJECT_DIR)/temp
LIB_OBJ_DIR=$(OBJ_DIR)/lib
TEST_OBJ_DIR=$(OBJ_DIR)/test

#-------------------------------------------------------------
# Library files
#-------------------------------------------------------------
SOURCES=timer.c delay.c spi.c d7seg.c
HEADERS=$(SOURCES:%.c=$(HEAD_DIR)/%.h)
TARGET=
COBJ=$(SOURCES:%.c=$(OBJ_DIR)/%.o)
DEPS=

#-------------------------------------------------------------
# Test files
#-------------------------------------------------------------
TEST_SOURCES=test_delay_ms_1.c test_spi_block.c test_spi_burst.c test_d7seg.c test_d7seg_quad.c
TEST_TARGETS=$(TEST_SOURCES:%.c=$(TEST_BIN_DIR)/%)
TEST_COBJ=$(TEST_SOURCES:%.c=$(OBJ_DIR)/%.o)
TEST_DEPS=$(BIN_DIR)/$(TARGET)

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
MCU=atmega328p
FREQ=16000000
VARIABLES=F_CPU=$(FREQ) SPI_TEST=1 DISPLAY_FYQ5641BS
export CDEFINES=$(VARIABLES:%=-D%) 
CFLAGS=-I$(HEAD_DIR) -Wall -Os -std=gnu99  -mmcu=$(MCU) -c $(CDEFINES)
LDFLAGS=-L$(LIB_BIN_DIR)
LDLIBS=
STRIPFLAGS=--strip-debug
ISPPORT=/dev/ttyACM0
ISPCONF=/etc/avrdude/avrdude.conf
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
	@echo -e "========= RULES ========================================================================"
	@echo -e "- help			-> prints this help"
	@echo -e "- all			-> compile everything (aavr library and tests)"
	@echo -e "- force_all		-> force the compilation of everything"
	@echo -e "- lib			-> compile aavr library"
	@echo -e "- tests			-> compile tests (and avr for dependancy, just the same as \"all\")"
	@echo -e "- clean			-> remove binary and temporary files"
	@echo -e "- read			-> read the loaded program in the avr device"
	@echo -e "- write_test_%		-> load the especified program test "test_%" in the avr device\n"


all: lib tests

force_all: clean all

lib: timer delay spi d7seg
	@echo -e "\tARCHIVING " $(LIB_TARGET)
	@$(STRIP) $(STRIPFLAGS) -g $(LIB_OBJ_DIR)/*
	@$(AR) rcsv $(LIB_TARGET) $(LIB_OBJ_DIR)/*
	@$(RANLIB) $(LIB_TARGET)

tests:
	@$(MAKE) -C test all

timer:
	@$(MAKE) -C src/timer all

spi:
	@$(MAKE) -C src/spi all

delay:
	@$(MAKE) -C src/delay all

d7seg:
	@$(MAKE) -C src/d7seg all


clean: clean_bin clean_temp

clean_bin:
	@echo -e "========= cleanup ========"
	@echo "removing binaries..."
	@rm -rf $(BIN_DIR)
	@mkdir $(BIN_DIR)
	@mkdir $(TEST_BIN_DIR)

clean_temp:
	@echo -e "removing temporary files"
	@rm -rf $(OBJ_DIR)
	@mkdir $(OBJ_DIR)

read:
	@echo -e "Reading device flash"
	@$(ISP) $(ISPFLAGS) -U flash:r:$(TARGET)_backup.hex:i

write_test_%: $(BIN_DIR)/test/test_%
	@echo -e "writing program '$<' to device flash"
	@sudo $(ISP) $(ISPFLAGS) -U flash:w:$<.hex

libinstall: lib
	@echo -e "not implemented"