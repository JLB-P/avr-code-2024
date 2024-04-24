/*
 * ssd1306.c
 *
 * Created: 3/30/2024 5:03:10 PM
 * Author : jlb
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "ssd1306.h"

//atate machine
enum state{init,st1,st2,st3,st4,st5};
char state=init;
int main()
{	
	while (1)
	{
		switch(state) {
			case init: init_i2c();
					   state=st1;
					   break;
			case st1:  _delay_ms(10);
						InitializeDisplay();
						state=st2;
						break;
			case st2:	setup();
						state=st3;
						break;   // setup();
			case st3:	printBigNumber('2',4,0);
						setXY(5,0);
						printBigTime("23:00");
						state=st4;
						break;
			case st4: break;
			default: break;
		}
	}
return 0;
}