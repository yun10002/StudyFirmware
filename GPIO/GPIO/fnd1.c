/*
 * fnd1.c
 *
 * Created: 2022-06-17 오후 4:21:31
 *  Author: pknu
 */ 

#define F_CPU 7432800
#include <avr/io.h>
#include <util/delay.h>

int Count_TR(unsigned char flag) {
	int count = 0;
	switch (flag) {
		case 0x01: // SW0을 눌렀을때
		count = 1;
		break;
		case 0x02: // SW1을 눌렀을때
		count = 2;
		break;
		case 0x04: // SW2을 눌렀을때
		count = -1;
		break;
		case 0x08: // SW3을 눌렀을때
		count = -2;
		break;
	}
	return count;
}

int main(){
	unsigned char fnd[] = {0x3f, 0x06, 0x5b, 0x4f,
						   0x66, 0x6d, 0x7d, 0x27,
						   0x7f, 0x6f, 0x77, 0x7c,
						   0x39, 0x5e, 0x79, 0x71};
	unsigned char switch_flag = 0;
	int cnt = 0;
	
	DDRA = 0xff; //포트A를 출력포트로 설정
	DDRD = 0x00; //포트D를 입력포트로 설정
	
	while (1)
	{
		switch_flag = PINE >> 4;
		while(PINE >> 4 != 0x00);
		
		if(switch_flag!=0) //스위치가 눌러졌을 때만 실행
			cnt += Count_TR(switch_flag);
		
		if(cnt < 0) cnt = 0;
		else if(cnt > 15) cnt = 15;
		
		PORTA = fnd[cnt];
		_delay_ms(100);
	}
	
	return 0;
}