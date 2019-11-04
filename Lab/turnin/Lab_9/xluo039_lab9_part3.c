/*	Xikang Luo & luoxikang@csu.edu.cn: Wenguang Wang & wangwenguang98@gmail.com
 *	Lab Section: 021
 *	Assignment: Lab9  Exercise 3
 *	Exercise Description: None
 *	
 *	I acknowledge all content contained herein, excluding template 
 * 	or example code, is my own original work.
 */
#include <asf.h>
#include <avr/interrupt.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
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
#define Len 14

void set_PWM(double frequency)
{
    static double current_frequency;
	if (frequency != current_frequency)
	{
		if(!frequency)
		{
			TCCR3B &= 0x08;
		}
		else
		{
			TCCR3B |= 0x03;
		}
		
		if (frequency < 0.954){OCR3A = 0xFFFF;}
		else if(frequency > 31250){OCR3A = 0x0000;}
		else {OCR3A = (short)(8000000/(128*frequency)) -1; }
		
		TCNT3 = 0;
		current_frequency = frequency;
		
	}
	
}

void PWM_on()
{
	TCCR3A = (1<< COM3A0);
	TCCR3B = (1<< WGM32) | (1<<CS31) | (1<<CS30) ;
	set_PWM(0);
}

void PWM_off()
{
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}


// Timer
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

// Prepare
typedef enum States{Wait, Singing} State;
State NowState = Wait;
unsigned char Button = 0;
short Rythsm[Len] = {D4,E4,F4,G4,B4,B4,C5,C5,B4,B4,G4,F4,E4,D4};

unsigned char PlayMusic()
{
	static unsigned char Point = 0;
	set_PWM(Rythsm[Point]);
	PORTC = Point;
	
	Point ++;
	
	if (Point == Len) //
	{
		Point = 0;
	}
	
	return Point;
}

void Tick()
{
	switch(NowState)
		{
			case Wait:
			{
				PWM_off();
				PORTC = 0x00;
				
				if (!Button) 
					NowState = Singing;
				break;
			}
			
			case Singing:
			{
				PWM_on();
				if(!PlayMusic())
				{
					NowState = Wait;
					break;
				}
			}
		}
}

int main()
{
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	PWM_on();
	TimerSet(30);
	TimerOn();
	
	
	
	
	while (1)
	{
		Button = PINA & 0x01;
		
		Tick();
		//PlayMusic();
		while(!TimerFlag)
		{
		}
		TimerFlag = 0;
	}
	
}
