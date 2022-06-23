/*
 * PWM.c
 *
 * Created: 2022-06-23 오전 9:54:31
 * Author : pknu
 */ 
/*PWM으로 PIEZO 올리기(도레미파솔라시도)*/
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

//피아노 음계에 해당하는 pwm 주파수
unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};
	
int main(void)
{
	unsigned char piano=0;
	
	DDRB = 0x80; // PWM 출력, OCR1C
	TCCR1A |= 0x0A; // COM1C(1:0)=“10”, OC1C핀사용, WGM3(1:0)=“10”
	TCCR1B |= 0x19; // WGM3(3:2)=“11”, CS3(2:0)=“001” 1분주 사용
	TCCR1C = 0x00; // WGM3(3:0)=“1110”, Fast PWM, 모드 14
	TCNT1 = 0x0000; // 타이머1 카운터 초기화

	while(1)
	{
		ICR1 = 7372800/DoReMi[piano]; // 버튼에 맞는 음향을 연주
		OCR1C = ICR1/4; // 50% 듀티비
		piano++; // piano 변수 1증가
		if(8 < piano) piano = 0; // piano가 9가 되면 초기화
		_delay_ms(1000);
	}
}
