#include "DEL.h"

/*************************************************
Nom: DEL()
Fonction: Constructeur de la classe DEL
**************************************************/
DEL::DEL() {
}

/*************************************************
Nom: Allumer
Fonction: Fonction qui prend en parametre le code hexadecimale de la couleur (0x01 : Rouge) (0x02 : Vert) (0x00 : ETEINT), 
		  le port selectionne et la rangee choisie selon les pins (A intervalle de 2 bits; 0,2,4,6)
**************************************************/
void DEL::Allumer(uint8_t couleurHexa, char port, int rangeePin){
	
    switch(port){
        case('a') :
        case('A') :
            DDRA = 0xFF; // 0xFF = mis en mode sortie
            PORTA = couleurHexa << rangeePin;
            break;
        case('b') :
        case('B') :
            DDRB = 0xFF;
            PORTB = couleurHexa << rangeePin;
            break;
        case('c') :
        case('C') :
            DDRC = 0xFF;
            PORTC = couleurHexa << rangeePin;
            break;
        case('d') :
        case('D') :
            DDRD = 0xFF;
            PORTD = couleurHexa << rangeePin;
            break;    
    }
}
