/*
 * interrupt3.c
 *
 * Created: 2022-06-20 오전 11:24:02
 *  Author: pknu
 */ 

/*LED 하나씩 옮겨가면서 점등, 버튼4 입력시 LED 점멸*/

#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char turn_off = 0;

SIGNAL(INT4_vect){
	turn_off = ~turn_off;
}

int main(){
	DDRE = 0x00; //입력
	DDRA = 0xff; //출력
	
	EIMSK = 1 << INT4; //인터럽트 4번 활성화
	EICRB = 1 << ISC41;
	
	sei();
	
	while(1){
		if(turn_off){
			PORTA = 0x00;
		}
		else{
			PORTA=0x01;
			_delay_ms(500);
			for(int i= 0 ; i < 8 ; i++){
				if(turn_off) PORTA=0x00;
				PORTA = PORTA << 1;
				_delay_ms(500);
			}
		}	
	}
	
	return 0;
}