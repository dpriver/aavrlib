SOURCES=test_d7seg.c test_d7seg_quad.c test_delay_ms_1.c test_spi_block.c test_spi_burst.c test_ir_receive_nolib.c test_lcd.c test_usart.c
HEADERS=

TARGET=$(SOURCES:%.c=$(TEST_BIN_DIR)/%)
COBJS=$(SOURCES:%.c=$(TEST_OBJ_DIR)/%.o)
CHEADS=$(HEADERS:%.h=$(HEAD_DIR)/%.h)

#-------------------------------------------------------------
# Directories
#-------------------------------------------------------------
PROJECT_DIR=..
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
MCU=atmega328p 
FREQ=16000000
CFLAGS=-I$(HEAD_DIR) -Wall -Os -std=gnu99  -mmcu=$(MCU) -c $(CDEFINES)
LDFLAGS=-L$(LIB_BIN_DIR)
LDLIBS=-laavr
STRIPFLAGS=--strip-debug



all: $(TARGET)

$(TARGET): $(CHEADS) $(COBJS) | $(TEST_BIN_DIR)

$(COBJS): | $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR)/%.o: %.c
	@echo -e "\tCC" $@
	@$(CC) $(CFLAGS) -o $@ $<

$(TEST_BIN_DIR)/%:
	@echo -e "\tLINKING CC" $@
	@$(CC) -mmcu=$(MCU) -o $@ $(@:$(TEST_BIN_DIR)/%=$(TEST_OBJ_DIR)/%.o) $(LDFLAGS) $(LDLIBS)
	@$(OBJC) -O ihex -R .eeprom $@ $@.hex
	@$(OBJC) -O binary -R .eeprom $@ $@.bin

#------------------------------------------------------------------------------------
#		Directories 
#------------------------------------------------------------------------------------
$(TEST_OBJ_DIR):
	@echo -e "creating dir $(TEST_OBJ_DIR)"
	@mkdir -p $(TEST_OBJ_DIR)

$(TEST_BIN_DIR):
	@echo -e "creating dir $(TEST_BIN_DIR)"
	@mkdir -p $(TEST_BIN_DIR)

