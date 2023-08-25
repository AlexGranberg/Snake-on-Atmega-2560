#include "max72xx.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "gameText.h"
#include <time.h>
#include <stdlib.h>
#include "generalFunctions.h"
#include "snake.h"
#include "analogRead.h"
#include <stdbool.h>

//// https://wokwi.com/projects/367313440995520513

#define VERT_PIN 0
#define HORZ_PIN 1
#define SEL_PIN  4

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 

#define BUTTON_IS_CLICKED(PINE, BUTTON_PIN) !BIT_CHECK(PINE, BUTTON_PIN)

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

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

int main() {

	BIT_CLEAR(DDRF,VERT_PIN);
	BIT_CLEAR(DDRF,HORZ_PIN);

	//Sätt till INPUT_PULLUP
    
	BIT_CLEAR(DDRE,SEL_PIN); // INPUT MODE
    BIT_SET(PORTE,SEL_PIN); 

	Snake snake;
	Food food;
	init_serial();
	max7219_init();
    srandom(time(NULL));   // Call only once!
	snake.x_Position = 4;
	snake.y_Position = 4;
	Snake_Direction currentSnakeDirection = snake_Direction_Right;
	int seed = analogRead(4);
	srandom(seed);
	
	bool foodEaten;
	bool firstFood = true;

    setPinInput(2);  // Set pin A2 as input

	while (1) {

		int horz = analogRead(HORZ_PIN);
  		int vert = analogRead(VERT_PIN);
		int lastPositionX;
		int lastPositionY;

		if(firstFood){
			max7219b_set(food.x_Postion, food.y_Postion);
			firstFood = false;
		}
		if (snake.x_Position == food.x_Postion && snake.y_Position == food.y_Postion){
			foodEaten = true;
		}
		if (foodEaten){
				food.x_Postion = randNum();
				food.y_Postion = randNum2();
				max7219b_set(food.x_Postion, food.y_Postion);
				foodEaten = false;
				
		}
		snakePosition(snake.x_Position, snake.y_Position);
		_delay_ms(70);
        max7219b_out();
		lastPositionX = snake.x_Position;
		lastPositionY = snake.y_Position;
		snakeMovement(&snake, currentSnakeDirection);
		max7219b_clr(lastPositionX, lastPositionY);

		if (vert < 300 && currentSnakeDirection != snake_Direction_Up) {
			currentSnakeDirection = snake_Direction_Down;
		}
		if (vert > 700 && currentSnakeDirection != snake_Direction_Down) {
			currentSnakeDirection = snake_Direction_Up;
		}
		if (horz < 300 && currentSnakeDirection != snake_Direction_Left) {
			currentSnakeDirection = snake_Direction_Right;
		}
		if (horz > 700 && currentSnakeDirection != snake_Direction_Right) {
			currentSnakeDirection = snake_Direction_Left;
		}

			// if (BUTTON_IS_CLICKED(PINE, SEL_PIN)) {
    		// 	max7219b_clr_all();
			// }

		//gameText(x, y); PRINT GAME HARDCODED

	}
	return 0;
}