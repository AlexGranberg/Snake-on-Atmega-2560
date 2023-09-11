#ifndef __snake_H
#define __snake_H
#include <stdbool.h>

typedef struct{
    int x_Position;
    int y_Position;
}Snake_Head;

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

typedef enum{
    GAME_START,
    PLAYING,
    GAME_OVER,
    WIN,
} Game_State;


void snakePosition(int x, int y);
void snakeMovement(Snake_Head *snake, Snake_Direction direction, int maxX, int maxY, Game_State *gameState);
bool isFoodOnSnake(unsigned char foodX, unsigned char foodY, Snake_Segment *segments, int numSegments);
bool isSnakeCollidingWithSnake(int headX, int headY, Snake_Segment *segments, int numSegments);
bool eatFood(Snake_Head *snake, Food *food, Snake_Segment snakeSegments[], int *numberOfSnakeSegments, Game_State *gameState);
void FoodInit(bool *firstFood, Food *food);
void updateSnakeSegments(Snake_Head *snake, Snake_Segment snakeSegments[], int numberOfSnakeSegments);
void controls(int vert, int horz, Snake_Direction *currentSnakeDirection);
void resetGame(Snake_Head *snake, Food *food, Snake_Segment snakeSegments[], int *numberOfSnakeSegments, Snake_Direction *currentSnakeDirection, bool *foodEaten, bool *firstFood);

#endif