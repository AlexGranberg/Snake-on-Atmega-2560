#include "uart.h"
#include <stdio.h>
#include "snake.h"
#include "max72xx.h"
#include <stdbool.h>

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

bool isFoodOnSnake(unsigned char foodX, unsigned char foodY, Snake_Segment *segments, int numSegments) {
    for (int i = 0; i < numSegments; i++) {
        if (foodX == segments[i].x && foodY == segments[i].y) {
            return true;
        }
    }
    return false;
}