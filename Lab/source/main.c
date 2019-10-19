
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Init, Waitrise, Increment, Decrement, Waitfall}State;
void Tick();
unsigned char button = 0x00;
unsigned char led = 0x00;

int main(){
   DDRA = 0x00; PORTA = 0xFF;
   DDRC = 0xFF; PORTC = 0x00;
   
   State = Start;
   while(1){
   	  
      Tick();      
   }
  return 0;
  } 
void Tick(){
   button = (~PINA & 0x03);
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
	     if(!(button&0x01) && !(button&0x02)){
	     State = Waitrise;
	     }
	     else if(!(button&0x01) && (button&0x02) ){
	     State = Decrement;
	     }
	     else if((button&0x01) && !(button&0x02)){
	     State = Increment;
	     }
	     else if((button&0x01) && (button&0x02)){
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
	     if((button&0x01) ^ (button&0x02)){
	     State = Waitfall;
	     }
	     else if(!(button&0x01) && !(button&0x02)){
	     State = Waitrise;
	     }
	     else if((button&0x01) && (button&0x02)){
	     State = Init;
	     }
	     break;
	  
	  default:
	     break;
	 	  
   }
   switch(State){
      case Start:
	  break;
	  
      case Init:
	     led = 0x00;
		 break;
		
	  case Waitrise:
	     led = led;
	     break;
		 
	  case Increment:
	     if(led < 9){
	     led = led + 1;
		 }
		 break;
		 
	  case Decrement:
	     if(led > 0){
	     led = led - 1;
	     }
		break;

          case Waitfall:
               led = led;
 
	   default:
             led = led;   
	     break;
   
   }
   
   PORTC = led;           
}
