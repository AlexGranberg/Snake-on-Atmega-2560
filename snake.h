#ifndef __snake_H
#define __snake_H

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

#endif