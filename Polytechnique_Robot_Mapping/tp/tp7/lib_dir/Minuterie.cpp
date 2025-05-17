/*
 * Nom:Minuterie.cpp
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452

*/

#include "Minuterie.h"
#include <avr/io.h> 
#include <avr/interrupt.h>

volatile uint8_t minuterieExpiree;
volatile bool MinuterieCommencee = false;

/*
ISR (TIMER1_COMPA_vect) {

    minuterieExpiree = 1;

}
*/

void partirMinuterie ( uint16_t duree ) {

    MinuterieCommencee = true;
    minuterieExpiree = 0;

    // mode CTC du timer 1 avec horloge divisée par 1024

    // interruption après la durée spécifiée

    TCNT1 = 0; //Initialisation du compteur

    OCR1A = duree; //Valeur a laquelle le timer est comparee

    TCCR1A |= (1 << COM1A0) ; //Activation du "compare match"

    TCCR1B |= (1 << CS12) | (1 << CS10) ; //Clock select /1024

    TCCR1C = 0; //

    TIMSK1 |= (1 << OCIE1A) ; // Output compare A match interrupt enable

}
