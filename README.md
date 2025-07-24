# Introduction
PicOS is a WIP OS for the Raspberry Pi Pico with plans for porting to other Pico & non-Raspberry Pi boards. This repository is for the kernel of the OS.

The name PicOS is a play on the board name Pico and the ultimate goal to load PIC binaries. For information on what currently works and what is planned, check [TODO.md](TODO.md).

This branch covers the shift to a microkernel approach for this OS, this is meant to be the canonical branch for the OS going forward. The previous monolithic kernel branches are incomplete and will likely never be completed. The microkernel approach is meant to be more modular and easier to maintain, allowing for better future development.

# Compilation & Running
1. Clone the repository
```
git clone https://github.com/hamdannawaz582/PicOS
``` 

2. Install an arm crosscompiler from your OS's package manager, in particular you need
   1. `arm-none-eabi-gcc`
   2. `arm-none-eabi-ld`
   3. `arm-none-eabi-as`
