/*
 * StepMotor.c
 *
 * Created: 2022-06-23 오후 3:07:59
 * Author : pknu
 */ 
/*1상 여자 방식으로 스텝 모터 돌리기*/

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0x20; //MOTOR1_EN을 출력 포트로 설정
	DDRD = 0xF0; //STEP 0~3을 출력 포트로 설정
	PORTB &= ~0x20; //M1 Disable, DC 모터 정지
    
    while (1) 
    {
		PORTD = 0x10; //1step
		_delay_ms(10);
		PORTD = 0x20; //2step
		_delay_ms(10);
		PORTD = 0x40; //3step
		_delay_ms(10);
		PORTD = 0x80; //4step
		_delay_ms(10);
    }
}

