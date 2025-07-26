BOARD := RPi-Pico

CC := arm-none-eabi-gcc
LD := arm-none-eabi-ld

CFLAGS := -nostdlib -ffreestanding -mcpu=cortex-m0plus -mthumb -std=gnu11 -Wall -I./include
ASFLAGS := -mcpu=cortex-m0plus -mthumb -ffreestanding -nostdlib
LDFLAGS := -Tsrc/board/$(BOARD)/linker.ld -nostdlib

SRC_C := $(shell find src/init src/kernel src/util src/board/$(BOARD) src/driver -name '*.c')
TEST_C := $(shell find tests -name '*.c')
SRC_ASM := $(shell find src/board/$(BOARD)/*.S)
OBJ_C := $(patsubst src/%.c, build/%.o, $(SRC_C))
TEST_OBJ_C := $(patsubst tests/%.c, build/%.o, $(TEST_C))
OBJ_ASM := $(patsubst src/%.S, build/%.o, $(SRC_ASM))

OBJS := $(OBJ_C) $(OBJ_ASM) $(TEST_OBJ_C)

OUT := kernel.elf

all: $(OUT)

$(OUT): $(OBJ_C) $(OBJ_ASM) $(TEST_OBJ_C)
	@echo "[LD] $@"
	$(LD) $(LDFLAGS) -o $@ $^

build/%.o: src/%.c
	@echo "[CC] $<"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: tests/%.c
	@echo "[TEST] $<"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: src/%.S
	@echo "[ASM] $<"
	@mkdir -p $(dir $@)
	$(CC) $(ASFLAGS) -c $< -o $@

clean:
	rm -rf build/ $(OUT)

.PHONY: all clean