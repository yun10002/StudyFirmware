/*
 * TIMER_COUNTER.c
 *
 * Created: 2022-06-21 오후 3:33:56
 * Author : pknu
 */ 
/*타이머로 LED 점멸*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;
unsigned char timer0Cnt = 0;
SIGNAL(TIMER0_OVF_vect);

int main(void)
{
	DDRC =  0x0f; //출력포트
	TCCR0 = 0x07;
    TCNT0 = 112; 
	TIMSK = 0x01;
	TIFR |= 1 << TOV0;
	sei();
	
	while(1){
		PORTC = LED_Data;
	}
	
	return 0;
}

SIGNAL(TIMER0_OVF_vect){
	cli();
	TCNT0 = 112;
	timer0Cnt++;
	if(timer0Cnt == 100){ //0.01s*100=1s
		LED_Data++;
		if(LED_Data>0x0f) LED_Data=0;
		timer0Cnt=0;
	}
	sei();
}

