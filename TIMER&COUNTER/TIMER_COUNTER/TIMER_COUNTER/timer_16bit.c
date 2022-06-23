/*
 * timer_16bit.c
 *
 * Created: 2022-06-22 오전 10:40:57
 *  Author: pknu
 */ 
/*타이머로 LED 점멸*/

#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;
unsigned char timer1Cnt = 0;

int main(){
	DDRC = 0x0f;
	
	TCCR1A = 0x00;
	TCCR1B = 0x01; // 프리스케일러 1
	
	TCNT1 = 656536-78800; // 
	TIMSK = 0x04;
	TIFR |=1 << TOV1;
	sei();

	while (1)
	{
		PORTC = LED_Data; //포트C로 변수 LED_Data에 있는 데이타 출력
	}
	return 0;
}

SIGNAL(TIMER1_OVF_vect)
{
	cli();
	timer1Cnt++; // timer0Cnt 변수 1 증가
	
	//if(timer1Cnt == 1) // 1ch 28800
	//{
		LED_Data++; // LED_Data 변수 1 증가
		if(LED_Data > 0x0F) LED_Data = 0;
		//timer1Cnt=36736;
	//}
	sei();
}
