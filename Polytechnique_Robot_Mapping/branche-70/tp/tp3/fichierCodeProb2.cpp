/*
 * Nom:TP2
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
*/

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

void PWM(int pourcentage, int frequence){
  int compteur = 0;
  while(compteur<16000000){
    PORTB = 0x01;

    while(compteur2 < 1/frequence*pourcentage*(pow(10,6))){
      _delay_us(100); 
      compteur2++;
    }

    compteur2 = 0;

    PORTB = 0x00;

    while(compteur2 < 1/frequence*(1-(pourentage/100))*(pow(10,6))){
      _delay_us(10000); 
      compteur2++;
    }
    compteur2 = 0;

    compteur++;
    fraction = compteur/500;
    }
  }
}

void ControleMoteur(){
  DDRB = 0xff; // PORT B est en mode sortie
  for (;;){
    PWM(0,60);
    PWM(25,60);
    PWM(50,60);
    PWM(75,60);
    PWM(100,60);
    PWM(0,400);
    PWM(25,400);
    PWM(50,400);
    PWM(75,400);
    PWM(100,400);
  }




/*
    while(fraction < 1)
    {
      PORTB = 0x00;

      while(compteur2 < 500-compteur){
        _delay_us(10); 
        compteur2++;
      }

      compteur2 = 0;

      PORTB = 0x01;

      while(compteur2 < compteur){
        _delay_us(10); 
        compteur2++;
      }
      compteur2 = 0;

      compteur++;
      fraction = compteur/500;
    }
    compteur = 0;
    fraction = compteur/500;

    while(fraction < 1)
    {
      PORTB = 0x01;

      while(compteur2 < 500-compteur){
        _delay_us(10); 
        compteur2++;
      }

      compteur2 = 0;

      PORTB = 0x00;

      while(compteur2 < compteur){
        _delay_us(10); 
        compteur2++;
      }
      compteur2 = 0;

      compteur++;
      fraction = compteur/500;
    }
  }
}

int main(){
  ControleMoteur();
  return 0;
}
