#include <avr/io.h> 

#include "DEL.h"
const int MODE_SORTIE = 0xff;

//Fonction qui prend en parametre le code hexadecimale de la couleur (0x01 : Rouge) (0x02 : Vert) (0x00 : ETEINT), le port selectionne et la rangee choisie selon les pins (A intervalle de 2 bits; 0,2,4,6)
void DEL(int couleurHexa, char port, int rangeePin){
    switch(port){
        case('A'|'a') :
            DDRA = MODE_SORTIE;
            PORTA = couleurHexa << rangeePin;
            break;
        case('B'|'b') :
            DDRB = MODE_SORTIE;
            PORTB = couleurHexa << rangeePin;
            break;
        case('C'|'c') :
            DDRC = MODE_SORTIE;
            PORTC = couleurHexa << rangeePin;
            break;
        case('D'|'d') :
            DDRD = MODE_SORTIE;
            PORTD = couleurHexa << rangeePin;
            break;    
    }
}