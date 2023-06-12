#include "max72xx.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "gameText.h"

//// https://wokwi.com/projects/367313440995520513


int main()
{
	init_serial();
	max7219_init();
	int x = 0;
	int y = 0;
	while (1) {
		gameText(x, y);
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