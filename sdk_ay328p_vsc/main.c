/*
 * sdk_atmega328p.c
 *
 * Created: 2/27/2024 6:31:58 PM
 * Author : josel
 */ 

#include <avr/io.h>
#include "ports.h"
#include "leds.h"
#include "lcd_4b.h"
int main(void)
{
    /* Replace with your application code */
    init_ports();
	led_on_off();
	lcd_init();
	lcd_write_string("todos reprobados");
	while (1) 
    {
    }
}

