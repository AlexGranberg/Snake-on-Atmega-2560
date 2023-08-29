#include "max72xx.h"
#include "uart.h"
#include <stdio.h>
#include "generalFunctions.h"
#include <time.h>

void setPinInput(unsigned char pin) {
    // Set pin as input using the appropriate registers for your MCU
    // For Atmega2560
    DDRF &= ~(1 << pin);    // Set pin direction to input
    PORTF &= ~(1 << pin);   // Disable internal pull-up resistor
}

int randNum(){
    int r;
    r = random() % 32;
    return r;
}

int randNum2(){
    int r;
    r = random() % 8;
    return r;
}