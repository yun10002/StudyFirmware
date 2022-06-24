/*
 * pwm3.c
 *
 * Created: 2022-06-23 오전 11:09:37
 *  Author: pknu
 */ 
/*키보드 입력값(1~8)에 따라 PIEZO 올리기(키패드로 피아노 연주)*/

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};volatile unsigned char sound_flag = 1;

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

void putch_USART0(char doremi)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = doremi;
}

unsigned char get_doremi(){
	unsigned char doremi;
	while((UCSR0A & 0x80) == 0); //데이터 수신할때까지 대기
	doremi = UDR0; //수신된 데이터 UDR0에 저장
	UCSR0A |= 0x80;
	
	switch (doremi)
	{
		case 49: //키보드 입력 값 1
			doremi='d'; //도
			break;
		case 50: //키보드 입력 값 2
			doremi='r'; //레
			break;
		case 51: //키보드 입력 값 3
			doremi='m'; //미
			break;
		case 52: //키보드 입력 값 4
			doremi='f'; //파
			break;
		case 53: //키보드 입력 값 5
			doremi='s'; //솔
			break;
		case 54: //키보드 입력 값 6
			doremi='l'; //라
			break;
		case 55: //키보드 입력 값 7
			doremi='t'; //시
			break;
		case 56: //키보드 입력 값 8
			doremi='D'; //도
			break;
		default:
		/* Your code here */
			break;
	}
	return doremi; //읽어온 문자 반환
}

int main(){
	unsigned char doremi = 0;
	
	DDRE = 0xfe; //Rx(입력 0), Tx(출력 1)
	
	UCSR0A = 0x00;
	UCSR0B = 0x18; //Rx, Tx enable
	UCSR0C = 0x06; //비동기 방식, No Parity bit, 1 Stop bit
	
	UBRR0H = 0x00;
	UBRR0L = 3; //115200 bps
	
	TCCR3A = 0x00;
	TCCR3B = 0x19;
	TCCR3C = 0x00; // WGM3(3:0) = “1110”, Fast PWM, 모드 14
	TCNT3 = 0x0000; // 타이머3 카운터 초기화
	
	while(1){
		doremi = get_doremi();
		putch_USART0(doremi);
		
		switch (doremi)
		{
			case 'd':
				ICR3 = 7372800/DoReMi[0]/4;
				break;
			case 'r':
				ICR3 = 7372800/DoReMi[1]/4;
				break;
			case 'm':
				ICR3 = 7372800/DoReMi[2]/4;
				break;
			case 'f':
				ICR3 = 7372800/DoReMi[3]/4;
				break;
			case 's':
				ICR3 = 7372800/DoReMi[4]/4;
				break;
			case 'l':
				ICR3 = 7372800/DoReMi[5]/4;
				break;
			case 't':
				ICR3 = 7372800/DoReMi[6]/4;
				break;
			case 'D':
				ICR3 = 7372800/DoReMi[7]/4;
				break;
			default:
				/* Your code here */
				break;
		}
		TCCR3A = 0x40; // PE4로 출력
		sound_flag = 1; // 부저 음이 발생하도록 설정
		
		if(sound_flag)
		{
			_delay_ms(200);
			TCCR3A = 0x00; //부저 소리 off
			sound_flag = 0;
		}
	}
	
	
	return 0;
}