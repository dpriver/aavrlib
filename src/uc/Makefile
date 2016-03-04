# Makefile to compile the avr files
#SOURCES=analog.c eeprom.c ioports.c spi.c system.c timers.c twi.c usart.c
SOURCES=timers.c usart.c
HEADERS=analog.h eeprom.h ioports.h spi.h system.h timers.h twi.h usart.h


COBJS=$(SOURCES:%.c=$(LIB_OBJ_DIR)/%.o)
CHEADS=$(HEADERS:%.h=$(HEAD_DIR)/$(AVR_DIR_NAME)/%.h)


all: $(CHEADS) $(COBJS) | $(LIB_BIN_DIR)

$(LIB_OBJ_DIR)/%.o: %.c
	@echo "\tCC" $@
	@$(CC) $(CFLAGS) -o $@ $<

$(COBJS): | $(LIB_OBJ_DIR)

#------------------------------------------------------------------------------------
#		Directories 
#------------------------------------------------------------------------------------
$(LIB_OBJ_DIR):
	@echo "creating dir $(LIB_OBJ_DIR)"
	@mkdir -p $(LIB_OBJ_DIR)

$(LIB_BIN_DIR):
	@echo "creating dir $(LIB_BIN_DIR)"
	@mkdir -p $(LIB_BIN_DIR)
