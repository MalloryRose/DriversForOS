# DOS Drivers Project

## Overview
Low-level mouse and VGA drivers for DOS environment

## Setup
- Tools: Open Watcom C/C++
- Platform: DOSBox
- Mode: x86 Real Mode

## Project Structure
drivers/
├── Makefile
├── mouse.h     # Mouse driver interface
├── vga.h       # VGA driver interface
└── tests.c     # Test program

## Build Instructions
```bash
# Compile library
cd drivers
wmake

# Compile test program
wcl tests.c drivers/drivers.lib -ml
