LIB=timer
SOURCES=ms_prescale.c
HEADERS=timer.h

TARGET=$(LIB_BIN_DIR)/lib$(LIB).a
COBJS=$(SOURCES:%.c=$(LIB_OBJ_DIR)/$(LIB)/%.o)
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
VARIABLES=F_CPU=$(FREQ)
CDEFINES=$(VARIABLES:%=-D%) 
CFLAGS=-I$(HEAD_DIR) -Wall -Os -std=gnu99  -mmcu=$(MCU) -c $(CDEFINES)
LDFLAGS=-L$(BIN_DIR)
LDLIBS=
STRIPFLAGS=--strip-debug



all: $(TARGET)

$(TARGET): $(CHEADS) $(COBJS) | $(LIB_BIN_DIR)
	@echo -e "\tARCHIVING CC" $(COBJS)
	@$(STRIP) $(STRIPFLAGS) -g $(COBJS)
	@$(AR) rcsv $@ $(COBJS)
	@$(RANLIB) $@


$(LIB_OBJ_DIR)/$(LIB)/%.o: %.c
	@echo -e "\tCC" $@
	@$(CC) $(CFLAGS) -o $@ $<

$(COBJS): | $(LIB_OBJ_DIR)/$(LIB)

#------------------------------------------------------------------------------------
#		Directories 
#------------------------------------------------------------------------------------
$(LIB_OBJ_DIR)/$(LIB):
	@echo -e "creating dir $(LIB_OBJ_DIR)/$(LIB)"
	@mkdir -p $(LIB_OBJ_DIR)/$(LIB)

$(LIB_BIN_DIR): $(BIN_DIR)
	@echo -e "creating dir $(LIB_BIN_DIR)"
	@mkdir -p $(LIB_BIN_DIR)
