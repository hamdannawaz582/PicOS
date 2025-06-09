CC = arm-none-eabi-gcc
CFLAGS = -fpic -nostdlib -mcpu=cortex-m0plus -mthumb
LDFLAGS = -T linkerscript.ld -mcpu=cortex-m0plus -mthumb

SRC = main.c 
OBJ = main.o
OUT = program.elf

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(OUT)

$(OBJ): $(SRC) $(wildcard *.h)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -f *.o $(OUT)