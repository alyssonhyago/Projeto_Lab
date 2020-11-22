/*
 * PWMcomTimer.c
 *
 * Created: 11/10/2020 11:44:36
 * Author : Alysson Hyago Pereira de Oliveira  Mat: 119210495
 */ 

 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// -- Função de vetores de interrupção externa
ISR(INT0_vect); //  INT EXT 0
ISR(INT1_vect);	// INT EXT 1

// declaração de variais para a contagem dos  displays
uint8_t seg[10] = {0x7E,0x30,0x6D, 0x79 , 0x33, 0x5B, 0x5F, 0x70 ,0x7F,0x7B};
int16_t cont = 0;	//variavel para contagem




int main(void)
{
	
	PORTD = 0xFF;	// pull-up
	DDRC = 0xFF;	// configira para saida o PORTD (1 saida 0  entrada)
	DDRB = 0xFF;	// configira para saida o PORTD (1 saida 0  entrada)
	
	DDRD = 0b11110011;	// Piwnos PD6 e PD5 , OCOA e OCOb respsctivamente  PWM
    TCCR0A = 0b10100011; // habilita o Modo PWM rapido e modo nao invertido  nos pinos OC0A e OC0B
	TCCR0B = 0b00000101;	//liga TC0, prescaler = 1024, fpwm =  16MHZ/(256*1024) = 61Hz
	OCR0A = 0; // controle do ciclo ativo do PWM OC0A(PD6)Duty = 200/256 = 78%
	
	//configuração das interrupções
	EICRA = 0b00001010;	// configurando como borda de descida
	EIMSK = 0b00000011; //habilita a interrupção extrena INT0 e INT1
	sei(); //habilita a chave de interrupção global
	PORTB = seg[0];
	PORTC = seg[0];
					
    while (1) 
    {
		
		PORTB = seg[cont%10]; // contagem de 0 a 9 menos significativo
		
		PORTC = seg[cont/10];	// contagem de 0 a 9 menos significativo
    }
}

ISR(INT0_vect) //interrupção para pausar e iniciar
{	
		cont +=5;
		if (cont>99)
		{
			cont= 99;
		}
		OCR0A = cont*2.55;
		
}
ISR(INT1_vect) // interrupção para zerar a contagem
{
	cont -= 5 ;
	if (cont<0)
	{
		cont=0;
	}
	OCR0A = cont*2.55;
}