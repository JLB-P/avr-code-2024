;
; lecture_04.asm
;
; Created: 2/12/2024 10:01:50 PM
; Author : jlb
;
/*
	1.SRAM memory
	-Data memory map (pag. 18)
		- 32 address General Purpose Registers
		- 64 I/O registers (pag.309)
		- 1024 internal data 
		- Addressing modes: 
			-Direct
			-Indirect with displacement
			-Indirect
			-Indirect with pre-decrement
			-Indirect with post-increment
	2. Variables declaration		
	3. addressing modes
		-Data Direct Addressing (lds Rd,K and lds K,Rr)
		-I/O Direct Addressing
		-Data indirect addressing (X=r27:r26,Y=r29:r28 o Z=r31:r30 como apuntador)
*/

;init data
.dseg
.org 0x0100
my_variable:		.byte	1 ;1 byte
my_variable_1:		.byte	3 ;3 bytes
my_variable_2:		.byte	1;

;init code
.cseg
.org 0x0
constant_1:			.db	0x15,6 ;Define constantes con valores 15 y 6
constant_2:			.db "ABCDEF"
constant_3:			.dw	0x1234
constant_4:			.dw	0x55	;Cambiar .dw por db y viceversa, obervar en debug
constant_5:			.dw 0x6677

;init Stack
	ldi r16,high(RAMEND)
	out SPH,r16
	ldi r16,low(RAMEND)
	out SPL,r16		;I/O Direct Addressing
;main program
start:
	;Data direct addressing
	ldi r16,0x25
	sts my_variable,r16 
	lds r17,my_variable
	ldi r17,0x69
	sts my_variable_1,r17
	ldi r16,0x55
	sts my_variable_2,r16

	;data indirect addressing
	ldi XH,high(my_variable)
	ldi XL,low(my_variable)
	ld r18,X
	ldi r18,0x77
	st X,r18

	;data indirect with + and - accessing to cseg
	ldi ZH,high(constant_5<<1)	;multiply by 2 to obtain byte
	ldi ZL,low(constant_5<<1)	;multiply by 2
	lpm r18,Z+
	lpm r18,Z

    rjmp start
