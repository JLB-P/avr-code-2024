/*
 * usart.h
 *
 * 
 *  Author: jlb
 */ 

#ifndef USART_H_
#define USART_H_
void init_usart(unsigned int baudrate);
unsigned char usart_receive( void );
void usart_transmit( uint8_t data );
void usart_transmit_string( char s[] );
#endif /* USART_H_ */