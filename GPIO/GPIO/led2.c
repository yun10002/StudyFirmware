/*
 * led2.c
 *
 * Created: 2022-06-17 오후 1:54:42
 *  Author: pknu
 */ 
#define F_CPU 7432800
#include <avr/io.h>
#include <util/delay.h>

int main(){
	/*
	DDRA = 0xff;
	
	while(1){
		PORTA=0x01;
		_delay_ms(1000);
		for(int i= 0 ; i < 8 ; i++){
		  PORTA=PORTA<<1;
		  if(i==7) break;
		  _delay_ms(1000);
		}
	}
	불 하나씩 들어오게 하기
	*/
	
	DDRA = 0xff;
	unsigned char led=0x01;
	
	while(1){
		led=0x01;
		
		for(int i=0; i<8; i++){	
			PORTA = ~(led);
			_delay_ms(1000);
			led=led<<1;
		}
	}
	
	return 0;
}