#====================================================================================================================================
#  Daniel Pinto Rivero	09-08-2014 Cáceres, Spain
#  libaavr project makefile 
#  It's kind of a mess, but it took me a whole day to figure out how to make all this work...
#=====================================================================================================================================

#-------------------------------------------------------------
# Directories
#-------------------------------------------------------------
SRC_DIR=src
TEST_SRC_DIR=test
BIN_DIR=bin
TEST_BIN_DIR=$(BIN_DIR)/test
HEAD_DIR=include
TEMP_DIR=temp

#-------------------------------------------------------------
# Library files
#-------------------------------------------------------------
SOURCES=timer.c delay.c spi.c d7seg.c
HEADERS=$(SOURCES:%.c=$(HEAD_DIR)/%.h)
TARGET=libaavr.a
COBJ=$(SOURCES:%.c=$(TEMP_DIR)/%.o)
DEPS=

#-------------------------------------------------------------
# Test files
#-------------------------------------------------------------
TEST_SOURCES=test_delay_ms_1.c test_spi_block.c test_spi_burst.c test_d7seg.c
TEST_TARGETS=$(TEST_SOURCES:%.c=$(TEST_BIN_DIR)/%)
TEST_COBJ=$(TEST_SOURCES:%.c=$(TEMP_DIR)/%.o)
TEST_DEPS=$(BIN_DIR)/$(TARGET)

#-------------------------------------------------------------
# Programs
#-------------------------------------------------------------
CC=avr-gcc
AS=avr-as
AR=avr-ar
RANLIB=avr-ranlib
STRIP=avr-strip
OBJC=avr-objcopy
ISP=avrdude

#-------------------------------------------------------------
# Configuration
#-------------------------------------------------------------
MCU=atmega328p
FREQ=16000000
VARIABLES=F_CPU=$(FREQ) SPI_TEST=2
CDEFINES=$(VARIABLES:%=-D%) 
CFLAGS=-I. -Iinclude/ -Wall $(CDEFINES) -std=gnu99
LDFLAGS=-L$(BIN_DIR)
LDLIBS=-laavr
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

lib: $(BIN_DIR)/$(TARGET)

tests: $(TEST_TARGETS)

$(TEST_TARGETS): $(TEST_COBJ) | $(TEST_BIN_DIR)
	@echo -e "\tLINKING CC" $(@:$(TEST_BIN_DIR)/%=$(TEMP_DIR)/%.o)
	@$(CC) -mmcu=$(MCU) -o $@ $(@:$(TEST_BIN_DIR)/%=$(TEMP_DIR)/%.o) $(LDFLAGS) $(LDLIBS)
	@$(OBJC) -O ihex -R .eeprom $@ $@.hex
	@$(OBJC) -O binary -R .eeprom $@ $@.bin


$(TEST_COBJ): $(TEST_SOURCES:%=$(TEST_SRC_DIR)/%) $(BIN_DIR)/$(TARGET) | $(TEMP_DIR)
	@echo -e "\tCC" $(@:$(TEMP_DIR)/%.o=$(TEST_SRC_DIR)/%.c)
	@$(CC) -mmcu=$(MCU) -c -o $@ $(@:$(TEMP_DIR)/%.o=$(TEST_SRC_DIR)/%.c) $(CFLAGS)

$(COBJ): $(SOURCES:%=$(SRC_DIR)/%) $(HEADERS) $(DEPS) | $(TEMP_DIR)
	@echo -e "\tCC" $(@:$(TEMP_DIR)/%.o=$(SRC_DIR)/%.c)
	@$(CC) -mmcu=$(MCU) -c -o $@ $(@:$(TEMP_DIR)/%.o=$(SRC_DIR)/%.c) $(CFLAGS)

$(BIN_DIR)/$(TARGET): $(COBJ) | $(BIN_DIR)
	@echo -e "\tARCHIVING CC" $(COBJ)
	@$(STRIP) -g $(COBJ)
	@$(AR) rcsv $@ $(COBJ)
	@$(RANLIB) $@

clean: clean_bin clean_temp

clean_bin:
	@echo -e "========= cleanup ========"
	@echo "removing binaries..."
	@rm -rf $(BIN_DIR)
	@mkdir $(BIN_DIR)
	@mkdir $(TEST_BIN_DIR)

clean_temp:
	@echo -e "removing temporary files"
	@rm -rf $(TEMP_DIR)
	@mkdir $(TEMP_DIR)

read:
	@echo -e "Reading device flash"
	@$(ISP) $(ISPFLAGS) -U flash:r:$(TARGET)_backup.hex:i

write_test_%: $(BIN_DIR)/test/test_%
	@echo -e "writing program '$<' to device flash"
	@sudo $(ISP) $(ISPFLAGS) -U flash:w:$<.hex

libinstall: lib
	@echo -e "not implemented"

$(BIN_DIR):
	@echo -e "creating bin directory"
	@mkdir $(BIN_DIR)

$(TEST_BIN_DIR): | $(BIN_DIR)
	@echo -e "creating test bin directory"
	@mkdir $(TEST_BIN_DIR)

$(TEMP_DIR):
	@echo -e "creating temp directory"
	@mkdir $(TEMP_DIR)