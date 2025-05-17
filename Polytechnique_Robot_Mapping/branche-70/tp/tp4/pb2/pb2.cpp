/*
 * Nom:TP4 pb2
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452

*/

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

const int PRESSED = 0x04, MODE_SORTIE = 0xff;
const int ROUGE = 0x01;
const int VERT = 0x02;
const int ETEINT = 0x00;
volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;
volatile bool currentStateIsPressed = false;
volatile bool MinuterieCommencee = false;

void CheckIfPressed(){ // Fonction qui verifie si le bouton D est active
    _delay_ms(10);
    if(PIND & PRESSED)	
        currentStateIsPressed = true;
    else
        currentStateIsPressed = false;
}

ISR (TIMER1_COMPA_vect) {

    minuterieExpiree = 1;

}


ISR (INT0_vect) {

    // anti-rebond

    CheckIfPressed();

    if (currentStateIsPressed && MinuterieCommencee){
        boutonPoussoir = 1;
    }
    EIFR |= (1 << INTF0) ;
}

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

void initialisation ( void ) {

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

void routine(){
    do {

    // attendre qu'une des deux variables soit modifiée

    // par une ou l'autre des interruptions.

    } while ( minuterieExpiree == 0 && boutonPoussoir == 0 );

    // Une interruption s'est produite. Arrêter toute

    // forme d'interruption. Une seule réponse suffit.

    cli ();

    // Verifier la réponse'modifier ici'

    if(boutonPoussoir)
    {
        PORTB = VERT;
    }
    else
        PORTB = ROUGE;

}

int main(){
    initialisation();
    _delay_ms(10000);
    PORTB = ROUGE;
    _delay_ms(100);
    PORTB = ETEINT;
    partirMinuterie(0x1E84);
    routine();

    return 0;
}

 
