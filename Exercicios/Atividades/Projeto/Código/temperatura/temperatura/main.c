#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "nokia5110.h"

#define tam_vetor 5
unsigned char leitura_ADC_string[tam_vetor];
uint16_t leitura_ADC= 0 ;

void int_to_str(uint16_t s, unsigned char *d);

float Vntc;
float Rntc;
float T_Kelvin;
float Celsius;
float a = 0.001129241;
float b = 0.0002341077;
float c = 0.00000008775468;

ISR(ADC_vect)
{
	leitura_ADC = ADC;
}

int main(void)
{
	//GPIO
	DDRB = 0xFF; // saida
	DDRC = 0b00100000; // PINC5 como saida
	PORTC = 0x00; // so C0 em baixo nivel

	//configurando o ADC
	ADMUX = 0b11000000; // tensao interna de ref(1.1v)
	ADCSRA = 0b11101111;//habilita o AD, interrupção, conversao, prescaler 128
	ADCSRB = 0x00;// conversão continua
	DIDR0 = 0b00111110;// habilita o PC0 como entrada do ADC0

	sei();
	nokia_lcd_init();
	
	while(1)
	{
		//Calculo do sensor LM35 Vout = 0.01 * T ;
		
		Celsius = (leitura_ADC/1023.0)*100;

		nokia_lcd_clear();
		int_to_str(Celsius, leitura_ADC_string);
		nokia_lcd_write_string("Temp: ",1);
		nokia_lcd_set_cursor(0, 10);
		nokia_lcd_write_string(leitura_ADC_string, 1);
		nokia_lcd_write_string(" Celsius ",1);
		nokia_lcd_set_cursor(0, 20);
		nokia_lcd_render();
		_delay_ms(1000);
		
		if (Celsius <= 80)
		{
			PORTC = 0b00000000;
		}
		else
		{
			PORTC = 0b00100000;
		}
	}
}

void int_to_str(uint16_t s, unsigned char *d)
{
	uint8_t n = tam_vetor - 2;

	for (int8_t i = n; i >= 0; i--)
	{
		d[i]=s%10+48;
		s/=10;
	}
}