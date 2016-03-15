#SOURCES=test_d7seg.c test_d7seg_quad.c test_delay_ms_1.c test_spi_block.c test_spi_burst.c test_ir_receive_nolib.c test_lcd.c test_usart.c test_flame_sensor.c test_micros_bug.c test_ir_send.c
SOURCES=test_pwm.c
HEADERS=

TARGET=$(SOURCES:%.c=$(TEST_BIN_DIR)/%)
COBJS=$(SOURCES:%.c=$(TEST_OBJ_DIR)/%.o)
CHEADS=$(HEADERS:%.h=$(HEAD_DIR)/%.h)

#-------------------------------------------------------------
# Directories
#-------------------------------------------------------------


#-------------------------------------------------------------
# Configuration
#-------------------------------------------------------------

LDLIBS=-laavr



all: $(TARGET)

$(TARGET): $(CHEADS) $(COBJS) | $(TEST_BIN_DIR)

$(COBJS): | $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR)/%.o: %.c
	@echo -e "\tCC" $@
	@$(CC) $(CFLAGS) -o $@ $<

$(TEST_BIN_DIR)/%:
	@echo -e "\tLINKING CC" $@
	@$(CC) -o $@ $(@:$(TEST_BIN_DIR)/%=$(TEST_OBJ_DIR)/%.o) $(LDFLAGS) $(LDLIBS)
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

