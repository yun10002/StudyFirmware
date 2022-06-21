/*
 * interrupt5.c
 *
 * Created: 2022-06-20 오후 2:24:33
 *  Author: pknu
 */ 

/*인터럽트로 FND 컨트롤*/

#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char time_STOP = 0;

SIGNAL(INT5_vect){
	cli(); 
	
	if(time_STOP == 0) time_STOP = 1;
	else time_STOP = 0;
	sei();
}

int main(){
	unsigned char fnd[] = {0x3f, 0x06, 0x5b, 0x4f,
						   0x66, 0x6d, 0x7c, 0x07,
						   0x7f, 0x67, 0x77, 0x7c,
						   0x39, 0x5e, 0x79, 0x71, 0x08, 0x80}; //표시할 글자 데이터
	
	unsigned char cnt = 0; //fnd 카운터 변수
	
	DDRE = 0x00; //입력
	DDRA = 0xff; //출력
	
	EICRB = 0x0c; //INT5 상승에지에서 동작하도록 설정
	EIMSK = 1 << INT5; //0x20; //INT5 허용
	EIFR = 0x20;  //INT5 플래그 클리어
	sei();
	
	while(1){
		PORTA = fnd[cnt];
		if(time_STOP == 0){
			cnt++;
			if(cnt>17) cnt=0; //fnd 테이블 크기 초과 방지 
		}
		_delay_ms(500);
	}
	
	//return 0;
}