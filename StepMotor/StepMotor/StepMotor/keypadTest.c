/*
 * keypadTest.c
 *
 * Created: 2022-06-23 오후 4:20:23
 *  Author: pknu
 */ 
/*키패드 입력 값에 따라 2진수로 LED 점등*/

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

void init_keypad()
{
	DDRA = 0xF8; //0b 1111 1000
	PORTA = 0x07; //0b 0000 0111
}

unsigned char keyscan()
{
	PORTA = 0x08; //0b 0000 1000
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '1';
	else if((PINA & 0x07) == 0x02) return '2';
	else if((PINA & 0x07) == 0x04) return '3';
	_delay_ms(10);
	
	PORTA = 0x10;		// 0x10
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '4';
	else if((PINA & 0x07) == 0x02) return '5';
	else if((PINA & 0x07) == 0x04) return '6';
	_delay_ms(10);
	
	PORTA = 0x20;		// 0x20
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '7';
	else if((PINA & 0x07) == 0x02) return '8';
	else if((PINA & 0x07) == 0x04) return '9';
	_delay_ms(10);
	
	PORTA = 0x40;		// 0x40
	_delay_ms(1);
	if((PINA & 0x07) == 0x01) return '*';
	else if((PINA & 0x07) == 0x02) return '0';
	else if((PINA & 0x07) == 0x04) return '#';
	_delay_ms(10);
	
	return 0;
}

int main()
{
	DDRC = 0xFf;
	init_keypad();
	
	while(1){
		unsigned char key = keyscan();
		
		//if(key == '1') PORTC = 0x01;
		//else if(key == '2') PORTC = 0x02;
		//else if(key == '3') PORTC = 0x03;
		
		switch (key)
		{
			case '1':
				PORTC = 0x01;
				break;
			case '2':
				PORTC = 0x02;
				break;
			case '3':
				PORTC = 0x03;
				break;
			case '4':
				PORTC = 0x04;
				break;
			case '5':
				PORTC = 0x05;
				break;
			case '6':
				PORTC = 0x06;
				break;
			case '7':
				PORTC = 0x07;
				break;
			case '8':
				PORTC = 0x08;
				break;
			case '9':
				PORTC = 0x09;
				break;
			case '0':
				PORTC = 0x00;
				break;
			case '*':
				PORTC = 0x2A;
				break;
			case '#':
				PORTC = 0x23;
				break;	
				
			default:
				PORTC = 0x00;
				break;
		}
		
	}
	
	return 0;
}