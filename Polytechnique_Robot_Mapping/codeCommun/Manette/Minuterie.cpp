/*
 * Nom:Minuterie.cpp
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
 *
*/

#include "Minuterie.h"

/*************************************************
Nom: Minuterie()
Fonction: Constructeur de la classe Minuterie
**************************************************/
Minuterie::Minuterie() {
	minuterieCommencee_ = false;
	minuterieExpiree_ = 0;
}

/*************************************************
Nom: partirMinuterie
Fonction: Fonction qui fait usage du Timer1 pour partir une minutere par interuption
**************************************************/
void Minuterie::partirMinuterie ( uint8_t duree ) {

    minuterieCommencee_ = true;
    minuterieExpiree_ = 0;

    // mode CTC du timer 1 avec horloge divisée par 1024
	
    // interruption après la durée spécifiée
    
    TCNT0 = 0; //Initialisation du compteur

    OCR0A = duree; //Valeur a laquelle le timer est comparee

    TCCR0A |= (1 << COM0A1) | (1 << COM0A0) | (1 << WGM01); //Activation du "compare match"

    TCCR0B |= (1 << CS02) | (1 << CS00) ; //Clock select /1024

    //TCCR0C = 0; //

    TIMSK0 |= (1 << OCIE0A) ; // Output compare A match interrupt enable
   
    
     
    
    sei();
    /*
    TCNT1 = 0; //Initialisation du compteur

    OCR1A = duree; //Valeur a laquelle le timer est comparee

    TCCR1A |= (1 << COM1A0) ; //Activation du "compare match"
	
    TCCR1B |= (1 << CS12) | (1 << CS10) ; //Clock select /1024

    TCCR1C = 0; //

    TIMSK1 |= (1 << OCIE1A) ; // Output compare A match interrupt enable
    */

}

/*************************************************
Nom: getExpiree
Fonction: Retourne le int Expiree_, utilisé par le ISR de l'interruption
**************************************************/
uint8_t Minuterie::getExpiree() {
	return minuterieExpiree_;
}

/*************************************************
Nom: getComencee
Fonction: Retourne le bool indiquant si la minuterie est active
**************************************************/
bool Minuterie::getComencee() {
	return minuterieCommencee_;
}

void Minuterie::setExpiree() {
    minuterieExpiree_= 1;
}

/*
volatile uint8_t minuterieExpiree;
ISR (TIMER1_COMPA_vect) {

	minuterieExpiree = 1;

}
*/
