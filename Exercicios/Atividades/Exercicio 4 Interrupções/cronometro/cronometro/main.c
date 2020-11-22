#define F_CPU 16000000UL //define a frequência do microcontrolador em 16MHz

#include <avr/io.h> //definições do componente especificado
#include <util/delay.h> //biblioteca para o uso das rotinas de _delay_
#include <avr/interrupt.h> // bibliteca da interrupção


uint8_t seg[10] = {0x7E,0x30,0x6D, 0x79 , 0x33, 0x5B, 0x5F, 0x70 ,0x7F,0x7B};
uint8_t cont = 0;
uint8_t cont2 = 0;
int aux = 1;

// -- Função de vetores de interrupção externa
ISR(INT0_vect); //  INT EXT 0
ISR(INT1_vect);	// INT EXT 1

int main(void)
{
	
	
	DDRD = 0x00;	// configura os pinos d como entrada
	PORTD = 0xFF;	// pull-up
	DDRC = 0xFF;	// configira para saida o PORTD (1 saida 0  entrada)
	DDRB = 0xFF;	// configira para saida o PORTD (1 saida 0  entrada)
	
	//configuração das interrupções
	EICRA = 0b00001010;	// configurando como borda de descida
	EIMSK = 0b00000011; //habilita a interrupção extrena INT0 e INT1
	sei(); // habilita todas as interrupções

	

	PORTC = seg[0]; // inicializa oem 0 o display esquerdo
	
	while (1)
	{
		
		
		if(aux)
		{
			
			PORTB = seg[cont];
			cont++;
			_delay_ms(1000);
			
			if(cont == 10) //reinicia a contagem
			{
				
				cont2++;
				if (cont2==10)
				{
					cont2 =0;
				}
				cont=0;
			}
			
			PORTC = seg[cont2];
			
		}
	}
}
ISR(INT0_vect) //pausar e iniciar
{
	
	aux =!aux;
	
}
ISR(INT1_vect) // zerar a contagem
{
	
	cont = 0;
	cont2 = 0;
	
}