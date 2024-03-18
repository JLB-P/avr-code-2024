/*
 * comp.c
 *
 * Created: 9/20/2023 4:18:36 PM
 *  Author: jlb
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd_i2c.h"

ISR(ANALOG_COMP_vect)
{
	lcd_i2c_col_row(1,2);
	lcd_i2c_write_string("Vin > Vref");
	_delay_ms(200);
	lcd_i2c_clr();
}

void init_analog_comp(void)
{
	ACSR |= (1 << ACIS1)| (1 << ACIS0);//Interrupt when Input>VRef
	ACSR |= (1 << ACIE);	//Enable interrupt
	
}