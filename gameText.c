#include "max72xx.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#define MATRIX_WIDTH 32
#define MATRIX_HEIGHT 8

// Function to display a character on the LED matrix
void displayCharacter(char character, int x, int y) {
    // Define a 5x7 font for characters
    char font[8];

    switch (character) {
        case 'G':
            font[0] = 0b0111100;
            font[1] = 0b1000010;
            font[2] = 0b1010010;
            font[3] = 0b1110010;
            font[4] = 0b0000000;
            break;
        case 'A':
            font[0] = 0b1111100;
            font[1] = 0b0010010;
            font[2] = 0b0010010;
            font[3] = 0b1111100;
            font[4] = 0b0000000;
            break;
        case 'M':
            font[0] = 0b1111110;
            font[1] = 0b0000100;
            font[2] = 0b0011000;
            font[3] = 0b0000100;
            font[4] = 0b1111110;
            break;
        case 'E':
            font[0] = 0b1111110;
            font[1] = 0b1010010;
            font[2] = 0b1010010;
            font[3] = 0b1000010;
            font[4] = 0b0000000;
            break;
        case 'W':
            font[0] = 0b1111110;
            font[1] = 0b0100000;
            font[2] = 0b0011000;
            font[3] = 0b0100000;
            font[4] = 0b1111110;
            break;
        case 'I':
            font[0] = 0b1111110;
            font[1] = 0b0000000;
            font[2] = 0b0000000;
            font[3] = 0b0000000;
            font[4] = 0b0000000;
            break;
        case 'N':
            font[0] = 0b1111110;
            font[1] = 0b0000100;
            font[2] = 0b0001000;
            font[3] = 0b0010000;
            font[4] = 0b1111110;
            break;
        case 'D':
            font[0] = 0b1111110;
            font[1] = 0b1000010;
            font[2] = 0b1000010;
            font[3] = 0b0111100;
            font[4] = 0b0000000;
            break;
        default:
            // Default font for unknown characters
            font[0] = 0b0000000;
            font[1] = 0b0000000;
            font[2] = 0b0000000;
            font[3] = 0b0000000;
            font[4] = 0b0000000;
            break;
    }

    // Display the character on the matrix
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            if ((font[i] >> j) & 1) {
                max7219b_set(x + i, y + j);
            }
        }
    }
}

// Function to display text on the LED matrix
void displayText(const char* text, int x, int y) {
    int xOffset = 0;
    while (*text) {
        char character = *text;
        if (character == 'M' || character == 'W'|| character == 'N') {
            displayCharacter(character, x + xOffset, y);
            xOffset += 7; // Adjust the horizontal spacing for wider characters
        }
        else if (character == 'I') {
            displayCharacter(character, x + xOffset, y);
            xOffset += 3; // Adjust the horizontal spacing for wider characters
        } 
        else {
            displayCharacter(character, x + xOffset, y);
            xOffset += 6; // Adjust the horizontal spacing between characters
        }
        text++;
    }
    max7219b_out();
}

void gameTextWin() {
    displayText("WIN", 5, 0);
    max7219b_out();
}
