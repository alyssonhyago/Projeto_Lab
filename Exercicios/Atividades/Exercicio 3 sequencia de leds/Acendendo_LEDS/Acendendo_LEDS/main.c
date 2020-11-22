#define F_CPU 16000000UL //define a frequ�ncia do microcontrolador 16MHz 

#include <avr/io.h> //defini��es do componente especificado
#include <util/delay.h> //biblioteca para as rotinas de delay

// --- Defini��es de macros - para o trabalho com os bits de uma vari�vel ---
#define set_bit(Y,bit_x)(Y|=(1<<bit_x)) //ativa o bit x da vari�vel Y (coloca em 1)
#define clr_bit(Y,bit_x)(Y&=~(1<<bit_x)) //limpa o bit x da vari�vel Y (coloca em 0)
#define tst_bit(Y,bit_x)(Y&(1<<bit_x)) //testa o bit x da vari�vel Y (retorna 0 ou 1)

// --- Definindos os Pinos de uso 

#define LED1 PD0 //LED � o substituto de PD2 na programa��o
#define LED2 PD1
#define LED3 PD2
#define LED4 PD3
#define LED5 PD4
#define BOTAO PD7 //BOTAO � o substituto de PD7 na programa��o

int main()
{
	DDRD = 0x1F; //configura o PORTD, PD0 a PD3 como sa�da, os demais pinos entradas
	PORTD= 0xFF; //habilita o pull-up para o bot�o e apaga o LED 
	int i = 1;
	
	
	while(1) 
	{
		
		if(!tst_bit(PIND,BOTAO))//se o bot�o for pressionado executa o if
		{
			
			while(!tst_bit(PIND,BOTAO)); //fica preso at� soltar o bot�o
			_delay_ms(100);
			i++;
		}
		if (i > 3)
		{
			i = 1;
		}
			_delay_ms(100); //atraso de 10 ms para eliminar o ru�do do bot�o
		
			switch (i)	// switch para selecionar qual sequencia de led ser� apresentada
			{
			
				case 1:
						if(tst_bit(PORTD,LED1))		//se o LED estiver apagado, liga o LED
						{ 
						_delay_ms(100);
						clr_bit(PORTD,LED5);
						
						_delay_ms(100);
						clr_bit(PORTD,LED4);
						
						_delay_ms(100);
						clr_bit(PORTD,LED3);
						
						_delay_ms(100);
						clr_bit(PORTD,LED2);
						
						_delay_ms(100);
						clr_bit(PORTD,LED1);
						_delay_ms(100);
						}
						else //se n�o apaga o LED
						{
						set_bit(PORTD,LED5);
						set_bit(PORTD,LED4);
						set_bit(PORTD,LED3);
						set_bit(PORTD,LED2);
						set_bit(PORTD,LED1);
						} 	
					break;
				case 2:
						if(tst_bit(PORTD,LED1))	//se o LED estiver apagado, liga o LED
						{ 
						_delay_ms(100);
						clr_bit(PORTD,LED1);
				
						_delay_ms(100);
						clr_bit(PORTD,LED2);
						
						_delay_ms(100);
						clr_bit(PORTD,LED3);
						
						_delay_ms(100);
						clr_bit(PORTD,LED4);
						
						_delay_ms(100);
						clr_bit(PORTD,LED5);
						_delay_ms(100);
						}
					   else //se n�o apaga o LED
						{
						set_bit(PORTD,LED1);
						set_bit(PORTD,LED2);
						set_bit(PORTD,LED3);
						set_bit(PORTD,LED4);
						set_bit(PORTD,LED5);
						}	
		
					break;	
			  case 3:
			
					if(tst_bit(PORTD,LED1))		//se o LED estiver apagado, liga o LED
					{
						
						clr_bit(PORTD,LED1);
						_delay_ms(100);
						clr_bit(PORTD,LED2);
						_delay_ms(100);
						clr_bit(PORTD,LED3);
						_delay_ms(100);
						clr_bit(PORTD,LED4);
						_delay_ms(100);
						clr_bit(PORTD,LED5);
						_delay_ms(100);
						set_bit(PORTD,LED1);
						set_bit(PORTD,LED2);
						set_bit(PORTD,LED3);
						set_bit(PORTD,LED4);
						//set_bit(PORTD,LED5);
						_delay_ms(200);
						clr_bit(PORTD,LED5);
						_delay_ms(100);
						clr_bit(PORTD,LED4);
						_delay_ms(100);
						clr_bit(PORTD,LED3);
						_delay_ms(100);
						clr_bit(PORTD,LED2);
						_delay_ms(100);
						clr_bit(PORTD,LED1);
						_delay_ms(100);
						set_bit(PORTD,LED5);
						set_bit(PORTD,LED4);
						set_bit(PORTD,LED3);
						set_bit(PORTD,LED2);
						set_bit(PORTD,LED1);
					}
					
					else //se n�o apaga o LED
					{
						/*_delay_ms(300);
						clr_bit(PORTD,LED4);
						_delay_ms(300);
						clr_bit(PORTD,LED3);
						_delay_ms(300);
						clr_bit(PORTD,LED2);
						_delay_ms(300);
						clr_bit(PORTD,LED1);
						_delay_ms(300);
						set_bit(PORTD,LED4);
						set_bit(PORTD,LED3);
						set_bit(PORTD,LED2);
						set_bit(PORTD,LED1);*/
					}	 
				break;	
			}// fim do switch 

	}// fim while 1 
	
}// fim da main
