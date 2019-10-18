/*	Author: wwang219
 *  Partner(s) Name: xikang&wenguang
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {

    DDRA = 0x00; DDRC = 0xFF;
    PORTA = 0xFF; PORTC = 0x00;
    unsigned char led  = 0x00;
    unsigned char button = 0x00;

    while(1){
	button = ~PINA & 0x0F;

        switch (button) {
	case 0:
	   led  =  0x40;
        case 1:  
           led  =  0x60;
           break;
        case 2:
           led  =  0x60;
           break;
        case 3:
           led  =  0x70;
           break;
        case 4:
           led  =  0x70;
           break;
        case 5:
           led  =  0x38;
           break;
        case 6:
           led  =  0x38;
           break;
        case 7:
           led  =  0x3C;
           break;
        case 8:
           led  =  0x3C;
           break;
        case 9:
           led  =  0x3C;
           break;
        case 10:
           led  =  0x3E;
           break;
           case 11:
           led  =  0x3E;
        break;
           case 12:
           led  =  0x3E;
        break;
           case 13:
           led  =  0x3F;
        break;
        case 14:
           led  =  0x3F;
           break;
        case 15:
           led  =  0x3F;
	   break;
        }
	PORTC = led ;
    }
    return 1;
}
