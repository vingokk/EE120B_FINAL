  /*    Author: Wenguang Wang        Email:wangwenguang98@gmail.com
 *      Partner(s) Name: xikang luo  Email: luoxikang@csu.edu.cn
 *      Lab Section: 022 
 *      Assignment: Lab #8  Exercise #3 
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

#define MAX 0x09F

void ADC_init();



int main(void){
   DDRA = 0x00; PORTA = 0xFF;
   DDRB = 0xFF; PORTB = 0x00;
   DDRD = 0xFF; PORTD = 0x00;
    ADC_init();
   unsigned short x;
   unsigned char temB;
   unsigned char temD;

   while(1){
      x = ADC;
      if ( x >= MAX/2){
	temB = 0x01;
      }
      else{
        temB = 0x00;
      }

      PORTB = temB;

   }

  
   return 1;



}

void ADC_init(){
ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

/* MAX ==
 * MIN == 1024
 */
