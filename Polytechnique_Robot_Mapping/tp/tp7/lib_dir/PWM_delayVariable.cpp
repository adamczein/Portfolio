/*
 * Fichier: PWM_delayVariable.cpp
 * Auteurs: Mohand Allache (1962202) et Azhar AKINOTCHO (1871583)
 * Date: 25 janvier 2019
 * Description: PWM & delay par variable
*/

#include "PWM_delayVariable.h"

void delay_ms_Variable(int delay)
{
    for (int i = 0; i < delay; i++)
        _delay_ms(1);
}

void PWM(int a, int b, int c)
{   
    //a : (POURCENTAGE * PERIODE)
    //b : PERIODE = (1/FREQUENCE) * 1000
    //c : nb de fois que la boucle est effectue pour atteindre le temps voulu
    for (int i = 0; i < c; i++)
    {

        PORTB = marche;
        delay_ms_Variable(a);
        PORTB = arret;
        delay_ms_Variable(b - a);
    }
}