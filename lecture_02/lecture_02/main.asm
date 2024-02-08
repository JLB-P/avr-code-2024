;
; lecture_02.asm
;
; Created: 2/7/2024 7:56:21 PM
; Author : jlb
; Program to generate a discrete signal
; using internal Timer0
;
.def temp=r16
.def repeat=r17
.def counter=r18

;init code segment
.cseg
.org 0x00
	;init stack
	ldi temp,high(RAMEND)
	out SPH,temp
	ldi temp,low(RAMEND)
	out SPL,temp
	;two ways of set PB5
	//sbi DDRB,PB5 ; PB5->output
	ldi r16,0b00100000 
	out DDRB,r16 ; PB5->output
	;init TIMER0 (datasheet pag.117)
	ldi temp,1 << CS02 | 1 << CS00 ;Precaler=1024
	out TCCR0B, temp	
	;example: pulse = 200ms using prescaler=1024
	;fosc= 16,000,000 s/1024 = 15,625 s= 15.625ms
	;counter=200ms*15.625ms = 3,125
	;Due to 8 bits register, it can not count up to 3,125
	;so 3,125/250=12.5 it requires 12 repeatitions of 250 times
			
start:
	in	R16,PINB
	andi r16,0b00011000
	brne start	   	
	sbi PORTB,PB5	;writes logic "1" on PB5
	rcall delay		;wait for 200ms
	cbi PORTB,PB5	;writes logic "0" on PB5
	rcall delay		;wait for 200ms
	rjmp start

//Subroutines
; delay using TIMER0
Delay:
	ldi counter,0
	out TCNT0,counter ;init counter on 0
	ldi repeat,0;
ciclo:
	in counter,TCNT0
	cpi counter,250
	brne ciclo
	ldi counter,0
	out TCNT0,counter ;init coounter on 0
	inc repeat
	cpi repeat,12
	brne ciclo
	ret	;end of soubroutine
