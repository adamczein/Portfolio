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
 
  DDRA = 0xff; // PORT B est en mode sortie
 

  for(;;)  // boucle sans fin
  {
                       
     PORTA = 0x01;
     _delay_ms  (1000);
    PORTA = 0x02;
     _delay_ms  (1000);

     for(int i=0;i<25 ;i++){
       PORTA=0x01;
       _delay_ms(20.0);
       PORTA=0x02;
       _delay_ms(20.0);
           
            }



   
    
   
  }
  return 0; 
}
