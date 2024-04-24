/*
 * I2C.h
 *
 *  Author: jlb
 */ 

#ifndef I2C_H_
#define I2C_H_
#define SCL_CLK 100000
#include <util/delay.h>

#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))
char read_addres;

void init_i2c(void);
void start_i2c(void);
void stop_i2c(void);

uint8_t I2C_Start(char write_address);/* I2C start function */
uint8_t I2C_Repeated_Start(char read_address); /* I2C repeated start function */
uint8_t I2C_Write(char data);	/* I2C write function */
char I2C_Read_Ack()	;	/* I2C read ack function */
char I2C_Read_Nack();		/* I2C read nack function */
#endif /* I2C_H_ */