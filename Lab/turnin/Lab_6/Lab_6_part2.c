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
unsigned char button =0x00;
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


enum Led_States{Start, Init, Down, Stop, Up } Led_State;
void Tick_Led();
int main(void){
        DDRA = 0x00;   PORTA = 0xFF;
	DDRB = 0xFF; 	PORTB = 0x00;
	TimerSet(300);
	TimerOn();
	Led_State = Start;
	while(1){
	   Tick_Led();
	while(!TimerFlag){}
	TimerFlag = 0;
	
        }
}
void Tick_Led(){
        unsigned char button =(~PINA &0x01);
	switch(Led_State){
	   case Start:
	      Led_State = Init;
	      break;

	   case Init:
	      Led_State = Down;
	      break;

	   case Down:
	     if(!button && (temp==0x04)){
	       Led_State = Up;
	     }
	     else if(button){	       
               Led_State = Stop;
	     }
	     else{
	       Led_State = Down;
	     }
	     break;

	   case Stop:
	     if(!button){
	       Led_State = Stop;
	     }
	     else if(button){	       
               Led_State = Init;
	     }
	     else{
	       Led_State = Stop;
	     }
	     break;

           case Up:
	     if(!button && (temp==0x01)){
	       Led_State = Down;
	     }
	     else if(button){	       
               Led_State = Stop;
	     }
	     else{
	       Led_State = Up;
	     }
	     break;
	
	   default:
	   break;
	}



     switch(Led_State){
	 case Start:
	    temp = 0x00;
	    break;
	 case Init:
	    temp = 0x01;
	    break;

         case Down:
	    temp = temp << 1;
	    break;
         case Stop:
            temp = temp;
            break;
         case Up:
	    temp = temp >> 1;
	    break;	
	default:
	    break;	
	}
	PORTB = temp;
	
}


