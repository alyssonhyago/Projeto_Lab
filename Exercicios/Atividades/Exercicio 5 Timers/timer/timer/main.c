/*
 * timer.c
 *
 * Created: 07/10/2020 14:21:01
 * Author : Alysson Hyago Pereira de Oliveira Mat:119210495
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>



// declaração de variais para a contagem dos  displays 
uint8_t seg[10] = {0x7E,0x30,0x6D, 0x79 , 0x33, 0x5B, 0x5F, 0x70 ,0x7F,0x7B};
uint8_t cont = 0;	//variavel para contagem 
uint8_t cont2 = 0;	//variavel para contagem 
int aux = 1; //variavel aux parar as interrupções de pause e star

uint16_t Cont3 = 1; //variavel para a condição de chegar a 1s

// -- Função de vetores de interrupção externa
ISR(INT0_vect); //  INT EXT 0
ISR(INT1_vect);	// INT EXT 1

int main()
{
	DDRD = 0x00;	// configura os pinos d como entrada
	PORTD = 0xFF;	// pull-up
	DDRC = 0xFF;	// configira para saida o PORTD (1 saida 0  entrada)
	DDRB = 0xFF;	// configira para saida o PORTD (1 saida 0  entrada)
	
	TCCR0A= 0b00000010;		//Habilita o modo do TC0 como CTC(01 bitlow) ou Normal(00 bitlow) 
	TCCR0B= 0b00000011;		//habilita o vaor do prescaler para TC0(clock/64 11-bitlow)
	OCR0A=	249;				// valor de comparação ; Tocr = (ValorPrescaler*(OCR0A+1))/16Mhz
	TIMSK0 = 0b00000010; //habilita a interrupção do TC0 1ms = (64*(249+1))/16MHz
	
	
	//configuração das interrupções
	EICRA = 0b00001010;	// configurando como borda de descida
	EIMSK = 0b00000011; //habilita a interrupção extrena INT0 e INT1
	sei(); //habilita a chave de interrupção global
	PORTB = seg[0];
	PORTC = seg[0];
	
	while(1)
	{
		PORTB = seg[cont]; // contagem de 0 a 9 menos significativo
		
		if(cont == 10) //reinicia a contagem menos significativo 
		{
			cont2++;
			
			if (cont2==10)// reinicia a contagem do mais significativo 
			{
				cont2 =0;
			}
			cont=0;
		}
		
		PORTC = seg[cont2];	// contagem de 0 a 9 menos significativo
	}
}


ISR(INT0_vect) //interrupção para pausar e iniciar
{
	if (aux==0)
	{
		aux++;
	}
	else
	{
	aux =0;
	}
}
ISR(INT1_vect) // interrupção para zerar a contagem
{
	
	cont = 0;
	cont2 = 0;
	
}
ISR(TIMER0_COMPA_vect) // interrupção para contagem do cronometro de 1s
{
	if(Cont3 == 1000)
	{
		Cont3=0;
		
		if(aux==1)
		{
			cont++;
		}
	}
	Cont3++;
}