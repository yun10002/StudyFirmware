/*
 * uart3.c
 *
 * Created: 2022-06-21 오후 12:13:37
 *  Author: pknu
 */ 
/*UART로 PC와 데이터 주고받기 응용 -> 구구단 출력*/

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

/*
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
*/
void putch_USART0(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void puts_USART0(char *str)
{
	while(*str != 0){
		putch_USART0(*str);
		str++;
	}
}

unsigned char get_dan(){
	unsigned char dan;
	while((UCSR0A & 0x80) == 0); //데이터 수신할때까지 대기
	dan = UDR0; //수신된 데이터 UDR0에 저장
	UCSR0A |= 0x80;
	
	return dan; //읽어온 문자 반환
}

int main(){
	unsigned char text[]=
	"[GUGUDAN]\r\n? times table >> ";
	unsigned char dan = 0, i = 0;
	
	DDRE = 0xfe; //Rx(입력 0), Tx(출력 1)
	
	UCSR0A = 0x00;
	UCSR0B = 0x18; //Rx, Tx enable
	UCSR0C = 0x06; //비동기 방식, No Parity bit, 1 Stop bit
	
	UBRR0H = 0x00;
	UBRR0L = 3; //115200 bps
	
	while(text[i] != '\0'){
		putch_USART0(text[i++]);
	}
	
	dan = get_dan(); //몇 단인지 입력 값 받아오기
	putch_USART0(dan); //터미널에 출력해주기
	
	unsigned char temp[] = {0, };
	for(i = 1; i < 10 ; i++){
		//dan이 char형이라서 10진수 값으로 변환해주기 위해 48 빼줌(아스키코드표 참고)
		sprintf(temp, "\r\n%d X %d = %d\r\n", dan-48, i, (dan-48)*i);
		puts_USART0(temp);
		_delay_ms(100);
	}

	return 0;
}