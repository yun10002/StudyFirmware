/*
 * pwm2.c
 *
 * Created: 2022-06-23 오전 10:11:26
 *  Author: pknu
 */ 
/*스위치 입력(스위치0~7) 값에 따라 PIEZO 올리기*/

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//피아노 음계에 해당하는 PWM 주파수
unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};volatile unsigned char sound_flag = 1;

int main(){
	DDRE = 0x08; //포트E PE3을 출력
	
	TCCR3A = 0x00;
	TCCR3B = 0x19;
	TCCR3C = 0x00; // WGM3(3:0) = “1110”, Fast PWM, 모드 14
	TCNT3 = 0x0000; // 타이머3 카운터 초기화
	
	EICRA = 0xFF; // 인터럽트 0, 1, 2, 3을 상승엣지에서 동작하도록 설정
	EICRB = 0xFF; // 인터럽트 4, 5, 6, 7을 상승엣지에서 동작하도록 설정
	EIMSK = 0xFF; // 인터럽트 0~7을 허용??
	EIFR = 0xFF; // 인터럽트 4, 5, 6, 7 플래그를 클리어
	sei();
	while(1)
	{
		if(sound_flag)
		{
			_delay_ms(500);
			TCCR3A = 0x00; //부저 소리 off
			sound_flag = 0;
		}
	}
}

SIGNAL(INT0_vect) // 인터럽트 서비스 루틴
{
	cli(); // 전체 인터럽트를 금지
	ICR3 = 7372800/DoReMi[0]/4; // 도
	TCCR3A = 0x40; // PE4로 출력
	sound_flag = 1; // 부저 음이 발생하도록 설정
	sei(); // 전체 인터럽트를 허용
}

SIGNAL(INT1_vect) // 인터럽트 서비스 루틴
{
	cli(); // 전체 인터럽트를 금지
	ICR3 = 7372800/DoReMi[1]/4; // 레
	TCCR3A = 0x40; // PE4로 출력
	sound_flag = 1; // 부저 음이 발생하도록 설정
	sei(); // 전체 인터럽트를 허용
}

SIGNAL(INT2_vect) // 인터럽트 서비스 루틴
{
	cli(); // 전체 인터럽트를 금지
	ICR3 = 7372800/DoReMi[2]/4; // 미
	TCCR3A = 0x40; // PE4로 출력
	sound_flag = 1; // 부저 음이 발생하도록 설정
	sei(); // 전체 인터럽트를 허용
}

SIGNAL(INT3_vect) // 인터럽트 서비스 루틴
{
	cli(); // 전체 인터럽트를 금지
	ICR3 = 7372800/DoReMi[3]/4; // 파
	TCCR3A = 0x40; // PE4로 출력
	sound_flag = 1; // 부저 음이 발생하도록 설정
	sei(); // 전체 인터럽트를 허용
}

SIGNAL(INT4_vect) // 인터럽트 서비스 루틴
{
	cli(); // 전체 인터럽트를 금지
	ICR3 = 7372800/DoReMi[4]/4; // 솔
	TCCR3A = 0x40; // PE4로 출력
	sound_flag = 1; // 부저 음이 발생하도록 설정
	sei(); // 전체 인터럽트를 허용
}

SIGNAL(INT5_vect) // 인터럽트 서비스 루틴
{
	cli(); // 전체 인터럽트를 금지
	ICR3 = 7372800/DoReMi[5]/4; // 라
	TCCR3A = 0x40; // PE4로 출력
	sound_flag = 1; // 부저 음이 발생하도록 설정
	sei(); // 전체 인터럽트를 허용
}

SIGNAL(INT6_vect) // 인터럽트 서비스 루틴
{
	cli(); // 전체 인터럽트를 금지
	ICR3 = 7372800/DoReMi[6]/4; // 시
	TCCR3A = 0x40; // PE4로 출력
	sound_flag = 1; // 부저 음이 발생하도록 설정
	sei(); // 전체 인터럽트를 허용
}

SIGNAL(INT7_vect) // 인터럽트 서비스 루틴
{
	cli(); // 전체 인터럽트를 금지
	ICR3 = 7372800/DoReMi[7]/4; // 도
	TCCR3A = 0x40; // PE4로 출력
	sound_flag = 1; // 부저 음이 발생하도록 설정
	sei(); // 전체 인터럽트를 허용
}
