/*
 * Fichier: Prob1.cpp
 * Auteurs: Mohand Allache (1962202) et Azhar AKINOTCHO (1871583)
 * Date: 25 janvier 2019
 * Description: Probleme1*/

#define F_CPU 8000000 // 8 MHz
#include <avr/io.h>
#include <util/delay.h>
#define PORTENSORTIE 0xff
#define PORTENENTREE 0X00
#define marche 0x01
#define arret 0x00

void delay_ms(int delay)
{
    for (int i = 0; i < delay; i++)
        _delay_us(1);
}

void avance(int a, int b, int c)
{   
    //a : (POURCENTAGE * PERIODE)
    //b : PERIODE = (1/FREQUENCE) * 1000
    //c : nb de fois que la boucle est effectue pour atteindre le temps voulu
    for (int i = 0; i < c; i++)
    {

        PORTB = marche;
        delay_ms(a);
        PORTB = arret;
        delay_ms(b - a);
    }
}

int main()
{

    DDRB = PORTENSORTIE; // PORT B est en mode sortie

    for (;;) // boucle sans fin
    {
        PORTB = marche;
        int a = 0; //delai pour le marche (POURCENTAGE * FREQUENCE)
        int b = 16666; //FREQUENCE
        int c = 0, d = 2500; 
        avance(a, b, 120);
        a = 4166;
        avance(a, b, 120);
        a = 8333;
        avance(a, b, 120);
        a = 12500;
        avance(a, b, 120);
        a = 16666;
        avance(a, b, 120);

        avance(c, d, 800);
        c = 625;
        avance(c, d, 800);
        c = 1250;
        avance(c, d, 800);
        c = 1875;
        avance(c, d, 800);
        c = 2500;
        avance(c, d, 800);
    }
    return 0;
}
