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


enum Led_States{Start, Init, Waitrise, Increment, Decrement, Waitfall } Led_State;
void Tick_Led();

int main(void){
        DDRA = 0x00;   PORTA = 0xFF;
	DDRC = 0xFF;   PORTC = 0x00;
	DDRD = 0xFF;   PORTD = 0x00;
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
        unsigned char button =(~PINA &0x02);
	
   switch(State){
      case Start:
             temC = 0x00;
	     State = Init;
	     break;
	  
	  case Init:
             PORTC = 0x07;
	     State = Waitrise;
	     break;
	  
	  case Waitrise:
	     if(!(PINA&0x01) && !(PINA&0x02)){
	     State = Waitrise;
	     }
	     else if(!(PINA&0x01) && (PINA&0x02) ){
	     State = Decrement;
	     }
	     else if((PINA&0x01) && !(PINA&0x02)){
	     State = Increment;
	     }
	     else if((PINA&0x01) && (PINA&0x02)){
	     State = Init;
	     }
	     break;
	  
	  case Increment:
	     State = Waitfall;
	     break;
	  
	  case Decrement:
	     State = Waitfall;
	     break;
	  
	  case Waitfall:
	     if((PINA&0x01) ^ (PINA&0x02)){
	     State = Waitfall;
	     }
	     else if(!(PINA&0x01) && !(PINA&0x02)){
	     State = Waitrise;
	     }
	     else if((PINA&0x01) && (PINA&0x02)){
	     State = Init;
	     }
	     break;
	  
	  default:
	     break;
	 	  
   }
   switch(State){
      case Start:
	  break;
	  
      case Init:
	     PORTC = 0x07;
		 break;
		
	  case Waitrise:
	     PORTC = PORTC;
	     break;
		 
	  case Increment:
	     if(PORTC < 9){
	     PORTC = PORTC + 1;
		 }
		 break;
		 
	  case Decrement:
	     if(PORTC > 0){
	     PORTC = PORTC - 1;
	     }
		break;

          case Waitfall:
               PORTC = PORTC;
 
	   default:
             PORTC = PORTC;   
	     break;
   
   }	   

    
	PORTB = temp;
	
}


