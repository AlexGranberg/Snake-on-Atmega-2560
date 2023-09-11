# Snake-on-Atmega-2560

# Snake Game README

This README provides an overview of the Snake Game code contained in multiple source files.

## Overview

The Snake Game is implemented in C for an AVR microcontroller, and it uses an LED matrix for display. The game logic, 
display functions, and user controls are distributed across several source files to maintain code organization and readability.

## Hardware

This project assumes the use of an AVR microcontroller, in this case the Atmega2560, an LED matrix controlled by the MAX7219 driver, 
a joystick for user input, and a UART module for serial communication.

<img width="665" alt="snake_on_atmega" src="https://github.com/AlexGranberg/Snake-on-Atmega-2560/assets/42450559/13d9d717-070e-4421-8d21-4886389d2a83">

## Getting Started

To use this code, you need to set up your hardware accordingly and flash it onto an AVR microcontroller. Additionally, you may 
need to install an AVR development environment (such as AVR-GCC) and program your microcontroller using a suitable programmer.

You could also test it out on wokwi: https://wokwi.com/projects/367313440995520513

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

## Acknowledgments

This Snake Game project was developed by Alexander Granberg.

Feel free to modify and adapt this code for your own purposes or learn from it to create your own AVR-based projects.

Enjoy playing the Snake Game!
