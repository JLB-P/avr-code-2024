/*
 * i2c.c
 *
 * Created: 4/1/2024 7:13:51 PM
 *  Author: jlb
 */ 
#include "i2c.h"

void TWI_Init (void)
{
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Calculation fclk:
	//
	// fclk = (fcpu)/(16+2*TWBR*4^Prescaler) m16
	// fclk = (fcpu)/(16+2*TWBR*Prescaler) m328p
	// -------------------------------------------------------------------------------------
	// Calculation TWBR:
	//
	// TWBR = {(fcpu/fclk) - 16 } / (2*4^Prescaler)
	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// @param1 value of TWBR (m16)
	//  fclk = 400kHz; TWBR = 3
	//  fclk = 100kHz; TWBR = 20
	// @param1 value of TWBR (m328p)
	//  fclk = 400kHz; TWBR = 2
	// @param2 value of Prescaler = 1
	TWI_FREQ (2, 1);
}
char TWI_MT_Start (void)
{
	// null status flag
	TWI_TWSR &= ~0xA8;
	// START
	// -------------------------------------------------------------------------------------
	// request for bus
	TWI_START();
	// wait till flag set
	TWI_WAIT_TILL_TWINT_IS_SET();
	// test if start or repeated start acknowledged
	if ((TWI_STATUS != TWI_START_ACK) && (TWI_STATUS != TWI_REP_START_ACK)) {
		// return status
		return TWI_STATUS;
	}
	// success
	return SUCCESS;
}

char TWI_MT_Send_SLAW (char address)
{
	// SLA+W
	// -------------------------------------------------------------------------------------
	TWI_TWDR = (address << 1);
	// enable
	TWI_ENABLE();
	// wait till flag set
	TWI_WAIT_TILL_TWINT_IS_SET();

	// test if SLA with WRITE acknowledged
	if (TWI_STATUS != TWI_MT_SLAW_ACK) {
		// return status
		return TWI_STATUS;
	}
	// success
	return SUCCESS;
}

char TWI_MT_Send_Data (char data)
{
	// DATA
	// -------------------------------------------------------------------------------------
	TWI_TWDR = data;
	// enable
	TWI_ENABLE();
	// wait till flag set
	TWI_WAIT_TILL_TWINT_IS_SET();

	// test if data acknowledged
	if (TWI_STATUS != TWI_MT_DATA_ACK) {
		// return status
		return TWI_STATUS;
	}
	// success
	return SUCCESS;
}

char TWI_MR_Send_SLAR (char address)
{
	// SLA+R
	// -------------------------------------------------------------------------------------
	TWI_TWDR = (address << 1) | 0x01;
	// enable
	TWI_ENABLE();
	// wait till flag set
	TWI_WAIT_TILL_TWINT_IS_SET();

	// test if SLA with READ acknowledged
	if (TWI_STATUS != TWI_MR_SLAR_ACK) {
		// return status
		return TWI_STATUS;
	}
	// success
	return SUCCESS;
}

void TWI_Stop (void)
{
	// End TWI
	// -------------------------------------------------------------------------------------
	// send stop sequence
	TWI_STOP ();
	// wait for TWINT flag is set
	//  TWI_WAIT_TILL_TWINT_IS_SET();
}
