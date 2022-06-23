/*
 * CFile1.c
 *
 * Created: 2022-06-22 오후 4:31:48
 *  Author: pknu
 */ 
/*PWM으로 LED 밝기 조절하기*/

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned char Light=0;
	DDRB = 0x10; // 포트B 를 출력포트로 설정
	
	TCCR0 = 0x77; // PC PWM 모드, 1024 분주 ==> 14.4 KHz :
	TCNT0 = 0x00; // 타이머0 카운터를 초기화

	
	while (1)
	{
		for(Light=0;Light<256;Light++)
		{
			OCR0 = Light;
			_delay_ms(10);
		}
		for(Light=256;0<Light;Light--)
		{
			OCR0 = Light;
			_delay_ms(10);
		}
	}
}
