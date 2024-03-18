/*
 * leds.c
 *
 * Created: 2/27/2024 6:51:07 PM
 *  Author: josel
 */ 
#include <avr/io.h>
#include <util/delay.h>
void led_on(char color)
{
	PORTB |= (1 << color);
}
void led_on_off (void)
{
	for (int i=0;i <= 5;i++)
	{
	PORTB ^= 1 << PB5;
	_delay_ms(200);
	}
}
	