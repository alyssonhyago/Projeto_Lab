/*
 * Codigo_Projeto.c
 *
 * Created: 10/11/2020 19:16:41
 * Author : ALYSSON
 */ 

#include <avr/io.h>
#include "i2c.h"
#include "LCD_I2C.h"
#include <util/delay.h>



int main(void)
{
	DDRD = 0b11111111; // PortD como saida 
	
	// inicialização do display 
	i2c_init();
	i2c_start();
	i2c_write(0x70);
	lcd_init();
	lcd_cmd(0x80);
	lcd_msg("Bom dia!");
	lcd_cmd(0xC0);
	lcd_msg("Digite sua senha!");
	 
	 
    while (1) 
    {
		PORTD = 0b00000001;
		_delay_ms(3000);
		PORTD = 0b00000000;
		_delay_ms(1000);
		
    }
}

