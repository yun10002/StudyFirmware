/*
 * interrupt2.c
 *
 * Created: 2022-06-20 오전 10:41:49
 *  Author: pknu
 */ 

/*스위치 4번 누르면 점등, 한 번 더 누르면 점멸*/

#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char exchange = 0;

SIGNAL(INT4_vect){
	exchange = ~exchange;
}

int main(){
	DDRE = 0x00; //입력
	DDRA = 0xff; //출력
	
	EIMSK = 1 << INT4;
	EICRB = 1 << ISC41;
	
	sei();
	
	while(1){
		if(exchange) PORTA = 0xff;
		else PORTA = 0x00;
	}
		
	return 0;
}