CC = arm-none-eabi-gcc
CFLAGS = -fpic -nostdlib
LDFLAGS = -T linkerscript.ld 

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