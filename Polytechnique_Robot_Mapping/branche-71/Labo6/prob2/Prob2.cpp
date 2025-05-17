/*
 * Fichier: Prob2.cpp
 * Auteurs: Mohand Allache (1962202) et Azhar AKINOTCHO (1871583)
 * Date: 22 fevrier 2019
 * Description: Probleme2*/

#define F_CPU 8000000 // 8 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"

#define PORTENSORTIE 0xff
#define PORTENENTREE 0X00
#define rouge 0x02
#define eteint 0x00
#define vert 0x01

#define lumiereBasse 0xA0 //160
#define lumiereForte 0xE6 //230

int main()
{
    DDRA = PORTENENTREE;
    DDRB = PORTENSORTIE;
    uint16_t lecture;
    can convert;

    for (;;)
    {
        lecture = convert.lecture(0);
        lecture = lecture >> 0x2;

        if (lecture < lumiereBasse)

            PORTB = vert;

        else
        {
            if (lecture < lumiereForte && lecture > lumiereBasse)
            {
                PORTB = vert;
                _delay_ms(10);
                PORTB = rouge;
                _delay_ms(10);
            }
            else
                PORTB = rouge;
        }
    }

    return 0;
}
