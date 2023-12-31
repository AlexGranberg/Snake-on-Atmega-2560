#include "uart.h"
#include <stdio.h>
#include "snake.h"
#include "max72xx.h"
#include <stdbool.h>
#include <util/delay.h>

void snakePosition(int x, int y){
	max7219b_set(x, y);
}

void snakeMovement(Snake_Head *snake, Snake_Direction direction, int maxX, int maxY, Game_State *gameState) {
    if (direction == snake_Direction_Down) {
        snake->y_Position += 1;
    }
    if (direction == snake_Direction_Up) {
        snake->y_Position -= 1;
    }   
    if (direction == snake_Direction_Right) {
        snake->x_Position += 1;
    }
    if (direction == snake_Direction_Left) {
        snake->x_Position -= 1;
    }

    // Check for collisions with boundaries
    if (snake->x_Position < 0 || snake->x_Position >= maxX || snake->y_Position < 0 || snake->y_Position >= maxY) {
        *gameState = GAME_OVER;
    }
}

//Update snake segments ie body
void updateSnakeSegments(Snake_Head *snake, Snake_Segment snakeSegments[], int numberOfSnakeSegments) {
    // Update the display with the new segments
    for (int i = numberOfSnakeSegments - 1; i > 0; i--) {
        snakeSegments[i] = snakeSegments[i - 1];
    }
    // Update the head of the snake
    snakeSegments[0].x = snake->x_Position;
    snakeSegments[0].y = snake->y_Position;

    for (int i = 0; i < numberOfSnakeSegments; i++) {
        max7219b_set(snakeSegments[i].x, snakeSegments[i].y);
    }
}

// Function to make sure food doesn't spawn on snake
bool isFoodOnSnake(unsigned char foodX, unsigned char foodY, Snake_Segment *segments, int numSegments) {
    for (int i = 0; i < numSegments; i++) {
        if (foodX == segments[i].x && foodY == segments[i].y) {
            return true;
        }
    }
    return false;
}

//function to check if snake is colliding with it self
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

//Snake eats food function
bool eatFood(Snake_Head *snake, Food *food, Snake_Segment snakeSegments[], int *numberOfSnakeSegments, Game_State *gameState) {
    if (snake->x_Position == food->x_Position && snake->y_Position == food->y_Position) {
        // Food is eaten
        food->x_Position = randNum();
        food->y_Position = randNum2();

        if (*numberOfSnakeSegments < 256) {
            // Add a segment to the snake
            snakeSegments[*numberOfSnakeSegments].x = snakeSegments[*numberOfSnakeSegments - 1].x;
            snakeSegments[*numberOfSnakeSegments].y = snakeSegments[*numberOfSnakeSegments - 1].y;
            (*numberOfSnakeSegments)++;
            // Update the display with the new segment
            max7219b_set(snakeSegments[*numberOfSnakeSegments - 1].x, snakeSegments[*numberOfSnakeSegments - 1].y);
        } else {
            *gameState = WIN;
        }

        return true;
    }

    return false;
}


void FoodInit(bool *firstFood, Food *food){
	max7219b_set(food->x_Position, food->y_Position);
	*firstFood = false;
}

//Function for the joystick controll
void controls(int vert, int horz, Snake_Direction *currentSnakeDirection) {
    static bool isVertical = false;
    static bool isHorizontal = false;
    int verticalThreshold = 200;  
    int horizontalThreshold = 200;

    if (vert < (300 - verticalThreshold)) {
        // Move the joystick down
        isVertical = true;
        isHorizontal = false;
        if (*currentSnakeDirection != snake_Direction_Up) {
            *currentSnakeDirection = snake_Direction_Down;
        }
    }
    else if (vert > (700 + verticalThreshold)) {
        // Move the joystick up
        isVertical = true;
        isHorizontal = false;
        if (*currentSnakeDirection != snake_Direction_Down) {
            *currentSnakeDirection = snake_Direction_Up;
        }
    }
    else if (horz < (300 - horizontalThreshold)) {
        // Move the joystick right
        isHorizontal = true;
        isVertical = false;
        if (*currentSnakeDirection != snake_Direction_Left) {
            *currentSnakeDirection = snake_Direction_Right;
        }
    }
    else if (horz > (700 + horizontalThreshold)) {
        // Move the joystick left
        isHorizontal = true;
        isVertical = false;
        if (*currentSnakeDirection != snake_Direction_Right) {
            *currentSnakeDirection = snake_Direction_Left;
        }
    }
    
    // Prevent diagonal movement by clearing the opposite flag
    if (isVertical && isHorizontal) {
        isVertical = false;
        isHorizontal = false;
    }
}

//Reset game function, getting called when joystick is clicked
void resetGame(Snake_Head *snake, Food *food, Snake_Segment snakeSegments[], int *numberOfSnakeSegments, Snake_Direction *currentSnakeDirection, bool *foodEaten, bool *firstFood) {
    snake->x_Position = randNum();
    snake->y_Position = randNum2();
    int randomX = randNum();
    if (randomX <= 16) {
		*currentSnakeDirection = snake_Direction_Right;
	} else {
		*currentSnakeDirection = snake_Direction_Left;
	}
    food->x_Position = randNum();
    food->y_Position = randNum2();
    *foodEaten = false;
    *firstFood = true;
    *numberOfSnakeSegments = 1;
    snakeSegments[0].x = snake->x_Position;
    snakeSegments[0].y = snake->y_Position;

    max7219b_clr_all();
    _delay_ms(1000); // Pause for a moment before restarting
}