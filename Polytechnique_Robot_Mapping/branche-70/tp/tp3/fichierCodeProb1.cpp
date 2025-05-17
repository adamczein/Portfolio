/*
 * Nom:TP2
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
*/

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

void BoucleRougeVertAmbre(){
  DDRB = 0xff; // PORT B est en mode sortie
  
  for (;;){
    PORTB = 0x01; //Rouge

    _delay_ms(1000); 

    PORTB = 0x02; //Vert

    _delay_ms(1000); 

    double compteur2 = 0;
    while (compteur2 <= 90){  //While loop pour Ambre //Compteur determine par essaie-erreur
       PORTB = 0x02;
      
      _delay_ms(10); //Delay determine par essaie-erreur

      PORTB = 0x01;

      _delay_ms(2); //Delay determine par essaie-erreur

      compteur2++;
    }
    
  }
}

void AttenuationRougeVert(){
  DDRB = 0xff; // PORT B est en mode sortie
  for (;;){
    int compteur = 0;
    int compteur2 = 0;
    double fraction = compteur/500;

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

void InterupteurAmbre(){
  DDRB = 0xff;
  for(;;){
    if(PIND & 0x04){
      _delay_ms(10);
      if(PIND & 0x04){
        double compteur2 = 0;
        while (compteur2 <= 90 && PIND & 0x04){  //While loop pour Ambre //Compteur determine par essaie-erreur
          PORTB = 0x02;
          
          _delay_ms(10); //Delay determine par essaie-erreur

          PORTB = 0x01;

          _delay_ms(2); //Delay determine par essaie-erreur

          compteur2++;
        }
      }
    }
    else{
      PORTB = 0x00;
    }
  }
}

int main(){
  AttenuationRougeVert();
  return 0;
}
