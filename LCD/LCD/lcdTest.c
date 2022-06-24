/*
 * lcdTest.c
 *
 * Created: 2022-06-20 오후 2:55:37
 *  Author: pknu
 */ 

#define F_CPU 7372800UL
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Lcd.h"

/*LCD 테스트*/
//int main(){ 
	//Byte str1[] = " LCD TEST";
	//Byte str2[] = " ATmega 128A";
	//
	//DDRA = 0xff; //A를 출력포트로 사용
	//DDRB = 0xff;
	//
	//Lcd_Init();
	//Lcd_Clear();
	//_delay_ms(1000);
	//Lcd_Pos(0, 0);
	//Lcd_STR(str1);
	//Lcd_Pos(1, 0);
	//Lcd_STR(str2);
	//
	//return 0;
//}

/*LCD에 구구단 출력하기*/
//int main(){
	//DDRA = 0xff; //A를 출력포트로 사용
	//DDRB = 0xff;
	//
	//Byte dan[16] = {0,};
	//Byte gugu[16] = {0,};
	//Byte gugudan[16] = {
//
	//
	//Lcd_Init();
	//Lcd_Clear();
	//_delay_ms(1000);
	//while(1){
		//Lcd_Pos(0, 0);
		//Lcd_STR("GUGUDAN");
		//for(int i = 2; i < 10; i++){
			//sprintf(dan, "%dDan ", i);
			//for(int j = 1; j < 10; j++){
				//sprintf(gugu, "%dX%d=%d", i, j , i*j);
				//sprintf(gugudan, "%s%s", dan, gugu);
				//Lcd_Pos(1, 0);
				//Lcd_STR(gugudan);
				//_delay_ms(500);
			//}
		//}
	//}
	//
	//return 0;
//}

/*구구단 출력 중 인터럽트 발생시 LCD에 알림*/
volatile unsigned char occured = 0;

SIGNAL(INT5_vect){
	cli();

	if(occured == 0) occured=1;
	else occured=0;
	
	//sei();
}

int main(){
	DDRE = 0x00; //E를 입력포트
	DDRA = 0xff; //A를 출력포트로 사용
	DDRB = 0xff; //B도 출력포트!
	
	EICRB = 0x0c; //INT5 상승에지에서 동작하도록 설정
	EIMSK = 1 << INT5; //0x20; //INT5 허용
	EIFR = 0x20;  //INT5 플래그 클리어
	sei();	

	Byte dan[16] = {0,};
	Byte gugu[16] = {0,};
	Byte gugudan[16] = {0,};

	
	Lcd_Init();
	Lcd_Clear();
	_delay_ms(1000);
	while(1){
		Lcd_Pos(0, 0);
		if(occured==0) {
			Lcd_Clear();
			_delay_ms(10);
			Lcd_STR("GUGUDAN");
			for(int i = 2; i < 10; i++){
				sprintf(dan, "%dDan ", i);
				for(int j = 1; j < 10; j++){
					sprintf(gugu, "%dX%d=%d", i, j , i*j);
					sprintf(gugudan, "%s%s", dan, gugu);
					Lcd_Pos(1, 0);
					Lcd_STR(gugudan);
					_delay_ms(500);
				}
			}
		}
		else{
			Lcd_Clear();
			Lcd_STR("! INTERRUPT");
			Lcd_Pos(1, 0);
			Lcd_STR("  OCCURED");
		}
	} //2022.06.20수정해야할 듯 ㅠ
	
	return 0;
}