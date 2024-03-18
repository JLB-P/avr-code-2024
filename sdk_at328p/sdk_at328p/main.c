/*
 * sdk_atmega328p.c
 *
 * Created: 2/27/2024 6:31:58 PM
 * Author : josel
 */ 

#include <avr/io.h>
#include "ports.h"
#include "leds.h"
#include "i2c.h"
#include "lcd_i2c.h"
#include "ext_int.h"
#include "comp.h"
#include <avr/interrupt.h>

int main(void)
{
    /* Replace with your application code */
    init_ports();
	led_on_off();
	init_i2c();
	lcd_i2c_init();
	lcd_i2c_write_string("todos reprobados");
	init_ext_int();
	init_analog_comp();
	//enable general interrupts sei
	sei();
	while (1) 
    {
    }
}

