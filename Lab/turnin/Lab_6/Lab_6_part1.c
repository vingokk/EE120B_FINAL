/*	Author: wenguang wang
 *      Partner(s) Name: xikang luo
 *	Lab Section:022
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0x00;
unsigned char temp = 0x00;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff(){
	TCCR1B = 0x00;
}
void TimerISR(){
	TimerFlag = 0x01 ;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}


enum Led_States{Start, Init, ON_1, ON_2, ON_3} Led_State;
void Tick_Led();
int main(void){
	
	DDRB = 0xFF; 
	PORTB = 0x00;
	TimerSet(100);
	TimerOn();
	Led_State = Start;
	while(1){
	   Tick_Led();
	while(!TimerFlag){}
	TimerFlag = 0;
	
        }
}
void Tick_Led(){
	switch(Led_State){
		case Start:
		   	Led_State = Init;
			break;
		case Init:
		  Led_State = ON_1;
			break;
		case ON_1:
			Led_State = ON_2;
			break;
		case ON_2:
		        Led_State = ON_3;
			break;
          	case ON_3:
		        Led_State = ON_1;
			break;
		default:
			break;
	}

	switch(Led_State){
		case Start:
			temp = 0x00;
			break;
		case Init:
			temp = 0x00;
			break;
		case ON_1:
		        temp = 0x01;
			break;
		case ON_2:
		       temp = 0x02;
			break;
          	case ON_3:
		       temp = 0x04;
			break;
		default:
			break;	
	}
	PORTB = temp;
	
}


