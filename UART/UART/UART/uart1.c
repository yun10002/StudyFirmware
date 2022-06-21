/*
 * uart1.c
 *
 * Created: 2022-06-21 오전 10:51:29
 *  Author: pknu
 */ 
 /*UART로 스위치 입력 값 보내기*/
 
 #include <avr/io.h>
 #include <avr/interrupt.h>
 
 volatile unsigned char TX_flag = 0;
 volatile char TX_data = 0; //스위치 전송 값 저장 변수
 
 void putch(unsigned char data){
	 while((UCSR0A & 0x20) == 0); //전송 준비 될 때까지 대기
	 UDR0 = data;
	 UCSR0A |= 0x20;
 }
 
 void putch_Str(char *str){ //문자열 출력 함수
	 unsigned char i = 0;
	 while(str[i] != '\0') putch(str[i++]); 
 }
 
 SIGNAL(INT4_vect){
	 cli(); //전체 인터럽트 금지
	 TX_data = '0'; //문자 0 저장
	 TX_flag = 1;
	 sei(); //전체 인터럽트 허용
 }
 
  SIGNAL(INT5_vect){
	  cli(); //전체 인터럽트 금지
	  TX_data = '1'; //문자 1 저장
	  TX_flag = 1;
	  sei(); //전체 인터럽트 허용
  } 
  
  SIGNAL(INT6_vect){
  cli(); //전체 인터럽트 금지
  TX_data = '2'; //문자 2 저장
  TX_flag = 1;
  sei(); //전체 인터럽트 허용
  } 
  
  SIGNAL(INT7_vect){
  cli(); //전체 인터럽트 금지
  TX_data = '3'; //문자 0 저장
  TX_flag = 1;
  sei(); //전체 인터럽트 허용
  }
  
 int main(){
	 DDRE = 0x02; //Rx(입력 0), Tx(출력, 1), SW0~3 입력
	 UCSR0A = 0x00;
	 UCSR0B = 0x18; //Rx, Tx enable
	 UCSR0C = 0x06; //비동기 방식, No Parity bit, 1 Stop bit
	 UBRR0H = 0x00;
	 UBRR0L = 3; //115200 bps
	 
	 EICRB = 0xff; //INT 4, 5, 6, 7을 상승엣지에서 동작하도록 설정 
	 EIMSK = 0xF0; //INT 4, 5, 6, 7 허용
	 EIFR = 0xF0;  //INT 4, 5, 6, 7 플래그 클리어
	 sei();		   //전체 인터럽트 허용
	 
	 while(1){
		 if(TX_flag == 1){
			putch_Str("\n\r Input Switch : ");
			putch(TX_data);
			TX_flag = 0;
		 }
	 }
	 
	 return 0;
 }