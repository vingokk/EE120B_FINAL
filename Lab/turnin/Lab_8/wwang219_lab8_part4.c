  /*    Author: Wenguang Wang        Email:wangwenguang98@gmail.com
 *      Partner(s) Name: xikang luo  Email: luoxikang@csu.edu.cn
 *      Lab Section: 022 
 *      Assignment: Lab #8  Exercise #4 
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <asf.h>
#define MAX 0x9B

void ADC_init(){
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE); 
}


unsigned char Pow(short Light)
{
	unsigned char Result = 1;
	for (unsigned char i=0; i<Light; i++ )
	{
		Result = Result*2;
	}
	return Result;
}

int main (void)
{
	

	board_init();
	ADC_init();
	DDRA = 0x00; DDRC = 0xFF; DDRB = 0xFF;
	PORTC = 0x00; PORTB = 0x00;
	unsigned long Light = 0;
	
	while (1){
		Light = ADC;
		Light = Light * 1024 / MAX;
		Light = Light >> 7 ;
		PORTC = Pow(Light);
	}


}
