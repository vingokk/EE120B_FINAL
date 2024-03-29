
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Init, Waitrise, Figure1, Figure2, Waitfall}State;
void Tick();
unsigned char button = 0x00;
unsigned char led = 0x00;

int main(){
   DDRA = 0x00; PORTA = 0xFF;
   DDRB = 0xFF; PORTB = 0x00;
  
   State = Start;
   while(1){
   	  
      Tick();      
   }
  return 0;
  } 
void Tick(){
   button = (~PINA & 0x01);
   switch(State){
      case Start:
             led = 0x00;
	     State = Init;
	     break;
	  
	  case Init:
             led = 0x00;
	     State = Waitrise;
	     break;
	  
	  case Waitrise:
	     if(!button&0x01 ){
	       State = Figure1;
	     }
	     else if(button&0x01 ){
	     State = Figure2;
	     }
	   
	     break;
	  
          case Figure1:
	     State = Waitfall;
	     break;
	  
          case Figure2:
	     State = Waitfall;
	     break;
	  
	  case Waitfall:
	     State = Waitrise;
	     break;
	  
	  default:
	     break;
	 	  
   }
   switch(State){
      case Start:
	  break;
	  
      case Init:
	     led = 0x2A;
		 break;
		
	  case Waitrise:
	     led = 0x2A;
	     break;
		 
	  case Figure1:
	     led = 0x15;
		 break;
		 
          case Figure2:
	   
	    led = 0x0f;
		break;

          case Waitfall:
               led = 0xff;
 
	   default:
             led = led;   
	     break;
   
   }
   
   PORTB = led;           
}
