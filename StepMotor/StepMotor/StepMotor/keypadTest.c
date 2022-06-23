/*
 * keypadTest.c
 *
 * Created: 2022-06-23 오후 4:20:23
 *  Author: pknu
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

unsigned char keyScan(){
	PORTA = 0xf7; //0b 1111 0111
	if(PINA == 0xf6) return '1'; //0b 1111 0110
	else if(PINA == 0xfd) return '2'; //0b 1111 1101
	else if(PINA == 0xfb) return '3'; //0b 1111 1011
	_delay_ms(10);
	
	PORTA = 0xef; //0b 1110 ffff
	if(PINA == 0xfe ) return '4';
	else if(PINA == 0xfd) return '5';
	else if(PINA == 0xfb) return '6';
	_delay_ms(10);
	
	PORTA = 0xdf; //0b 1101 ffff
	if(PINA == 0xfe) return '7';
	else if(PINA == 0xfd) return '8';
	else if(PINA == 0xfb) return '9';
	_delay_ms(10);
	
	PORTA = 0xbf; //0b 1011 ffff
	if(PINA == 0xfe) return '*';
	else if(PINA == 0xfd) return '0';
	else if(PINA == 0xfb) return '#';
	_delay_ms(10);

}

int main(){
	unsigned char key;
	DDRA = 0xf8; //0b 1111 1000 포트A의 상위 4비트는 출력, 하위 4비트는 입력
	DDRC = 0xff;
	
	while (1)
	{
		key = keyScan();
		if(key == '1') PORTC = 0x01;
	}
	
	return 0;
}