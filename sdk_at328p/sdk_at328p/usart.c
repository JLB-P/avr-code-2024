/*
 * usart.c
 *
 *  Author: jlb
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart.h"

//global variables
volatile char usart_received_char;

ISR (USART_RX_vect)
{
	usart_received_char=UDR0;
	usart_transmit(0x2D); //transmit "-"
	usart_transmit(0x3E); //then ">" symbol
	usart_transmit(usart_received_char);//char from keyboard
	if (usart_received_char == '1')
	{
		PORTB |= 1 << PINB5;	
	}
	else
	{
		PORTB &= ~(1 << PINB5);	
	}
}

unsigned char usart_receive( void )
{
  while (!(UCSR0A & (1 << RXC0))); // wait for data (RXC=1)
  return UDR0;
}

void usart_transmit( unsigned char data )
{
  while (!(UCSR0A & (1 << UDRE0)));  // wait for transmitter buffer empty(UDRE=1)
  UDR0 = data; // when buffer empty, write data to UDR
}

void usart_transmit_string( char s[] )
{	
	int i = 0;
  while (i < 64)
  {
	  if (s[i] == '\0') break;
	  usart_transmit(s[i++]);
  }
}

void init_usart(unsigned int baudrate)
{
	UCSR0C &= (~(1<<UMSEL00) & ~(1<<UMSEL01)); // bit UMSEL = 0 asyncronous mode	
	UCSR0A = (1<<U2X0); // bit U2X = 1 double speed
	//Baudrate:fosc=16Mhz,U2Xn=1,BaudRate=9600, then UBRR= 207 (DS pag.199)
	UBRR0H = (unsigned char) (baudrate>>8); // write(MSB)
	UBRR0L = (unsigned char) (baudrate);	//write(LSB)
	UCSR0C = ((1<<UCSZ00) | (1<<UCSZ01)); //8 bits data lenght
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);	//enable transmitter & receiver
	//UCSRC = (1<<USBS);	//2 stop bits
	UCSR0B |= (1<<RXCIE0);	//enable reception complete (RXCIE0=1) interrupts
}