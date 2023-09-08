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

bool isSnakeCollidingWithSnake(int headX, int headY, Snake_Segment *segments, int numSegments){
	if (numSegments <= 1) {
		return false;
	}
	for (int i = 0; i < numSegments; i++){
		if(headX == segments[i].x && headY == segments[i].y) {
			return true;
		}
	}
	return false;
}

bool eatFood(Snake *snake, Food *food, Snake_Segment snakeSegments[], int *numberOfSnakeSegments) {
    if (snake->x_Position == food->x_Position && snake->y_Position == food->y_Position) {
        // Food is eaten
        food->x_Position = randNum();
        food->y_Position = randNum2();
        
        if (*numberOfSnakeSegments < 256) {
            // Add a segment to the snake
            snakeSegments[*numberOfSnakeSegments].x = snakeSegments[*numberOfSnakeSegments - 1].x;
            snakeSegments[*numberOfSnakeSegments].y = snakeSegments[*numberOfSnakeSegments - 1].y;
            (*numberOfSnakeSegments)++;
        }
        
        return true;
    }
    
    return false;
}

void FoodInit(bool *firstFood, Food *food){
	max7219b_set(food->x_Position, food->y_Position);
	*firstFood = false;
}

void updateSnakeSegments(Snake *snake, Snake_Segment snakeSegments[], int numberOfSnakeSegments) {
    // Update the head of the snake
    snakeSegments[0].x = snake->x_Position;
    snakeSegments[0].y = snake->y_Position;

    // Shift the segments
    for(int i = numberOfSnakeSegments - 1; i > 0; i--) {
        snakeSegments[i] = snakeSegments[i - 1];
    }

    // Update the display with the new segments
    for(int i = 0; i < numberOfSnakeSegments; i++) {
        max7219b_set(snakeSegments[i].x, snakeSegments[i].y);
    }
	printf("%d", numberOfSnakeSegments);
}