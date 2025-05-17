/*
 * Nom:InterruptionExterne.cpp
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452

*/

#include "InterruptionExterne.h"
#include <avr/io.h> 
#include <avr/interrupt.h>
#include "Debounce.h"

const int PRESSED = 0x04, MODE_SORTIE = 0xff;
volatile uint8_t boutonPoussoir;
volatile bool currentStateIsPressed = false;

ISR (INT0_vect) {

    if (CheckIfPressed()){
        boutonPoussoir = 1;
    }
    EIFR |= (1 << INTF0) ;
}

void initialisationIntExterne ( void ) {

    // cli est une routine qui bloque toutes les interruptions.

    // Il serait bien mauvais d'être interrompu alors que

    // le microcontroleur n'est pas prêt...

    cli();

    // configurer et choisir les ports pour les entrées

    // et les sorties. DDRx... Initialisez bien vos variables

    DDRB = MODE_SORTIE;

    // cette procédure ajuste le registre EIMSK

    // de l’ATmega324PA pour permettre les interruptions externes

    EIMSK |= (1 << INT0);

    // il faut sensibiliser les interruptions externes aux

    // changements de niveau du bouton-poussoir

    // en ajustant le registre EICRA

    EICRA |= (1 << ISC00);

    // sei permet de recevoir à nouveau des interruptions.

    sei ();
}
