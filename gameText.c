#include "max72xx.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>


void gameText(int x, int y) {

    //  G
    max7219b_set(3 + x, 3 + y);
    max7219b_set(3 + x, 4 + y);
    max7219b_set(3 + x, 5 + y);
    max7219b_set(3 + x, 6 + y);
    max7219b_set(3 + x, 7 + y);
    max7219b_set(4 + x, 3 + y);
    max7219b_set(5 + x, 3 + y);
    max7219b_set(6 + x, 3 + y);
    max7219b_set(4 + x, 7 + y);
    max7219b_set(5 + x, 7 + y);
    max7219b_set(6 + x, 7 + y);
    max7219b_set(6 + x, 6 + y);
    max7219b_set(6 + x, 5 + y);
    max7219b_set(5 + x, 5 + y);
    
    //  A
    max7219b_set(8 + x, 3 + y);
    max7219b_set(8 + x, 4 + y);
    max7219b_set(8 + x, 5 + y);
    max7219b_set(8 + x, 6 + y);
    max7219b_set(8 + x, 7 + y);
    max7219b_set(9 + x, 3 + y);
    max7219b_set(10 + x, 3 + y);
    max7219b_set(11 + x, 3 + y);
    max7219b_set(9 + x, 5 + y);
    max7219b_set(10 + x, 5 + y);
    max7219b_set(11 + x, 5 + y);
    max7219b_set(11 + x, 4 + y);
    max7219b_set(11 + x, 6 + y);
    max7219b_set(11 + x, 7 + y);

    //  M
    max7219b_set(13 + x, 3 + y);
    max7219b_set(13 + x, 4 + y);
    max7219b_set(13 + x, 5 + y);
    max7219b_set(13 + x, 6 + y);
    max7219b_set(13 + x, 7 + y);
    max7219b_set(14 + x, 3 + y);
    max7219b_set(15 + x, 4 + y);
    max7219b_set(15 + x, 5 + y);
    max7219b_set(16 + x, 3 + y);
    max7219b_set(17 + x, 3 + y);
    max7219b_set(17 + x, 4 + y);
    max7219b_set(17 + x, 5 + y);
    max7219b_set(17 + x, 6 + y);
    max7219b_set(17 + x, 7 + y);

    //  E
    max7219b_set(19 + x, 3 + y);
    max7219b_set(19 + x, 4 + y);
    max7219b_set(19 + x, 5 + y);
    max7219b_set(19 + x, 6 + y);
    max7219b_set(19 + x, 7 + y);
    max7219b_set(20 + x, 3 + y);
    max7219b_set(21 + x, 3 + y);
    max7219b_set(22 + x, 3 + y);
    max7219b_set(20 + x, 7 + y);
    max7219b_set(21 + x, 7 + y);
    max7219b_set(22 + x, 7 + y);
    max7219b_set(20 + x, 5 + y);
    max7219b_set(21 + x, 5 + y);
    max7219b_out();
}