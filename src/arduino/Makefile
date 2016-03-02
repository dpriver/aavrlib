# Makefile to compile the avr files
SOURCES=
HEADERS=arduinoUNO.h ioports.h


COBJS=$(SOURCES:%.c=$(LIB_OBJ_DIR)/%.o)
CHEADS=$(HEADERS:%.h=$(HEAD_DIR)/arduino/%.h)


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
