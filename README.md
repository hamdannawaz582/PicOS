# Introduction
PicOS is a WIP OS for the Raspberry Pi Pico with plans for porting to other Pico & non-Raspberry Pi boards. At the moment it heavily relies on the Pico SDK but I have plans to remove this in the future.

The name PicOS is a play on the board name Pico and the ultimate goal to load PIC binaries. For information on what currently works and what is planned, check [TODO.md](TODO.md).

# Compilation & Running
1. Clone the repository
```
git clone https://github.com/hamdannawaz582/PicOS
``` 

2. Follow the instructions listed in the official [Raspberry Pi Pico Getting Started Guide](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf) to install the Pico SDK and flash the image onto your Raspberry Pi Pico.

#### Note: This is temporary and will move to a cross-compiler + Makefile in the future