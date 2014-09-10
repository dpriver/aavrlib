LIB=delay
SOURCES=delay_cycle.c delay_ms.c
HEADERS=delay.h

COBJS=$(SOURCES:%.c=$(LIB_OBJ_DIR)/%.o)
CHEADS=$(HEADERS:%.h=$(HEAD_DIR)/%.h)

#-------------------------------------------------------------
# Directories
#-------------------------------------------------------------
PROJECT_DIR=../..
SRC_DIR=$(PROJECT_DIR)/src
TEST_SRC_DIR=$(PROJECT_DIR)/test
BIN_DIR=$(PROJECT_DIR)/bin
HEAD_DIR=$(PROJECT_DIR)/include
OBJ_DIR=$(PROJECT_DIR)/temp
LIB_BIN_DIR=$(BIN_DIR)/lib
TEST_BIN_DIR=$(BIN_DIR)/test
LIB_OBJ_DIR=$(OBJ_DIR)/lib
TEST_OBJ_DIR=$(OBJ_DIR)/test

#-------------------------------------------------------------
# Configuration
#-------------------------------------------------------------


#-------------------------------------------------------------
# Configuration
#-------------------------------------------------------------
MCU=atmega328p 
FREQ=16000000
CFLAGS=-I$(HEAD_DIR) -Wall -std=gnu99  -mmcu=$(MCU) -c $(CDEFINES)
LDFLAGS=-L$(LIB_BIN_DIR)
LDLIBS=-laavr
STRIPFLAGS=--strip-debug


all: $(CHEADS) $(COBJS) | $(LIB_BIN_DIR)

$(LIB_OBJ_DIR)/%.o: %.c
	@echo -e "\tCC" $@
	@$(CC) $(CFLAGS) -o $@ $<

$(COBJS): | $(LIB_OBJ_DIR)

#------------------------------------------------------------------------------------
#		Directories 
#------------------------------------------------------------------------------------
$(LIB_OBJ_DIR):
	@echo -e "creating dir $(LIB_OBJ_DIR)"
	@mkdir -p $(LIB_OBJ_DIR)

$(LIB_BIN_DIR):
	@echo -e "creating dir $(LIB_BIN_DIR)"
	@mkdir -p $(LIB_BIN_DIR)