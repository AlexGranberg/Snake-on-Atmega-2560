# Snake-on-Atmega-2560

# Snake Game README

This README provides an overview of the Snake Game code contained in multiple source files.

## Overview

The Snake Game is implemented in C for an AVR microcontroller, and it uses an LED matrix for display. The game logic, 
display functions, and user controls are distributed across several source files to maintain code organization and readability.


## Hardware

This project assumes the use of an AVR microcontroller, in this case the Atmega2560, an LED matrix controlled by the MAX7219 driver, 
a joystick for user input, and a UART module for serial communication.

<img width="743" alt="Skärmbild 2023-09-20 095442" src="https://github.com/AlexGranberg/Snake-on-Atmega-2560/assets/42450559/f77f5705-1f6e-458e-ae41-7ce4b248db7b">

## Getting Started

To use this code, you need to set up your hardware accordingly and flash it onto an AVR microcontroller. Additionally, you may 
need to install an AVR development environment (such as AVR-GCC) and program your microcontroller using a suitable programmer.

You could also test it out on wokwi: https://wokwi.com/projects/367313440995520513

Inside the max72xx.c file there are two variants of the function void max7219b_out(void), one is for physical and one for simulation.
Needed to get the orientation of the led matrix in order.

Please refer to the individual source files for more details on the functions and how they work together to create the Snake Game.


## Files

### main.c

`main.c` is the entry point of the Snake Game. It initializes hardware, manages the game loop, and handles the game's 
state transitions. The file includes functions for initializing hardware components, reading user input from a joystick, 
updating the game state, and rendering the game on the LED matrix.

### snake.c

`snake.c` contains functions related to the Snake game's core logic. This includes handling the snake's movement, 
collision detection (with walls and itself), food generation, and food consumption. It also provides functions for
resetting the game and initializing the snake and food.

### gameText.c

`gameText.c` includes functions for displaying text messages on the LED matrix. It defines a custom 5x8 font for characters 
and provides a `displayText` function to render text messages. It handles character spacing to ensure proper alignment.

### generalFunctions.c

`generalFunctions.c` contains various utility functions that are used across the project. This includes functions for setting 
and clearing individual bits in a register, generating random numbers, and initializing the millisecond timer.

### max72xx.c

`max72xx.c` provides functions for interfacing with the MAX7219 LED matrix driver. It includes functions for initializing the 
display, setting individual pixels, and sending data to the LED matrix.

### uart.c

`uart.c` handles serial communication and provides functions for serial initialization and data transmission. It is useful 
for debugging and sending messages from the microcontroller to a connected terminal.

### analogRead.c

`analogRead.c` contains functions for reading analog values from pins, particularly for the joystick input in this project.

### millis.c

`millis.c` is responsible for implementing a simple millisecond timer using the AVR Timer1. It includes functions for 
initializing the timer and getting the current millisecond count.


## Makefile

The project includes a Makefile for building and programming the code onto an AVR microcontroller, specifically the ATmega2560. 
The Makefile is designed to work with the AVR-GCC toolchain and other AVR utilities.

### Configuration

CC, LD, OBJCOPY, OBJDUMP, AVRSIZE, and OBJISP variables are configured to point to the respective AVR toolchain utilities. 
Please ensure that these paths are correctly set based on your toolchain installation.

MCU specifies the target microcontroller, which in this case is the ATmega2560. You can change this to match your specific 
microcontroller if needed.

CFLAGS contains compiler flags, including optimization level, microcontroller type, and CPU frequency. Adjust these flags 
as necessary for your project requirements.

LDFLAGS specifies linker flags and the target microcontroller for linking. Ensure that it matches your microcontroller.

PORT specifies the serial port used for programming the AVR microcontroller. Update this to match the port you are using for programming.

BIN is the base name for the output binary.

OUT is the output HEX file generated by the build process.

SOURCES lists all the source code files in your project. Make sure to include all relevant source files.

DEBUG is a variable that, when set to 1, indicates a debug build. Adjust this variable as needed for debug or release builds.

### Usage

To build the project, simply run make in the project directory. The output binary will be generated in the specified output 
directory (bin/debug for debug builds and bin/release for release builds).

To program the microcontroller, use the make isp target. Make sure to connect your AVR programmer and specify the correct 
port (-PCOMX) in the OBJISP variable.

To clean the project directory and remove generated files, run make clean.


## Acknowledgments

This Snake Game project was developed by Alexander Granberg.

Feel free to modify and adapt this code for your own purposes or learn from it to create your own AVR-based projects.

Enjoy playing the Snake Game!
