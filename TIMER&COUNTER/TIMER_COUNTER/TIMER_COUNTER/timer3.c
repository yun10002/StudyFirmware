/*
 * timer3.c
 *
 * Created: 2022-06-21 오후 5:06:32
 *  Author: pknu
 */ 
/*타이머와 인터럽트로 FND 점멸*/

#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,
							  0X7C,0X07,0X7F,0X67,0X77,0X7C,
							  0X39,0X5E,0X79,0X71,0X08,0X80};

volatile unsigned char time_s = 0; //0.5초를 세는 변수
volatile unsigned char Time_STOP = 0; //숫자 증가 및 정지 시키는 변수

unsigned char timer0Cnt = 0;

int main(){
	DDRE = 0x00; //입력
	DDRA = 0xff; //출력
	
	TCCR2 = 0x05; //프리스케일러 1024
	OCR2 = 144; //0.01초마다 한 번씩 인터럽트 발생
	TIMSK |= 1 << OCF2;
	
	EICRB = 0x03; //INT4를 상승엣지에서 동작하도록 설정
	EIMSK = 0x10; //INT4 허용
	EIFR = 0x10; //INT4 플래그 클리어
	
	sei();
	
	while(1){
		PORTA = FND_DATA_TBL[time_s]; //포트A에 FND 연결 및 tbl값 출력
	}
	
	return 0;
}

SIGNAL(TIMER2_COMP_vect){
	cli(); //전체 인터럽트 금지
	OCR2 += 72; //0.01초 후에 인터럽트 발생
	timer0Cnt++;
	if(timer0Cnt == 50){ //0.01s * 50 = 0.5s -> 0.5초를 얻기 위한 카운트 횟수
		if(Time_STOP == 0){
			if(time_s >= 16) time_s = 0; //16되면 0으로 초기화
			else time_s++; //time_s 변수는 16까지만 증가
		}
	timer0Cnt = 0;
	}
	sei();
}

SIGNAL(INT4_vect){
	cli(); //전체인터럽트 금지
	
	if(Time_STOP == 0) 
		Time_STOP = 1; //Time_STOP이 0인 경우에만 1 입력
	else Time_STOP = 0; //반대
	
	sei(); //전체 인터럽트 허용
}