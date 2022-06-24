/*
 * MiniProject.c
 *
 * Created: 2022-06-24 오전 9:42:14
 * Author : 최윤진
 */ 

/*

[Digital DoorLock]

1. 4자리 비밀번호를 설정하고 키패드를 통해서 패스워드 입력.
   맞으면 스탭모터 구동(도어 open), LCD 창에 "open", 부저음 발생.
   틀리면 LCD 창에 "Error number", 에러 부저음 발생
   
2. Interrupt button 을 누르면 통신을 통해서 비밀번호 입력.
	이후 동작은 동일.
	
*/

#include <avr/io.h>
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "Lcd.h"

unsigned char pinNum[] = "0714";
unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};

//키패드 초기화 함수
void init_keypad()
{
	DDRA = 0xF8; //0b 1111 1000
	PORTA = 0x07; //0b 0000 0111
}

//키패드 값
unsigned char keyscan()
{
	//while(1){
		PORTA = 0x08; //0b 0000 1000
		_delay_ms(1);
		if((PINA & 0x07) == 0x01) return '1';
		else if((PINA & 0x07) == 0x02) return '2';
		else if((PINA & 0x07) == 0x04) return '3';
		_delay_ms(10);
	
		PORTA = 0x10;		// 0x10
		_delay_ms(1);
		if((PINA & 0x07) == 0x01) return '4';
		else if((PINA & 0x07) == 0x02) return '5';
		else if((PINA & 0x07) == 0x04) return '6';
		_delay_ms(10);
	
		PORTA = 0x20;		// 0x20
		_delay_ms(1);
		if((PINA & 0x07) == 0x01) return '7';
		else if((PINA & 0x07) == 0x02) return '8';
		else if((PINA & 0x07) == 0x04) return '9';
		_delay_ms(10);
	
		PORTA = 0x40;		// 0x40
		_delay_ms(1);
		if((PINA & 0x07) == 0x01) return '*';
		else if((PINA & 0x07) == 0x02) return '0';
		else if((PINA & 0x07) == 0x04) return '#';
		_delay_ms(10);
	//}
	
	return 0;
}

//문자 출력 함수
void putch_USART0(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

//문자열 출력 함수
void puts_USART0(char *str)
{
	while(*str != 0){
		putch_USART0(*str);
		str++;
	}
}

//문자 받아오는 함수
unsigned char get_pin(){
	unsigned char pin;
	while((UCSR0A & 0x80) == 0); //데이터 수신할때까지 대기
	pin = UDR0; //수신된 데이터 UDR0에 저장
	UCSR0A |= 0x80;
	
	return pin; //읽어온 문자 반환
}

void init_USART0(void)
{
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0A = 0x00;
	//UCSR0C = (1<<UPM01)|(1<<UCSZ01)|(1<<UCSZ00);
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	UBRR0H = 0x00;
	UBRR0L = 3;
	//sei();
}

//스텝모터 작동 함수
void stepMotorOn(){
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

void init_PIEZO(void){
	DDRE = 0x08; //포트E PE3을 출력
	
	TCCR3A = 0x00;
	TCCR3B = 0x19;
	TCCR3C = 0x00; // WGM3(3:0) = “1110”, Fast PWM, 모드 14
	TCNT3 = 0x0000; // 타이머3 카운터 초기화
}

void sound(){
	TCCR3A = 0x40; //PE4로 출력??
	_delay_ms(200);
	TCCR3A = 0x00; //부저 소리 off
}

//비번 맞을 때 나는 소리
void correctSound(){
	ICR3 = 7372800/DoReMi[0]/4;
	sound();
	
	ICR3 = 7372800/DoReMi[2]/4;
	sound();
	
	ICR3 = 7372800/DoReMi[4]/4;
	sound();
	
	ICR3 = 7372800/DoReMi[7]/4;
	TCCR3A = 0x40;
	_delay_ms(500);
	TCCR3A = 0x00; //부저 소리 off
}

//비번 틀릴 때 나는 소리
void wrongSound(){
	for(unsigned char i = 0 ; i < 3 ; i++){
		ICR3 = 7372800/DoReMi[2]/4;
		TCCR3A = 0x40;
		_delay_ms(150);
		TCCR3A = 0x00; //부저 소리 off
		
		ICR3 = 7372800/DoReMi[0]/4;
		TCCR3A = 0x40; //PE4로 출력??
		_delay_ms(150);
		TCCR3A = 0x00; //부저 소리 off
	}
}

int main(void)
{
	//keyPad 사용에 필요
	DDRF=0XFF;
	
	init_keypad();
	
	char text1[] = "*DoorLock System";
	char text2[] = "Insert PIN: ";
	char text3[] = "Door Open!";
	char text4[] = "Retry!";
	
	unsigned char pinTemp[10] = "****";
	unsigned char i = 0; //카운터 변수
	
	DDRC = 0xff; //C를 출력포트로 사용
	DDRB = 0xff;
	
	init_PIEZO();
	
	while (1){
		i = 0; //카운터 변수 초기화
		
		Lcd_Init();
		Lcd_Clear();
		_delay_ms(200);
		
		Lcd_Pos(0, 0); 
		Lcd_STR(text1); //LCD 윗줄에 text1 출력
		Lcd_Pos(1, 0);
		Lcd_STR(text2); //LCD 밑줄에 text2 출력
		
		while(i < 4){
			unsigned char pin = keyscan();
			if(pin != 0){
				pinTemp[i++] = pin;
				_delay_ms(200);
				Lcd_STR("*");
				ICR3 = 7372800/DoReMi[3]/4;
				sound();
			}
			//Lcd_STR(pinTemp); //pinTemp값 확인 -> 잘 들어감
		}
		_delay_ms(200);
		
		if(strcmp(pinNum, pinTemp) == 0){
			Lcd_Clear();
			Lcd_Pos(0, 0);
			Lcd_STR(text3); //LCD 윗줄에 text1 출력
			correctSound();
			stepMotorOn();
			break;
		}
		else{
			Lcd_Clear();
			Lcd_Pos(0, 0);
			Lcd_STR(text4); //LCD 윗줄에 text1 출력
			wrongSound();
		}
		
	}
	
	
	/*
	//인터럽트 발생시 UART로 전환
	init_USART0();
	
	
	puts_USART0("\r\n[DoorLock System]");
	while(1){
		puts_USART0("\r\nInsert PIN >>"); //화면에 text 출력
		
		while(i < 4){ //4자리 PIN 입력받기
			pinTemp[i++] = get_pin();
			putch_USART0('*');
		}	
		//puts_USART0(pinTemp); //입력 값 확인 -> 제대로 들어옴
		i = 0; //카운터 변수 초기화
		
		if(strcmp(pinNum, pinTemp) == 0){
			puts_USART0("\r\nDoor open!");
			correctSound();
			stepMotorOn();
			break;
		}
		else{
			puts_USART0("\r\nRetry!");
			wrongSound();
		}
	}
	*/
	
	
	return 0;
}

