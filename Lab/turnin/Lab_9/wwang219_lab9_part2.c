  /*    Author: Wenguang Wang        Email:wangwenguang98@gmail.com
 *      Partner(s) Name: xikang luo  Email: luoxikang@csu.edu.cn
 *      Lab Section: 022 
 *      Assignment: Lab #9  Exercise #2
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

#define C4 261.63
#define D4 293.66
#define E4 329.63
#define F4 349.23
#define G4 392.00
#define A4 440.00
#define B4 493.88
#define C5 523.25
double music[8]={C4, D4, E4, F4, G4, A4, B4, C5};
unsigned char button = 0x00;
unsigned int i = 0;
volatile unsigned char TimerFlag = 0x00;
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




void set_PWM(double frequency){
     static double current_frequency;
     if(frequency != current_frequency){
        if(!frequency){ TCCR3B &= 0X08; }
        else { TCCR3B |= 0x03; }

     if(frequency < 0.954){ OCR3A = 0xFFFF;}
     else if(frequency > 31250){ OCR3A = 0x0000;}
     else{OCR3A = (short)(8000000 / (128 * frequency)) - 1;}
     TCNT3 = 0;
     current_frequency = frequency;
     }
}

void PWM_on(){
  TCCR3A = (1 << COM3A0);
  TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
  set_PWM(0);
}


void PWM_off(){
   TCCR3A = 0x00;
   TCCR3B = 0x00;
}


void Buffer_Tick();


enum States{Init, On, Off, Wait, ScaleUp, ScaleDown}State;

int main(void){
   DDRA = 0x00; PORTA = 0xFF;
   DDRB = 0x4F;  
   PORTB = 0x4F;
   PWM_on();
   TimerSet(100);
   TimerOn();
   while(1){
     Buffer_Tick();
     while(!TimerFlag){}
     TimerFlag = 0;
   }
}

void Buffer_Tick(){
   button = (~PINA & 0x07);
   switch(State){
   case Init:
     if(button & 0x01){
       State = On;
     }
     break;

   case On:
     if(button & 0x02){
       State = ScaleUp;
     }
     else if (button & 0x04){
       State = ScaleDown;
     }
     if(button & 0x01){
       State = Off;
     }
     break;

   case ScaleUp:
     State = Wait;
     break;
   
   case ScaleDown:
     State = Wait;
     break;

   case Wait:
     if(button & 0x02){
       State = ScaleUp;
     }
     else if (button & 0x04){
       State = ScaleDown;
     }
     else if (button & 0x01){
       State = Off;
     }
     break;

   case Off:
     State = Init;
     break;
   }

   switch(State){

   case Init:
     i = 0;
     set_PWM(0);
     break;

   case On:
     i = 0;
     set_PWM(music[i]);
     break;

   case ScaleUp:
     if(i<7){
       ++i;
       set_PWM(music[i]);
     }
     break;
   

   case ScaleDown:
     if(i>0){
       --i;
       set_PWM(music[i]);
     }
     break;

   case Wait:
     set_PWM(music[i]);
     break;

   case Off:
     set_PWM(0);
    break;

   default:
   break;
	     }


}
