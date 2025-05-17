/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 */

#define F_CPU 8000000 // 8 MHz
#include <avr/io.h> 
#include <util/delay.h>


int main()
{
 
  DDRB = 0xff; // PORT B est en mode sortie
 

  for(;;)  // boucle sans fin
  {
      PORTB=0x00;
     if ( PIND & 0x04 ){
     _delay_ms(20.0);
     while (PIND & 0x04){
    
       PORTB=0x01;
       _delay_ms(20.0);
       PORTB=0x02;
       _delay_ms(20.0);
         
     }
     }



   
    
   
  }
  return 0; 
}