# Introduction
PicOS is a WIP OS for the Raspberry Pi Pico with plans for porting to other Pico & non-Raspberry Pi boards. At the moment it heavily relies on the Pico SDK but I have plans to remove this in the future.

The name PicOS is a play on the board name Pico and the ultimate goal to load PIC binaries. For information on what currently works and what is planned, check [TODO.md](TODO.md).

This no-sdk version is severely limited compared to the sdk-based one, but the primary reason is I wanted to move towards a microkernel approach, and since this version is a downgrade compared to the main branch I will refrain from merging it until I build a proper microkernel on this approach.

# Compilation & Running
1. Clone the repository
```
git clone https://github.com/hamdannawaz582/PicOS
``` 

2. Install an arm crosscompiler from your OS's package manager, in particular you need
   1. `arm-none-eabi-gcc`
   2. `arm-none-eabi-ld`
   3. `arm-none-eabi-as`
3. Navigate to the project directory
4. Run the following command to compile the project
```
arm-none-eabi-gcc -nostdlib -ffreestanding -mcpu=cortex-m0plus -mthumb -std=gnu11 -Wall -O0 -T linkerscript.ld -mcpu=cortex-m0plus -mthumb *.h *.S OS.c -o OS.elf
```

I realize that this process is very ghetto but I was having trouble getting the Makefile working since my function definitions were in the same file as my declarations. I will fix this at a later date (one that will probably never come).