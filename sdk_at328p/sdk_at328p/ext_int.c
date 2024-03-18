/*
 * INT_EXT.c
 *
 * Created: 12/03/2024 07:07:39 a. m.
 *  Author: jlb
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd_i2c.h"

ISR(INT0_vect)
{
	//interrupt service routine
	lcd_i2c_col_row(1,2);
	lcd_i2c_write_string("INT0");
	_delay_ms(200);
	lcd_i2c_clr();
}
ISR(INT1_vect)
{
	//interrupt service routine
	lcd_i2c_col_row(1,2);
	lcd_i2c_write_string("INT1");
	_delay_ms(200);
	lcd_i2c_clr();
}

void init_ext_int(void)
{
	//interrupt sense control (pag.80)
	EICRA |= (1 << ISC01)|(1 << ISC11); //enable INT0 & INT1 rising
	//enable interrupt
	EIMSK |= 1 << INT0 | 1 << INT1; //enable interrupt
	
}
