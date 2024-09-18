# Be silent per default, but 'make V=1' will show all compiler calls.
ifneq ($(V),1)
Q		:= @
NULL		:= 2>/dev/null
endif

SRC_DIR        = src
INC_DIR        = inc
OPENCM3_DIR    = ../libopencm3

OBJ_DIR        = Objects
BUILD_DIR      = Build

BINARY = main

###############################################################################
# Basic Device Setup

LIBNAME			= opencm3_stm32f1
DEFS				+= -DSTM32F1
ARCH_FLAGS	= -mthumb -mcpu=cortex-m4

###############################################################################
# Linkerscript

LDSCRIPT = ../linkerscript.ld
LDLIBS		+= -l$(LIBNAME)
LDFLAGS		+= -L$(OPENCM3_DIR)/lib

###############################################################################
# Includes

DEFS		+= -I$(OPENCM3_DIR)/include
DEFS		+= -I$(INC_DIR)

###############################################################################
# Executables

PREFIX		?= arm-none-eabi-

CC		:= $(PREFIX)gcc
CXX		:= $(PREFIX)g++
LD		:= $(PREFIX)gcc
AR		:= $(PREFIX)ar
AS		:= $(PREFIX)as
OBJCOPY		:= $(PREFIX)objcopy
OBJDUMP		:= $(PREFIX)objdump
GDB		:= $(PREFIX)gdb
STFLASH		= $(shell which st-flash)
OPT		:= -Os
DEBUG		:= -ggdb3
CSTD		?= -std=c99


###############################################################################
# Source files

SRCS		= $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))

###############################################################################
# C flags

TGT_CFLAGS	+= $(OPT) $(CSTD) $(DEBUG)
TGT_CFLAGS	+= $(ARCH_FLAGS)
TGT_CFLAGS	+= -Wextra -Wshadow -Wimplicit-function-declaration
TGT_CFLAGS	+= -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes
TGT_CFLAGS	+= -fno-common -ffunction-sections -fdata-sections

###############################################################################
# C++ flags

TGT_CXXFLAGS	+= $(OPT) $(CXXSTD) $(DEBUG)
TGT_CXXFLAGS	+= $(ARCH_FLAGS)
TGT_CXXFLAGS	+= -Wextra -Wshadow -Wredundant-decls  -Weffc++
TGT_CXXFLAGS	+= -fno-common -ffunction-sections -fdata-sections

###############################################################################
# C & C++ preprocessor common flags

TGT_CPPFLAGS	+= -MD
TGT_CPPFLAGS	+= -Wall -Wundef
TGT_CPPFLAGS	+= $(DEFS)

###############################################################################
# Linker flags

TGT_LDFLAGS		+= --static -nostartfiles
TGT_LDFLAGS		+= -T$(LDSCRIPT)
TGT_LDFLAGS		+= $(ARCH_FLAGS) $(DEBUG)
TGT_LDFLAGS		+= -Wl,-Map=$(BUILD_DIR)/$(BINARY).map -Wl,--cref
TGT_LDFLAGS		+= -Wl,--gc-sections
ifeq ($(V),99)
TGT_LDFLAGS		+= -Wl,--print-gc-sections
endif

###############################################################################
# Used libraries

LDLIBS		+= -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

###############################################################################
# Directories creation

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

###############################################################################
# Targets

ST_FLASH ?= /usr/bin/st-flash
FL_ADDR ?= 0x8000000

.PHONY: build clean flash
clean:
	$(Q)rm -rf $(OBJ_DIR) $(BUILD_DIR)

build: $(BUILD_DIR)/$(BINARY).elf $(BUILD_DIR)/$(BINARY).bin

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(Q)$(OBJCOPY) -Obinary $< $@
$(BUILD_DIR)/%.elf: $(OBJS) $(LDSCRIPT) $(OPENCM3_DIR)/lib/lib$(LIBNAME).a | $(BUILD_DIR)
	$(Q)$(LD) $(TGT_LDFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(Q)$(CC) $(TGT_CFLAGS) $(CFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) -o $@ -c $<



flash: $(BUILD_DIR)/$(BINARY).bin
	sudo $(ST_FLASH) write $< ${FL_ADDR}
