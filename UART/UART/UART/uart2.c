/*
 * uart2.c
 *
 * Created: 2022-06-21 오전 11:18:17
 *  Author: pknu
 */ 

/*UART로 PC와 데이터 주고받기*/

#include <avr/io.h>

void putch(unsigned char data){
	while((UCSR0A & 0x20) == 0); //전송 준비될 때까지 대기
	UDR0 = data; //데이터를 UDR0에 쓰면 전송
	UCSR0A |= 0x20;
}

unsigned char getch(){
	unsigned char data;
	while((UCSR0A & 0x80) == 0); //데이터 수신할때까지 대기
	data = UDR0; //수신된 데이터 UDR0에 저장
	UCSR0A |= 0x80;
	
	return data; //읽어온 문자 반환
}

int main(){
	unsigned char text[]=
	"\r\nWelcome! edgeiLAB\r\n USART 0 Test Program.\r\n";
	
	unsigned char echo[] = "ECHO >> ";
	unsigned char i = 0;
	
	DDRE = 0xfe; //Rx(입력 0), Tx(출력 1)
	
	UCSR0A = 0x00;
	UCSR0B = 0x18; //Rx, Tx enable
	UCSR0C = 0x06; //비동기 방식, No Parity bit, 1 Stop bit
	
	UBRR0H = 0x00;
	UBRR0L = 3; //115200 bps
	
	
	while(text[i] != '\0'){
		putch(text[i++]);
	}

	i = 0; //카운터변수 초기화
	while(echo[i] != '\0'){
		putch(echo[i++]);
	}
	
	while(1){
		putch(getch()); //getch()로 입력받은 문자를 다시 putch()로 문자열 출력
	}

	return 0;
}