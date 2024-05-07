/*
 * line_follower.c
 *
 * Created: 5/14/2022 7:46:57 PM
 * Author : jlb
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "motors.h"

int main(void)
{
	//Initialize Motors
	motors_init();
	motor_right(MOTOR_FORWARD,255);//255
	motor_left(MOTOR_FORWARD,255);//255
	_delay_ms(9000);
	motor_right(MOTOR_BACKWARD,255);//255
	motor_left(MOTOR_BACKWARD,255);//255
	_delay_ms(9000);
	motor_right(MOTOR_STOP,0);//255
	motor_left(MOTOR_STOP,0);//255
	_delay_ms(9000);
	
    while (1) 
    {	
		
    }
}

