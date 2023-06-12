#include "max72xx.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "gameText.h"
#include <time.h>
#include <stdlib.h>

//// https://wokwi.com/projects/367313440995520513

void setPinInput(uint8_t pin) {
    // Set pin as input using the appropriate registers for your MCU
    // For Atmega2560, you can use the following code:
    DDRF &= ~(1 << pin);    // Set pin direction to input
    PORTF &= ~(1 << pin);   // Disable internal pull-up resistor
}

int randNum(x){
    int c;
    c = random() % 32;
    return c;
}

int randNum2(y){
    int r;
    r = random() % 7;
    return r;
}

int main()
{
	init_serial();
	max7219_init();
    srandom(time(NULL));   // Initialization, should only be called once.
	int x = 0;
	int y = 0;

    setPinInput(0);  // Set pin A0 as input

	while (1) {
        int seed = analogRead(0);
        srandom(seed);

        int number1 = randNum(x);
        printf("%d\n", randNum);
        int number2 = randNum2(y);
        printf("%d\n", randNum2);
        max7219b_set(number1, number2);
        max7219b_out();
        _delay_ms(2000);
		//gameText(x, y);
		for(int i = 0; i < 32;i++){
			printf("%d\n", i);
			max7219b_set(i, y);
			max7219b_out();
			max7219b_clr(i, y);
				_delay_ms(50);
		}
		for(int n = 0; n < 8;n++){
			printf("%d\n", n);
			max7219b_set(x, n);
			max7219b_out();
			max7219b_clr(x, n);
				_delay_ms(50);
		}
		for(int d = 0; d < 32;d++){
			y = 1;
			printf("%d\n", d);
			max7219b_set(d, y);
			max7219b_out();
			max7219b_clr(d, y);
				_delay_ms(50);
		}
		y = 0;

	}
	return 0;
}