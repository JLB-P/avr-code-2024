/*
 * INT_EXT.c
 *
 * Created: 12/03/2024 07:07:39 a. m.
 *  Author: jlb
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
	//interrupt service routine
}

void init_ext_int(void)
{
	//interrupt sense control (pag.80)
	//enable interrupt
	//enable general interrupts sei
}
