/*
 * ports.c
 *
 * Created: 3/15/2022 6:42:47 PM
 *  Author: josel
 */ 
#include <avr/io.h>

void init_ports(void)
{	
	//assign lcd pin
	/*
	PORB	|	lcd
	--------+------
	PB0		|	RS	
	PB1		|	R/W
	PB2		|	E
	PB3		|	NC
	PB4		|	D4
	PB5		|	D5
	PB6		|	D6
	PB7		|	D7
	*/
	DDRB = 0xFF;	
}