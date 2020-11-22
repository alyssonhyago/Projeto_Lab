/*
 * USART.c
 *
 * Created: 19/10/2020 19:49:34
 * Author : Alysson Hyago Pereira de Oliveira
 */ 

#define  F_CPU 16000000UL
#define BAUD 9600 //bps
#define MYUBRR F_CPU/16/BAUD-1 // modo normal assincrono formula slider 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "nokia5110.h"

// -- Função de vetores de interrupção externa
ISR(INT0_vect); //  INT EXT 0
ISR(USART_RX_vect);


// Função para inicialização da USART
void USART_Init(unsigned int ubrr)
{
	UBRR0H = (unsigned char)(ubrr>>8); // taxa de transmissao 
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = 0b10011000;// habilita a transmissao e recepção  e as interrupção de recepção
	UCSR0C = 0b00001110; //ajusta a forma do frame: 8 bits e 2 paradas 
}

//TRansmissao de dados de 5 a 8 bits
void USART_transmit(unsigned char data)
{
	while(!(UCSR0A = 0b00100000));
	 UDR0 = data; // coloca da do no reg. e o envia 
}
unsigned char USART_Receive(void)
{
	while(!(UCSR0A = 0b00100000));//espera o dado ser recebido
	return UDR0;// lê o dado e retorna 
}

int i = 0;
int test = 1;


int main(void)
{
	
	//Portas GPIO
	DDRD = 0b01000000; // todos os pinos da porta D como entrada, somente o 6 como saida
	DDRC = 0b00000001; // como modo de saida 
	PORTD= 0b00000100;
	//configuração das interrupções
	EICRA = 0b00000010;	// configurando como borda de descida
	EIMSK = 0b00000001; //habilita a interrupção extrena INT0 
	sei(); //habilita a chave de interrupção global
	
	//modo PWM
	TCCR0A = 0b10100011; // habilita o Modo PWM rapido e modo nao invertido  nos pinos OC0A e OC0B
	TCCR0B = 0b00000101;	//liga TC0, prescaler = 1024, fpwm =  16MHZ/(256*1024) = 61Hz
	OCR0A = 0; // controle do ciclo ativo do PWM OC0A(PD6)Duty = 200/256 = 78%
	
	// USART
	USART_Init(MYUBRR);
   
    while (1) 
    {
		
		if (test == 1)
		{

			nokia_lcd_init();
			nokia_lcd_clear();
			nokia_lcd_write_string("minha casa",1);
			nokia_lcd_set_cursor(0, 10);
			nokia_lcd_write_string("*------------*", 1);
			nokia_lcd_set_cursor(0, 20);
			nokia_lcd_write_string("L. sala:", 1);
			nokia_lcd_set_cursor(0, 30);
			nokia_lcd_write_string("L. quarto:", 1);
			nokia_lcd_set_cursor(0, 40);
			nokia_lcd_write_string("cortina:", 1);
			nokia_lcd_set_cursor(0,50);
			nokia_lcd_render();
			test = 0;
		}
		
		//OCR0A = i *60;	
		
    }
}
ISR(INT0_vect) // alarme
{
	nokia_lcd_init();
	nokia_lcd_clear();
	nokia_lcd_write_string("Alarme",1);
	nokia_lcd_set_cursor(0, 20);
	nokia_lcd_render();
	_delay_ms(3000);
	test = 1;
}

ISR(USART_RX_vect)
{
		char recebido;
		recebido = UDR0;
		
		if (recebido == 'l')
		{
			PORTC = 0b00000001;
			nokia_lcd_init();
			nokia_lcd_clear();
			nokia_lcd_write_string("lamp.sala:ligada",1);
			nokia_lcd_set_cursor(0, 10);
			nokia_lcd_render();
			_delay_ms(2000);
			test=1;
		}
		
		if (recebido == 'd')
		{
			PORTC = 0b00000000;
			nokia_lcd_init();
			nokia_lcd_clear();
			nokia_lcd_write_string("lamp.sala:desligada",1);
			nokia_lcd_set_cursor(0, 10);
			nokia_lcd_render();
			_delay_ms(2000);
			test=1;
		}
		
		if(recebido == '0')
		{
			 i = 0;
			 OCR0A = i *60;
			 nokia_lcd_init();
			 nokia_lcd_clear();
			 nokia_lcd_write_string("lamp.quarto:desligada",1);
			 nokia_lcd_set_cursor(0, 10);
			 nokia_lcd_write_string("Porcentagem:0%",1);
			 nokia_lcd_set_cursor(0, 10);
			 nokia_lcd_render();
			 _delay_ms(2000);
			 test=1;
			
		}
		
		if(recebido == '1')
		{
			 i = 1;
			 OCR0A = i *60;
			 nokia_lcd_init();
			 nokia_lcd_clear();
			 nokia_lcd_write_string("lamp.quarto:ligada",1);
			 nokia_lcd_set_cursor(0, 10);
			 nokia_lcd_write_string("Porcentagem:25%",1);
			 nokia_lcd_set_cursor(0, 10);
			 nokia_lcd_render();
			 _delay_ms(2000);
			 test=1;
		}
		
		if(recebido == '2')
		{
			 i = 2;
			 OCR0A = i *60;
			 nokia_lcd_init();
			 nokia_lcd_clear();
			 nokia_lcd_write_string("lamp.quarto:ligada",1);
			 nokia_lcd_set_cursor(0, 10);
			 nokia_lcd_write_string("Porcentagem:50%",1);
			 nokia_lcd_set_cursor(0, 10);
			 nokia_lcd_render();
			 _delay_ms(2000);
			 test=1;
		}
		
		if(recebido == '3')
		{
			 i = 3;
			 OCR0A = i *60;
			 nokia_lcd_init();
			 nokia_lcd_clear();
			 nokia_lcd_write_string("lamp.quarto:ligada",1);
			 nokia_lcd_set_cursor(0, 10);
			 nokia_lcd_write_string("Porcentagem:75%",1);
			 nokia_lcd_set_cursor(0, 10);
			 nokia_lcd_render();
			 _delay_ms(2000);
			 test=1;
		}
		
		if(recebido == '4')
		{
			 i = 4;
			 OCR0A = i *60;
			 nokia_lcd_init();
			 nokia_lcd_clear();
			 nokia_lcd_write_string("lamp.quarto:ligada",1);
			 nokia_lcd_set_cursor(0, 10);
			 nokia_lcd_write_string("Porcentagem:100%",1);
			 nokia_lcd_set_cursor(0, 10);
			 nokia_lcd_render();
			 _delay_ms(2000);
			 test=1;

		}
		
		USART_transmit(recebido);
		
}