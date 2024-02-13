;
; lecture_03.asm
;
; Created: 2/12/2024 9:26:41 PM
; Author : jlb
; Program to write "1" or "0" according to
; input on PIN
;
;init code
.cseg	
.org 0x00
.def temp = r16

;Main program
	;Stack init
	ldi temp,high(RAMEND) ;High byte
	out SPH,temp
	ldi temp,low(RAMEND) ;Low byte
	out SPL,temp
	;Port configuration
	ldi temp,0b00100000 ; PB5->output PB4<-input
	out DDRB,temp
	sbi PORTB,PB4;enable Rp
start:
	in	temp,PINB
	andi temp,0b00010000
	brne led_on
	cbi PORTB,PB5 ;led_off
	rjmp start
led_on:
	sbi PORTB,PB5 ;led on
	rjmp start
