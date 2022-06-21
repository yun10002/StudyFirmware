/*
 * timer2.c
 *
 * Created: 2022-06-21 오후 4:48:13
 *  Author: pknu
 */ 
/*타이머를 이용한 디지털 시계*/

#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,
						   	  0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,
							  0X79,0X71,0X08,0X80};
							
volatile unsigned char time_s = 0;
unsigned char timer0Cnt = 0;

int main(){
	DDRA = 0xff; //출력
	
	TCCR0 = 0x07;
	OCR0 = 72; //0.01초마다 한번씩 인터럽트 발생
	TIMSK = 0x02; //출력비교 인터럽트 활성화
	TIFR |= 1 << OCF0;
	sei();
	
	while(1){
		PORTA = FND_DATA_TBL[time_s];
	}
	
	return 0;
}

SIGNAL(TIMER0_COMP_vect){
	cli();
	OCR0 += 72; // 0.01초 후에 인터럽트 발생
	timer0Cnt++; // timer0Cnt 변수 1 증가
	// 0.01s * 100 = 1s // 1초를 얻기 위한 카운트 횟수
	if(timer0Cnt == 100)
	{
		if(time_s >= 16)
		time_s = 0; // time_s 변수는 16까지만 증가
		else time_s++; // 16되면 0으로 초기화
		timer0Cnt=0;
	}
	sei();
}
