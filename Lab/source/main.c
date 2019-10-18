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
        switch (PINA & 0x0F) {
        case 1:  
        PORTC =  0x60;
        break;
        case 2:
        PORTC =  0x60;
        break;
        case 3:
        PORTC =  0x70;
        break;
        case 4:
        PORTC =  0x70;
        break;
        case 5:
        PORTC =  0x38;
        break;
        case 6:
        PORTC =  0x38;
        break;
        case 7:
        PORTC =  0x3C;
        break;
        case 8:
        PORTC =  0x3C;
        break;
        case 9:
        PORTC =  0x3C;
        break;
        case 10:
        PORTC =  0x3E;
        break;
        case 11:
        PORTC =  0x3E;
        break;
        case 12:
        PORTC =  0x3E;
        break;
        case 13:
        PORTC =  0x3F;
        break;
        case 14:
        PORTC =  0x3F;
        break;
        case 15:
        PORTC =  0x3F;
        break;
        }
    }
    return 1;
}
