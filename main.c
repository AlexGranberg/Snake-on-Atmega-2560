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
#include "millis.h"
#include <avr/interrupt.h>

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

int main() {

	BIT_CLEAR(DDRF,VERT_PIN);
	BIT_CLEAR(DDRF,HORZ_PIN);

	//Sätt till INPUT_PULLUP
    
	BIT_CLEAR(DDRE,SEL_PIN); // INPUT MODE
    BIT_SET(PORTE,SEL_PIN); 

	Snake snake;
	Food food;
	millis_init();
	sei();
	unsigned long current_millis = millis_get();
	unsigned long gameStartTime = current_millis;
	unsigned long lastActionTime = current_millis;
	init_serial();
	max7219_init();
    srandom(time(NULL));   // Call only once!

	Snake_Direction currentSnakeDirection = snake_Direction_Right;
	int seed = analogRead(4);
	srandom(seed);

	snake.x_Position = randNum();
	snake.y_Position = randNum2();	
	food.x_Position = randNum();
	food.y_Position = randNum2();
	bool foodEaten = false;
	bool firstFood = true;


    setPinInput(2);  // Set pin A2 as input

	Snake_Segment snakeSegments[256];
	int numberOfSnakeSegments = 0;

	while (1) {
		current_millis = millis_get();
    	unsigned long elapsed_millis = current_millis - gameStartTime;

		bool isSnakeColliding = false;
		isSnakeColliding = isSnakeCollidingWithSnake(snake.x_Position, snake.y_Position, snakeSegments, numberOfSnakeSegments);
		
		int horz = analogRead(HORZ_PIN);
  		int vert = analogRead(VERT_PIN);

		int lastPositionX;
		int lastPositionY;

		if(firstFood) FoodInit(&firstFood, &food);

		if (current_millis - lastActionTime >= 150) {
            lastActionTime = current_millis;

		if (eatFood(&snake, &food, snakeSegments, &numberOfSnakeSegments)) {
            do {
                food.x_Position = randNum();
                food.y_Position = randNum2();
            } while (isFoodOnSnake(food.x_Position, food.y_Position, snakeSegments, numberOfSnakeSegments));

            max7219b_set(food.x_Position, food.y_Position);
            foodEaten = false;
        }

		updateSnakeSegments(&snake, snakeSegments, numberOfSnakeSegments);
		snakePosition(snake.x_Position, snake.y_Position);
       	max7219b_out();
		max7219b_clr(snakeSegments[numberOfSnakeSegments - 1].x, snakeSegments[numberOfSnakeSegments - 1].y);
		lastPositionX = snake.x_Position;
		lastPositionY = snake.y_Position;
		snakeMovement(&snake, currentSnakeDirection);
        }
		
	
		if (isSnakeColliding) {
			snake.x_Position = randNum();
            snake.y_Position = randNum2();
            food.x_Position = randNum();
            food.y_Position = randNum2();
            foodEaten = false;
            firstFood = true;
            numberOfSnakeSegments = 1;
            snakeSegments[0].x = snake.x_Position;
            snakeSegments[0].y = snake.y_Position;
            currentSnakeDirection = snake_Direction_Right;

            // Clear the display and reset game state
            max7219b_clr_all();
            _delay_ms(2000); // Pause for a moment before restarting
			isSnakeColliding = false;
		}		


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