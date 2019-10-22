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
unsigned int cnt = 0;
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


enum Led_States{Start, Init, ON_1, Wait_1, ON_2, Wait_2, ON_3, Wait_3 } Led_State;
void Tick_Led();
int main(void){
        DDRA = 0x00;
        PORTA = 0xFF;
	DDRB = 0xFF; 
	PORTB = 0x00;
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
		  Led_State = ON_1;
			break;
		case ON_1:
			Led_State = Wait_1;
			break;
	        case Wait_1:
		  if(!button && !cnt){
		     Led_State = ON_2;		    
		  }  
		  else if(button ){
		     ++cnt;
		     Led_State = Wait_1;
		  }
		  else if(cnt==1){
		     Led_State = Wait_1;	     
		  } 
		  else if(cnt>1){
		     Led_State =  Init;
		  }  
                  break;

	        case ON_2:
		        Led_State = Wait_2;
			break;

	        case  Wait_2:
		  if(!button && !cnt){
		     Led_State = ON_3;		    
		  }  
		  else if(button ){
		     ++cnt;
		     Led_State = Wait_2;
		  }
		  else if(cnt==1){
		     Led_State = Wait_2;	     
		  } 
		  else if(cnt>1){
		     Led_State =  Init;
		  }  
		  break;
     
          	case ON_3:
		        Led_State = Wait_3;
			break;

	        case Wait_3:
		  if(!button && !cnt){
		     Led_State = ON_1;		    
		  }  
		  else if(button ){
		     ++cnt;
		     Led_State = Wait_3;
		  }
		  else if(cnt==1){
		     Led_State = Wait_3;	     
		  } 
		  else if(cnt>1){
		     Led_State =  Init;
		  }  
		  break;
		default:
			break;
	}



	switch(Led_State){
		case Start:
			temp = 0x00;
			cnt = 0;
			break;
		case Init:
			temp = 0x00;
			cnt = 0;
			break;
		case ON_1:
		        temp = 0x01;
			break;
		case Wait_1:
		        break;
		case ON_2:
		       temp = 0x02;
			break;
		case Wait_2:
		        break;
          	case ON_3:
		       temp = 0x04;
			break;
		case Wait_3:
		        break;
		default:
			break;	
	}
	PORTB = temp;
	
}


