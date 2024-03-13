/*
 * i2c.c
 *
 * Created: 
 *  Author: jlb
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

void init_i2c(void)
{
	TWSR = ((0 << TWPS1) & (0 << TWPS0)); //Prescaler = 1
	TWBR = 0X14; //Define Bit rate SCL_frec=CPU_frec/(16+2(TWBR)x4^(prescaler))
				//SCL_Frec=(16000000/(16+2(20)(4)))=74Khz
	TWCR = (1<<TWEN); //Enable TWI
}

void start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //START condition
	while((TWCR & (1<<TWINT))==0); //wait until TWINT=0 (TWI then finish)
}

void stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //STOP condition
	_delay_ms(1);
}

void write_i2c(uint8_t data)
{
	TWDR = data; //Byte to write
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA); //writing with acknowledge (TWEA=1)
	while((TWCR & (1<<TWINT))==0); //wait until TWINT=0 (TWI then finish)
}

uint8_t read_i2c()
{
	TWCR = (1<<TWINT)|(1<<TWEN); //read without aknowledge (TWEA=0)
	while((TWCR & (1<<TWINT))==0); //wait until TWINT=0 (TWI termina su trabajo)
	return TWDR; //returns data read
}

