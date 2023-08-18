#include "max72xx.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "gameText.h"
#include <time.h>
#include <stdlib.h>
#include "generalFunctions.h"

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

void snakePosition(int x, int y){
	max7219b_set(x, y);
}


void snakeMovement(Snake *snake, Snake_Direction direction){
	int maxY = 8;
	int maxX = 32;
	if(direction == snake_Direction_Down){
		snake->y_Position = (snake->y_Position + 1 + maxY) % maxY;
	}
	if(direction == snake_Direction_Up){
		snake->y_Position = (snake->y_Position - 1 + maxY) % maxY;
	}	
	if(direction == snake_Direction_Right){
		snake->x_Position = (snake->x_Position + 1) % maxX;
	}
	if(direction == snake_Direction_Left){
		snake->x_Position = (snake->x_Position - 1 + maxX) % maxX;
	}
}

int main() {

	BIT_CLEAR(DDRF,VERT_PIN);
	BIT_CLEAR(DDRF,HORZ_PIN);

	//Sätt till INPUT_PULLUP
    
	BIT_CLEAR(DDRE,SEL_PIN); // INPUT MODE
    BIT_SET(PORTE,SEL_PIN); 

	Snake snake;
	init_serial();
	max7219_init();
    srandom(time(NULL));   // Call only once!
	snake.x_Position = 4;
	snake.y_Position = 4;
	Snake_Direction currentSnakeDirection = snake_Direction_Right;
	int seed = analogRead(4);
	srandom(seed);
	


    setPinInput(2);  // Set pin A2 as input

	while (1) {

		int horz = analogRead(HORZ_PIN);
  		int vert = analogRead(VERT_PIN);
		int lastPositionX;
		int lastPositionY;
		int randomX = 0;
		int randomY = 0;
        int number1 = randNum();
        printf("%d\n", randNum);
        int number2 = randNum2();
        printf("%d\n", randNum2);
        // max7219b_set(number1, number2);

		// max7219b_set(x, y);
		snakePosition(snake.x_Position, snake.y_Position);
		_delay_ms(150);
        max7219b_out();
		lastPositionX = snake.x_Position;
		lastPositionY = snake.y_Position;
		snakeMovement(&snake, currentSnakeDirection);
		max7219b_clr(lastPositionX, lastPositionY);

		if (vert < 300) {
			currentSnakeDirection = snake_Direction_Down;
		}
		if (vert > 700) {
			currentSnakeDirection = snake_Direction_Up;
		}
		if (horz < 300) {
			currentSnakeDirection = snake_Direction_Right;
		}
		if (horz > 700) {
			currentSnakeDirection = snake_Direction_Left;
		}

			// if (BUTTON_IS_CLICKED(PINE, SEL_PIN)) {
    		// 	max7219b_clr_all();
			// }

        // _delay_ms(100);

		//gameText(x, y); PRINT GAME HARDCODED

		// PRINT OUT SOM ROWS

		// for(int i = 0; i < 32;i++){
		// 	printf("%d\n", i);
		// 	max7219b_set(i, y);
		// 	max7219b_out();
		// 	max7219b_clr(i, y);
		// 		_delay_ms(50);
		// }
		// for(int n = 0; n < 8;n++){
		// 	printf("%d\n", n);
		// 	max7219b_set(x, n);
		// 	max7219b_out();
		// 	max7219b_clr(x, n);
		// 		_delay_ms(50);
		// }
		// for(int d = 0; d < 32;d++){
		// 	y = 1;
		// 	printf("%d\n", d);
		// 	max7219b_set(d, y);
		// 	max7219b_out();
		// 	max7219b_clr(d, y);
		// 		_delay_ms(50);
		// }
		// y = 0;

	}
	return 0;
}