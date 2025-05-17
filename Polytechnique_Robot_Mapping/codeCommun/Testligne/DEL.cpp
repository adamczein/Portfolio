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
void DEL::allumerDEL(uint8_t couleurHexa, char port, int rangeePin){
	
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

/*
PORT CORRESPONDANT DEL BREADBOARD

int main(){
    DEL del;
    del.allumerDEL(0x01,'C',0); // DEL 1
    _delay_ms(1000);
    del.allumerDEL(0x00,'C',0);
    _delay_ms(1000);
    del.allumerDEL(0x01,'C',2); // DEL 2
    _delay_ms(1000);
    del.allumerDEL(0x00,'C',2);
    _delay_ms(1000);
    del.allumerDEL(0x02,'C',2); // DEL 3
    _delay_ms(1000);
    del.allumerDEL(0x00,'C',2);
    _delay_ms(1000);
    del.allumerDEL(0x02,'C',6); // DEL 4
    _delay_ms(1000);
    del.allumerDEL(0x00,'C',6);
    _delay_ms(1000);
    del.allumerDEL(0x02,'C',4); // DEL 5
    _delay_ms(1000);
    del.allumerDEL(0x00,'C',4);
    _delay_ms(1000);
}
*/
