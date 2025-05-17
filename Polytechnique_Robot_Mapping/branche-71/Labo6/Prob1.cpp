/*
 * Fichier: Prob1.cpp
 * Auteurs: Mohand Allache (1962202) et Azhar AKINOTCHO (1871583)
 * Date: 22 fevrier 2019
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
    // laisser un delai avant de confirmer la réponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms(30);

    // changements d'états
    if (etat == 3)
        etat = 0;
    else
        etat++;

    //si une seconde interruption entre celle-ci, l'AVR
    //s'en souvient et ISR sera exécutée après l'interruption courante
    EIFR |= (1 << INTF0);
}

/****************************************************************************
 * Fonction: initialisation()
 * Description: Elle ajuste bien des paramètres avant 
 *              le début du traitement principal              
 * Paramètres: Aucun
 * Retour: Aucun
 ****************************************************************************/
void initialisation(void)
{

    cli(); // cli est une routine qui bloque toutes les interruptions

    DDRA = PORTENSORTIE;
    DDRD = PORTENENTREE;

    // ajuste le registre EIMSK pour permettre les interruptions externes
    EIMSK |= (1 << INT0);

    //ajuste le registre EICRA pour sensibiliser les interruptions
    //externes aux changements de niveau
    EICRA |= (1 << ISC00);

    sei(); // permet de recevoir à nouveau des interruptions.
}

/****************************************************************************
 * Fonction: main()
 * Description: fonction principal traitant le probleme 2      
 * Paramètres: Aucun
 * Retour: Aucun
 ****************************************************************************/
int main()
{
    int compteur = 0;
    initialisation();

    for (;;)
    {

        switch (etat)
        {

        case 0:

            PORTA = eteint;
            break;

        case 1:

            if (compteur < 120)
            {
                compteur += 10;
                _delay_ms(1000);
            }

            else
                etat = 2;

            break;

        case 2:

            for (int i = 0; i < 5; i++)
            {
                PORTA = vert;
                _delay_ms(50);
                PORTA = eteint;
                _delay_ms(50);
            }
            etat = 3;
            break;

        case 3:
            //delai de 2 secondes
            _delay_ms(2000);
            //faire clignoter la DEL en rouge (compteur / 2) fois
            //au rythme de 2 fois par seconde
            for (int i = 0; i < (compteur / 10); i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    PORTA = rouge;
                    _delay_ms(100);
                    PORTA = eteint;
                    _delay_ms(100);
                }
            }
            PORTA = vert;
            _delay_ms(1000); //délai de 1 seconde
            PORTA = eteint;
            etat = 0;

            break;
        }
    }
    return 0;
}
