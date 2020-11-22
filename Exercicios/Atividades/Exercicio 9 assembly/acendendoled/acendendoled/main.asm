;
; acendendoled.asm
;
; Created: 01/11/2020 18:56:34
; Author : ALYSSON
;


; definições de pinos e Registradores para o codigo 
	
.equ LED1 = 0
.equ LED2 = 1
.equ LED3 = 2
.equ LED4 = 3
.equ LED5 = 4
.equ LED6 = 5
.equ LED7 = 6
.equ LED8 = 7
 
.def delay_0 = R17
.def delay_1 = R18
.def delay_2 = R19
 
 
init:
	LDI		R16,	0xFF		;carrega 0b11111111 no R16 
	OUT		DDRD,	R16			;configura como saida 
 
loop:
	ldi		delay_0, 9	;DEFINIÇÃO DA FREQUENCIA 
	ldi		delay_1, 90
	ldi		delay_2, 229
 
	;lIGA OS LEDS NA SEQUENCIA SUBINDO 
	sbi		PIND,LED8
	rcall	delay
	sbi		PIND,LED7
	rcall	delay
	sbi		PIND,LED6
	rcall	delay
	sbi		PIND,LED5
	rcall	delay
	sbi		PIND,LED4
	rcall	delay
	sbi		PIND,LED3
	rcall	delay
	sbi		PIND,LED2
	rcall	delay
	sbi		PIND,LED1		
 
	rjmp	loop	;loop 
 
 ;Função delay
delay:
	ldi r18, 9
	ldi r19, 30
	ldi r20, 229
loop_delay:
	dec r20
	brne loop_delay
	dec r19
	brne loop_delay
	dec r18
	brne loop_delay
	nop
	ret
	