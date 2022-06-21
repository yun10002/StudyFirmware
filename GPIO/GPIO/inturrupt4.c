/*
 * inturrupt4.c
 *
 * Created: 2022-06-20 오후 12:26:21
 *  Author: pknu
 */ 

/*인터럽트로 LED의 좌우 이동 방향 변경하기*/

#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Shift_flag = 1;

SIGNAL(INT5_vect){
	cli(); //전체 인터럽트 금지 -> 금지는 왜 하는거지?
	Shift_flag = 1;
	sei(); //전체 인터럽트 허용
}

SIGNAL(INT7_vect){
	cli();
	Shift_flag = 2;
	sei();
}

int main(){
	unsigned char LED_data = 0x01;
	
	DDRE = 0x00; //입력
	DDRC = 0xff; //출력
	
	EICRB = 0xC8; //INT5를 하강에지, INT7을 상승에지에서 동작하도록 설정
	
	EIMSK = 0xA0; //INT5, 7 허용
	EIFR = 0xA0;  //INT5, 7 플래그 클리어
	
	sei();
	
	while(1){
		PORTC = LED_data;
		if(Shift_flag == 1){ //LED0 ~ LED7 순서로 이동
			if(LED_data == 0x80) LED_data = 0x01;
			
			else LED_data <<= 1; //LED_Data 값을 왼쪽으로 쉬프트
		}
		else if(Shift_flag == 2) //LED7 ~ LED0 순서로 이동
		{
			if(LED_data == 0x01) LED_data = 0x80;
			else LED_data >>= 1; //LED_Data 값을 오른쪽으로 쉬프트
		}
		_delay_ms(500);
	}
	
	//return 0;
}