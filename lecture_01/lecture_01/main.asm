;
; lecture_01.asm
;
; Created: 2/7/2024 6:49:37 PM
; Author : jlb
; Program to generate a discrete signal
; using delay subroutine
;
.cseg	;code segment origin
.org 0x00
.def temp = r16
.def counter = r17
.def multiplier = r18

;Main program
;*******************************************
; Writes "1" or "0" to PB5 at time intervals
;*******************************************
	;Stack init
	ldi temp,high(RAMEND) ;High byte
	out SPH,Temp
	ldi temp,low(RAMEND) ;Low byte
	out SPL,Temp
;Port configuration
	;using (1<<PBx) to write at bit level
	ldi temp,(1<<PB5)
	out DDRB,Temp 
start:
	rcall on_off	;go to subroutine
	rjmp start
;Subroutines
;****************************************
; Sends "1" or "0" (on/off) to PB1
;****************************************
on_off:
	sbi PORTB,PB5	;on bit
	ldi counter,20  ;requency 1
	rcall delay 	;wait (go to suroutine)
	cbi PORTB,PB5	;Off bit
	ldi counter,20  ;requency 1
	rcall delay 	;wait (go to suroutine)
	ret

;********************************************
; Delay given by "counter x multiplier" times
;********************************************
delay:
c2:		ldi multiplier,167
c1:		dec multiplier
		brne c1
		dec counter 
		brne c2
		ret