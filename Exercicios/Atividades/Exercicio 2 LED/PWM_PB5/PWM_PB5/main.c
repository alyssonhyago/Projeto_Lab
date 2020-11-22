/*
 * PWM_PB5.c
 *
 * Created: 18/09/2020 09:58:38
 * Author : Alysson Hyago Pereira de Oliveira 
 * Matricula: 119210495
 */ 


#define F_CPU 16000000UL //define frequencia do microcontrolador 16MHz

#include <avr/io.h>
#include <util/delay.h>

#define LED PB5

// --- Defini��es de macros - empregadas para trabalhar com os bits ---

#define set_bit(Y,bit_x) (Y|=(1<<bit_x)) // ativa o bit x da variavel Y (coloca 1)

#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x)) // limpa o bit X da variavel Y (coloca 0)

// -- Prot�tipo da fun��o delay --
void delay_ms(uint16_t count);

int main(void)
{
	double T = 32;			// periodo 
	double t_off = 0;	   //tempo desligado
	double t_on = 0;	  //tempo ligado
	double duty = 0;	 //dutycycle
	
	DDRB = 0xFF;	   // configura todos os pinos do PORTB como sa�das
	
	while (1)
	{
			t_on = (duty * T)/100;
			set_bit(PORTB,LED);		 //Liga LED
			delay_ms(t_on);		    //atraso de 200 ms
			
			t_off = T - t_on;
			clr_bit(PORTB,LED);	 //apaga o LED
			delay_ms(t_off);	//atraso de 200 ms
			
			if(duty<100)
			{
				duty = duty + 1;
			}
			
			else
			{
				duty = 0;
			}		  
			
	}
		
}


// -- Fun��o delay --
void delay_ms(uint16_t count)
{
	while(count--)
	{
		_delay_ms(1);
	}
}