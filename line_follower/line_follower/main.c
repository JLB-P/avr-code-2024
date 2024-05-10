/*
 * line_follower.c
 *
 * Created: 5/5/2024 9:42:15 PM
 * Author: jlb
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "motors.h"
#include "adc.h"
#include "leds.h"
#include "irsensors.h"

int main(void)
{
	//Initialize LED subsystem
	led_init();
	test_leds();
	//Initialize Analog to Digital Converter (ADC)
	adc_init();
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

