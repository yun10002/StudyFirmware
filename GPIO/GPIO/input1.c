/*
* input1.c
*
* Created: 2022-06-17 오후 3:29:52
*  Author: pknu
*/

#define F_CPU 7432800
#include <avr/io.h>
#include <util/delay.h>

int main(){
	DDRD = 0x00; //포트D 입력으로 설정
	DDRA = 0xff;  //포트A 출력으로 설정
	
	while(1){
		
		PORTA=PIND;
		
		//if(PIND==0x01){
		//PORTA=0x01; //포트D의 입력값이 0x01이면 포트A의 0번비트 출력
		//_delay_ms(300);
		//PORTA=0x00;
		//}
	}

	return 0;
}