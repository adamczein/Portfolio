/*
 * Nom:TP4 pb3
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452

*/

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

const int MODE_SORTIE = 0xff;

void ajustementPWM (int pourcentage) {

    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6

    // page 177 de la description technique du ATmega324PA)

    OCR1A = pourcentage;
    
    OCR1B = pourcentage;
    
    // division d'horloge par 8 - implique une frequence de PWM fixe

    //PAGE 123 & section 16.10.4
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1)| (1 << WGM10); //Table 16-4.

    TCCR1B |= (1 << CS11);

    TCCR1C = 0;

}

int main(){
    TCNT1 = 0;
    DDRD = MODE_SORTIE;
    ajustementPWM(255);
    _delay_ms(2000);
    ajustementPWM(191);
    _delay_ms(2000);
    ajustementPWM(127);
    _delay_ms(2000);
    ajustementPWM(64);
    _delay_ms(2000);
    ajustementPWM(0);

    return 0;
}
