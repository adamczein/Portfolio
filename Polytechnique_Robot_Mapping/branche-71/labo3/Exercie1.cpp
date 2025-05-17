/*
 * Fichier: Prob1.cpp
 * Auteurs: Mohand Allache (1962202) et Azhar AKINOTCHO (1871583)
 * Date: 25 janvier 2019
 * Description: Probleme1*/

#define F_CPU 8000000 // 8 MHz
#include <avr/io.h>
#include <util/delay.h>
#define PORTENSORTIE 0xff
#define PORTENENTREE 0X00

void delay_ms(int delay){
  for(int i=0; i<delay;i++)
    _delay_us(1);
}
int main()
{

  DDRA = PORTENSORTIE; // PORT A est en mode sortie
  
  
  uint8_t rouge = 0x02;
  uint8_t eteint = 0x00;

  for (;;) // boucle sans fin
  {
     int a=1200;//delaie pour le rouge
  int const b=1200;//delaie pour eteint
      while (a>0){
       PORTA=rouge;
       delay_ms(a);
       PORTA=eteint;
       delay_ms(b-a);
       a--;       
    }
  }
    
  return 0;
}



