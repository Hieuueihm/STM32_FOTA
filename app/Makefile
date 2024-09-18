MAIN_DIR = app
START_UP_DIR = ../Startup
SRC_DIR = src
INC_DIR = inc
OPENCM3_DIR = ../libopencm3
LIBNAME = opencm3_stm32f1

OBJ_DIR = Objects
BUILD_DIR = Build

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Source and object files
SOURCES  = ${SRC_DIR}/main.c     
SOURCES += ${START_UP_DIR}/startup_stm32f103c8tx.s
SOURCES += $(filter-out ${SRC_DIR}/main.c, $(wildcard ${SRC_DIR}/*.c)) 
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(patsubst %.s, $(OBJ_DIR)/%.o, $(notdir $(SOURCES))))

# Name for output binary files
PROJECT ?= main

# Compiler, objcopy (should be in PATH)
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# Path to st-flash (or should be specified in PATH)
ST_FLASH ?= /usr/bin/st-flash

# Specify compiler flags
CFLAGS  = -g -O2 -Wall
CFLAGS += -T../STM32F103C8TX_FLASH.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m3 -mthumb-interwork
CFLAGS += -DSTM32F1                   
CFLAGS += -I$(INC_DIR)
CFLAGS += -I$(OPENCM3_DIR)/include
CFLAGS += -Wl,--gc-sections

# Linker and library flags
LDLIBS += -l$(LIBNAME)
LDFLAGS += -L$(OPENCM3_DIR)/lib

FL_ADDR ?= 0x8000000

vpath %.c $(SRC_DIR)
vpath %.s $(START_UP_DIR)

build: $(BUILD_DIR)/$(PROJECT).elf

# Compile and link
$(BUILD_DIR)/$(PROJECT).elf: $(OBJ_DIR) $(BUILD_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).hex
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).bin

$(OBJ_DIR)/%.o: $(START_UP_DIR)/%.s
	$(CC) $(CFLAGS) -c $< -o $@

# Create object files for C source files
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


# Create object files for assembly source files
$(OBJ_DIR)/%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(BUILD_DIR)/*.elf $(BUILD_DIR)/*.bin $(BUILD_DIR)/*.hex

# Flash
flash: $(BUILD_DIR)/$(PROJECT).bin
	sudo $(ST_FLASH) write $(BUILD_DIR)/$(PROJECT).bin ${FL_ADDR}

.PHONY: build clean flash
