  /*    Author: Wenguang Wang        Email:wangwenguang98@gmail.com
 *      Partner(s) Name: xikang luo  Email: luoxikang@csu.edu.cn
 *      Lab Section: 022 
 *      Assignment: Lab #10  Exercise #1
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
void TimerOn();
void TimerISR();
void TimerOff();
ISR(TIMER1_COMPA_vect);
void TimerSet(unsigned long M);



typedef struct task{
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int(*TickFct)(int);
}task;

task tasks[2];

const unsigned char tasksNum = 2;
const unsigned long periodThreeLEDs = 1000;
const unsigned long periodBlinkingLED = 1000;
const unsigned long tasksPeriodGCD = 1000;


enum TL_States{TL_Start,TL_S1,TL_S2, TL_S3} TL_State;
int TickFct_ThreeLEDs(int state);

enum Bl_States{BL_Start, BL_S1, BL_S2} BL_State;
int TickFct_BlinkingLED(int state);

void TickFct_CombineLEDs();



int main(){
  DDRB = 0xFF; PORTB = 0x00;



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
   TimerOn();

   while(1){
     /* Sleep();
      */
   }


   return 0;
}


unsigned char tempTL = 0x00;
int TickFct_ThreeLEDs(int state){
switch(state){

 case TL_Start:
   tempTL = 0x00;
   state = TL_S1;
   break;

 case TL_S1:
   state = TL_S2;
   break;

 case TL_S2:
   state = TL_S3;
   break;

 case TL_S3:
   state = TL_S1;
   break;

 default:
   state = TL_Start;
   break; 
}

switch(state){

 case BL_Start:
   tempTL = 0x00;
   break;

 case TL_S1:
   tempTL = 0x01;
   break;

 case TL_S2:
   tempTL = 0x02;
   break;

 case TL_S3:
   tempTL = 0x04;
   break;

 default:
   break;
}

 return state;
}

unsigned char tempBL = 0x00;
int TickFct_BlinkingLED( int state){
switch(state){

 case BL_Start:
   tempBL = 0x00;
   state = BL_S1;
   break;

 case BL_S1:
   state = BL_S2;
   break;

 case BL_S2:
   state = BL_S1;
   break;

 default:
   state = BL_Start;
   break; 
}


switch(state){

 case BL_Start:
   tempBL = 0x00;
   state = TL_S1;
   break;

 case BL_S1:
   tempBL = 0x08;
   break;

 case BL_S2:
   tempBL = 0x00;
   break;

 default:
   break; 
}

 return state;

}

void TickFct_CombineLEDs(){
  PORTB = tempBL | tempTL;
}


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

void TimerISR(){
   unsigned char i = 0;
   for(i = 0; i < tasksNum; ++i){
     if(tasks[i].elapsedTime >= tasks[i].period){
       tasks[i].state = tasks[i].TickFct(tasks[i].state);
       tasks[i].elapsedTime = 0;
     }
     tasks[i].elapsedTime += tasksPeriodGCD;
   } 
   TickFct_CombineLEDs();

}
