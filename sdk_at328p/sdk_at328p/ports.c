/*
 * ports.c
 *
 * Created: 2/27/2024 6:34:52 PM
 *  Author: josel
 */ 
#include <avr/io.h>

void init_ports(void)
{
//LCD 4bit definition
/*
PORTB|	LCD
----+--------
PB0	|	RS
PB1	|	RW
PB2	|	E
PB3	|	
PB4	|	D4
PB5	|	D5
PB6	|	D6
PB7	|	D7
*/	
	DDRB = 0xFF;
}