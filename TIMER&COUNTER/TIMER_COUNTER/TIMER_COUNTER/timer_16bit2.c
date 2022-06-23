/*
 * timer_16bit2.c
 *
 * Created: 2022-06-22 오전 11:39:56
 *  Author: pknu
 */ 
/*타이머를 이용한 스위치 누른 시간 구하기*/

#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,
							  0X7C,0X07,0X7F,0X67,0X77,0X7C,
							  0X39,0X5E,0X79,0X71,0X08,0X80};							  volatile unsigned char time_s = 0; //초를 세는 변수volatile unsigned char FND_flag = 0, edge_flag = 0;int main(){	DDRE = 0x00;	DDRA = 0xff;		TCCR3A = 0x00;		TCCR3B = 0x45;
	ETIMSK = 0x20; // 입력캡처 인터럽트3 활성화
	ETIFR |= 1 << ICF3;
	sei();
	PORTA = FND_DATA_TBL[0]; //포트A에 FND Table의 값을 출력
	
	while (1) {
		if(FND_flag) {
			if(time_s > 15) // 최대 1.5초까지 표시(F)
			time_s = 15;
			PORTA = FND_DATA_TBL[time_s]; // 포트A에 FND Table 값 출력
			FND_flag = 0;
		}
	}	return 0;}