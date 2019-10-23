#include <avr/io.h>
#include "io.h"

int main(void){

  DDRC = 0xFF; PORTC = 0x00;
  DDRD = 0xFF; PORTD = 0x00;
  
  PORTD = 0xff;
  LCD_init();

  LCD_DisplayString(1, "HELLO WORLD");
  
  while(1){continue;}
 
}

