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
        case('A'|'a') :
            DDRA = 0xFF;
            PORTA = couleurHexa << rangeePin;
            break;
        case('B'|'b') :
            DDRB = 0xFF;
            PORTB = couleurHexa << rangeePin;
            break;
        case('C'|'c') :
            DDRC = 0xFF;
            PORTC = couleurHexa << rangeePin;
            break;
        case('D'|'d') :
            DDRD = 0xFF;
            PORTD = couleurHexa << rangeePin;
            break;    
    }
}
