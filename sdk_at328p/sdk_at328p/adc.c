/*
 * adc.c
 *
 * Created: 
 *  Author: jlb
 */ 
#include <avr/io.h>
#include <stdlib.h>	//conversion to ASCII
#include <avr/interrupt.h>
#include "lcd_i2c.h"

ISR (ADC_vect)
{
	uint8_t LowPart = ADCL;	//10-bit resolution
	uint16_t TenBitResult = ADCH << 2 | LowPart >> 6;
		
	//Example:reading sensor output on LCD
	char ascii_temp [10];
	float temp = (TenBitResult*150/307);
	//Celsius dgree conversion
	//LM35 output=1.5v for 150 degrees
	//then: 5v   -> 1023
	//		1.5v -> x
	// x=((1.5v)*(1023))/5v=306.9
	dtostrf(temp, 4, 1, ascii_temp);
	//4 integers, 1 decimals
	lcd_i2c_col_row(5,2);
	lcd_i2c_write_string(ascii_temp);
	lcd_i2c_data(0xDF); //degrees character
	lcd_i2c_write_string("C");
	//start another conversion
	ADCSRA |= 1<<ADSC;
}

void init_adc(void)
{
	ADCSRA |= 1 << ADEN;//enable adc
	// activate prescaler fo=16,000,000Hz/128~125KHz
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	
	//left justified (ADCH bit9-2, ADCL bit1-0)
	ADMUX |= 1 << ADLAR;		
	//Selects ADC channel (0-5)
	ADMUX |= 1 << MUX0;
	//AVcc= 5v & Aref= with capacitor to GND
	ADMUX |= 1 << REFS0; //Selects Vref(pag 257)
	//enable ADC interrupts
	ADCSRA |= 1 << ADIE;
	//Enable general interrupts
	sei();	
	//start conversion
	ADCSRA |= 1 << ADSC;
}