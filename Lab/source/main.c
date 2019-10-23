/*	Author: wenguang wang
 *      Partner(s) Name: xikang luo
 *	Lab Section:022
 *	Assignment: Lab #7  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0x00;
unsigned int tempC = 0;
unsigned char button0 = 0x00;
unsigned char button1 = 0x00;

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


enum States{Start, Init, Waitrise, Increment, Decrement, Waitfall }State;
void Tick_Led();

int main(void){
        DDRA = 0x00;   PORTA = 0xFF;
	DDRC = 0xFF;   PORTC = 0x00;
	DDRD = 0xFF;   PORTD = 0x00;

        LCD_init();

	TimerSet(500);
	TimerOn();
	State = Start;
	while(1){
	   Tick_Led();
           LCD_ClearScreen();
           LCD_Cursor(1);
           LCD_WriteData (tempC + '0');
	   while(!TimerFlag){}
           TimerFlag = 0;
        }
}
void Tick_Led(){
   unsigned char button0 = (~PINA & 0x01);
   unsigned char button1 = (~PINA & 0X02);
   switch(State){
           case Start:
             tempC= 0;
	     State = Init;
	     break;
	  
	  case Init:
             tempC = 0;
	     State = Waitrise;
	     break;
	  
	  case Waitrise:
	     if(!button0 && !button1){
	     State = Waitrise;
	     }
	     else if(!button0 && button1 ){
	     State = Decrement;
	     }
	     else if(button0 && !button1){
	     State = Increment;
	     }
	     else if(button0 && button1){
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
	     if(!button0 && button1){
	       State = Decrement;
	     }
	     else if(button0 && !button1){
	       State = Increment;
	     }
	     else if(button0 && button1){
	       State = Init;
	     }
	     else{
	       State = Waitrise;
	     }
	     break;
	  
	  default:
	     break;
	 	  
   }
   switch(State){
      case Start:
	  break;
	  
      case Init:
	     tempC = 0;
		 break;
		
	  case Waitrise:
	     tempC = tempC;
	     break;
		 
	  case Increment:
	     if(tempC < 9){
	     tempC = tempC + 1;
		 }
		 break;
		 
	  case Decrement:
	     if(tempC > 0){
	     tempC = tempC - 1;
	     }
		break;

          case Waitfall:
               tempC = tempC;
	       break;
	  default:
               tempC = tempC;   
	       break;
   
   }	   

	
}


