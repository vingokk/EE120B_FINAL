/*	Author: wenguang wang
 *      Partner(s) Name: xikang luo
 *	Lab Section:022
 *	Assignment: Lab #10  Exercise #1
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






typedef struct task{
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int(*TickFct)(int);
}tasks;

task tasks[3];

const unsigned char tasksNum = 3;
const unsigned long periodThreeLEDs = 1000;
const unsigned long periodBlinkingLED = 1000;
const unsigned long tasksPeriodGCD = 1000;


enum ThreeLEDsStates{TL_Start,TL_S1,TL_S2, TL_S3} ThreeLEDsState;
int TickFct_ThreeLEDs(int state);

enum BlinkingLEDStates{BL_Start, BL_S1, BL_S2}  BlinkingLEDState;
int TickFct_BlinkingLED(int state);

void TimerISR(){
   unsigned char i = 0;
   for(i = 0; i<tasksNum; ++i){
      task.TL_S1
} 

}


int main(){
   unsigned char i = 0;
   tasks[i].state =TL_Start;
   tasks[i].period = periodThreeLEDs;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = & TickFct_ThreeLEDs; 

   ++i;

   tasks[i].state =TL_Start;
   tasks[i].period = periodBlinkingLED;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = & TickFct_BlinkingLED;

   TimerSet(tasksPeriodGCD);
   TimerOn;

   while(1){
      sleep();
   }


   return 0;
}


unsigned char tempTL = 0x00;
int TickFct_ThreeLEDs(int state){
switch(state){
case TL_Start:
tempT = 0x00;
state = TL_S1;
break;

case TL_S1:
state = TL_S2;
break;

case TL_S3:
state = TL_S1
break;

 default:
break; 
}

switch(state)





}
