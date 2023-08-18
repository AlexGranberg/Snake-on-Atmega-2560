#ifndef __generalFunctions_H
#define __generalFunctions_H

typedef struct{
    int x_Position;
    int y_Position;
}Snake;

typedef enum{
    snake_Direction_Up,
    snake_Direction_Down,
    snake_Direction_Left,
    snake_Direction_Right,
}Snake_Direction;

#endif