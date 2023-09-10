#ifndef __GAMETEXT_H
#define __GAMETEXT_H

#include <avr/io.h>

void gameText(int x, int y);
void displayCharacter(char character, int x, int y);
void setLED(int x, int y);
void displayPhrase(const char* phrase, int x, int y);


#endif