/*
 * lcd_4b.c
 *
 * Created: 6/24/2021 7:47:30 AM
 *  Author: jlb
 */ 
//#define F_CPU 16000000UL //arduino freq.
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_4b.h"

char FirstColumn [2] = {0 , 64};	//first column address

//lcd reset or init lcd 
//DataSheet HD44780 pag.46
void lcd_reset(void)
{
	lcd_port = 0xFF; 		//wait for at least 15 ms
	_delay_ms(20);			//20 ms, the more the better
	
	lcd_port = 0x30+LCD_EN; //Writes Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 & E=1
	lcd_port = 0x30;		//Writes Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 & E=0
	_delay_us(5);			//Wait 4.1 ms
	
	lcd_port = 0x30+LCD_EN; //Writes Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 & E=1
	lcd_port = 0x30;		//Writes Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 & E=0
	_delay_us(200);			//Wait 100 us
	
	lcd_port = 0x30+LCD_EN; //Writes Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 & E=1
	lcd_port = 0x30;		//Writes Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1 & E=0
	_delay_us(200);			//Wait for 100 us
	
	lcd_port = 0x20+LCD_EN; //Writes Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=0 y E=1
	lcd_port = 0x20;		//Writes Rs=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=0 y E=0
	_delay_us(200);			//Wait for 100 us
}

//send commands to lcd in hexadecimal format (0x2c)
//DataSheet HD44780 pag.24
void lcd_cmd (char cmd)
{
	lcd_port = (cmd & 0xF0)|LCD_EN;
	lcd_port = (cmd & 0xF0);
	lcd_port = ((cmd << 4) & 0xF0)|LCD_EN;
	lcd_port = ((cmd << 4) & 0xF0);
	_delay_ms(2);
	_delay_ms(2);
}

//lcd configuration
void lcd_init (void)
{
	lcd_reset();        // Reset lcd
	lcd_cmd(0x2C);		// Function Set:4 bits, 2 lines, resolution 5�10
	lcd_cmd(0x0C);      // Display control: LCD on, cursor on, blinking
	lcd_cmd(0x06);      // Entry mode: Increment
	lcd_cmd(0x80);      // point to DDRAM
}

//write one character given between single brackets 'A' 
void lcd_data (unsigned char dat)
{
	lcd_port = ((dat & 0xF0)|LCD_EN|LCD_RS);
	lcd_port = ((dat & 0xF0)|LCD_RS);
	lcd_port = (((dat << 4) & 0xF0)|LCD_EN|LCD_RS);
	lcd_port = (((dat << 4) & 0xF0)|LCD_RS);
	_delay_ms(2);
	_delay_ms(2);
}

//set cursor at given column,row position
void lcd_col_row(uint8_t x, uint8_t y)
{
	lcd_cmd(0x80 + FirstColumn[y-1]+(x-1));
}

//clear lcd screen
void lcd_clr(void)
{
	lcd_cmd(0x01); //sends command to clear screen (0000 0001)
	_delay_ms(2);
}

//Displays character string given between brackets "hello"
void lcd_write_string(char *a)
{
	unsigned int i;
	for(i=0;a[i]!=0;i++)
	lcd_data(a[i]);
}
