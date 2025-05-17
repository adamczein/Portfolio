/*
 * Fichier: Prob1.cpp
 * Auteurs: Mohand Allache (1962202) et Azhar AKINOTCHO (1871583)
 * Date: 25 janvier 2019
 * Description: Probleme1*/

#define F_CPU 8000000 // 8 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define PORTENSORTIE 0xff
#define PORTENENTREE 0X00
#define rouge 0x02
#define eteint 0x00
#define vert 0x01

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

ISR(TIMER1_COMPA_vect)
{

    minuterieExpiree = 1;
}

ISR(INT0_vect)
{

    boutonPoussoir = 1;

    // anti-rebond

    _delay_ms(30);

    EIFR |= (1 << INTF0);
}

void partirMinuterie(uint16_t duree)
{

    minuterieExpiree = 0;

    // mode CTC du timer 1 avec horloge divisée par 1024

    // interruption après la durée spécifiée

    TCNT1 = 0;

    OCR1A = duree;

    TCCR1A |= (1 << COM1A1);
    TCCR1A |= (1 << COM1A0);

    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12);
    TCCR1B |= (1 << CS10);

    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A);
}

void initialisation(void)
{

    cli();

    DDRA = PORTENSORTIE;
    DDRD = PORTENENTREE;

    EIMSK |= (1 << INT0);

    EICRA |= (1 << ISC01);

    sei();
}

int main()
{ 
    initialisation();
    do
    {

        
        // attendre qu'une des deux variables soit modifiée
        _delay_ms(3000);
        PORTA = rouge;
        _delay_ms(100);
        PORTA = eteint;
        partirMinuterie(0x1E84);
        // par une ou l'autre des interruptions.

    } while (minuterieExpiree == 0 && boutonPoussoir == 0);

    // Une interruption s'est produite. Arrêter toute

    // forme d'interruption. Une seule réponse suffit.

    cli();

    // Verifier la réponse

    if (minuterieExpiree == 0)
        PORTA = vert;
    else
        PORTA = rouge;

    return 0;
}
