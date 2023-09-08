#ifndef __snake_H
#define __snake_H
#include <stdbool.h>

typedef struct{
    int x_Position;
    int y_Position;
}Snake;

typedef struct{
    int x;
    int y;
}Snake_Segment;

typedef struct{
    unsigned char x_Position;
    unsigned char y_Position;
}Food;

typedef enum{
    snake_Direction_Up,
    snake_Direction_Down,
    snake_Direction_Left,
    snake_Direction_Right,
}Snake_Direction;


void snakePosition(int x, int y);
void snakeMovement(Snake *snake, Snake_Direction direction);
bool isFoodOnSnake(unsigned char foodX, unsigned char foodY, Snake_Segment *segments, int numSegments);
bool isSnakeCollidingWithSnake(int headX, int headY, Snake_Segment *segments, int numSegments);
bool eatFood(Snake *snake, Food *food, Snake_Segment snakeSegments[], int *numberOfSnakeSegments);
void FoodInit(bool firstFood, Food *food);

#endif