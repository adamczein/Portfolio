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

volatile uint8_t etat = 0; // selon le nom de votre variable

ISR(INT0_vect)
{

   _delay_ms(30);
   /* if (PIND & 0x04)
        _delay_ms(10);
    if (PIND & 0x04)*/
 
        if (etat == 5)
            etat = 0;
        else
            etat++;
   

    EIFR |= (1 << INTF0);
}

void initialisation(void)
{

    cli();

    DDRA = PORTENSORTIE;
    DDRD = PORTENENTREE;

    EIMSK |= (1 << INT0);

    EICRA |= (1<<ISC00);

    sei();
}

int main()
{
    initialisation();
    for (;;) // boucle sans fin
    {

        switch (etat)
        {

        case 0:

            PORTA = rouge;
            break;

        case 1:

            PORTA = vert;
            _delay_ms(15);
            PORTA = rouge;
            _delay_ms(5);

            break;

        case 2:

            PORTA = vert;

            break;

        case 3:
            PORTA = rouge;

            break;

        case 4:

            PORTA = eteint;

            break;

        case 5:
            PORTA = vert;

            break;
        }
    }
    return 0;
}
