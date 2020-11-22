#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "nokia5110.h"

#define tam_vetor 3
char leitura_ADC_string[tam_vetor];
uint16_t leitura_ADC = 0;
void float2string( float Celsius,  char *disp);

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
	OCR0A = leitura_ADC/4-1;
	leitura_ADC = (leitura_ADC/1023.0)*100;
}

int main(void)
{
	
	DDRB = 0xFF; // saida
	DDRC = 0x00; // entrada
	PORTC = 0xFE; // so C0 em baixo nivel
	DDRD = 0b01000000; // todos os pinos da porta D como entrada, somente o 6 como saida
	
	//configurando o ADC
	ADMUX = 0b11000000; // tensao interna de ref(1.1v)
	ADCSRA = 0b11101111;//habilita o AD, interrupção, conversao, prescaler 128
	ADCSRB = 0x00;// conversão continua
	DIDR0 = 0b00111110;// habilita o PC0 como entrada do ADC0
	
	//modo PWM
	TCCR0A = 0b10100011; // habilita o Modo PWM rapido e modo nao invertido  nos pinos OC0A e OC0B
	TCCR0B = 0b00000101;	//liga TC0, prescaler = 1024, fpwm =  16MHZ/(256*1024) = 61Hz
	OCR0A = 0; // controle do ciclo ativo do PWM OC0A(PD6)Duty = 200/256 = 78%
	
	sei();
	nokia_lcd_init();
	
	while(1)
	{
		Vntc = ((5.0 * leitura_ADC)/1023);
		Rntc = (Vntc*(10000.0/(5.0-Vntc)));
		T_Kelvin = 1/(a + b * log(Rntc) + c * pow(log(Rntc),3));
		Celsius = (T_Kelvin - 273);
		
		nokia_lcd_clear();
		int2string(leitura_ADC, leitura_ADC_string);
		nokia_lcd_write_string(leitura_ADC_string, 3);
		nokia_lcd_write_char('%', 3);
		nokia_lcd_render();
		_delay_ms(1000);
	}
	
}

void float2string( float Celsius, char *disp)
{
	for (uint8_t n = 0; n<tam_vetor; n++)
	disp[n] = 0 +48;
	
	disp += tam_vetor -1;
	do
	{
		*disp = (Celsius)+48;
		disp--;
	} while (Celsius!=0);
}