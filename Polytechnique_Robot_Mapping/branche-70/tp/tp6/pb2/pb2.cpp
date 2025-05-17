/*
 * Nom:TP6 pb2
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
*/
#include <can.h>
#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

const int MODE_SORTIE = 0xff;
const int MODE_ENTREE = 0x00;
const int ROUGE = 0x01;
const int VERT = 0x02;

int main(){
    DDRA = MODE_ENTREE;
    DDRB = MODE_SORTIE;
    can sensor = can();

    uint16_t tampon;
    uint8_t tampon2;
    for(;;){
        tampon = sensor.lecture(1); //Nous obtennons une valeur 16bits dont les 10lsb possedent la valeur du sensor
        tampon2 = tampon >> 2; //Nous shiftons de 2bits vers la droite pour eliminer les 2 bits sans signification
                                // la valeur est convertie en 8bits
        if(tampon2 < 175){ //150 determine par essaie-erreur
            PORTB = VERT;
        }
        else if(tampon2 > 245){ //250 determine par essaie-erreur
            PORTB = ROUGE;
        }
        else {
            PORTB = VERT;
            _delay_ms(1); //Temps du delay determine par essaie-erreur
            PORTB = ROUGE;
        }
    }
}

 
