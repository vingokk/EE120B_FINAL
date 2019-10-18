
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Init, Waitrise, Increment, Decrement, Waitfall}State;
void Tick();

int main(){
   DDRA = 0x00; PORTA = 0x0F;
   DDRC = 0x0F; PORTC = 0x00;
   State = Start;
   while(1){
      Tick();      
   }
  return 0;
  } 
void Tick(){
   
   switch(State){
      case Start:
             PORTC = 0x07;
	     State = Init;
	     break;
	  
	  case Init:
             PORTC = 0x07;
	     State = Waitrise;
	     break;
	  
	  case Waitrise:
	     if(!(PINA&0x01) && !(PINA&0x02)){
	     State = Waitrise;
	     }
	     else if(!(PINA&0x01) && (PINA&0x02) ){
	     State = Decrement;
	     }
	     else if((PINA&0x01) && !(PINA&0x02)){
	     State = Increment;
	     }
	     else if((PINA&0x01) && (PINA&0x02)){
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
	     if((PINA&0x01) ^ (PINA&0x02)){
	     State = Waitfall;
	     }
	     else if(!(PINA&0x01) && !(PINA&0x02)){
	     State = Waitrise;
	     }
	     else if((PINA&0x01) && (PINA&0x02)){
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
	     PORTC = 0x07;
		 break;
		
	  case Waitrise:
	     PORTC = PORTC;
	     break;
		 
	  case Increment:
	     if(PORTC < 9){
	     PORTC = PORTC + 1;
		 }
		 break;
		 
	  case Decrement:
	     if(PORTC > 0){
	     PORTC = PORTC - 1;
	     }
		break;

          case Waitfall:
               PORTC = PORTC;
 
	   default:
             PORTC = PORTC;   
	     break;
   
   }
            

}
