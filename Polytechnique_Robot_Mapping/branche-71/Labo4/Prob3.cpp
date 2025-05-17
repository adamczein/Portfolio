#define F_CPU 8000000 // 8 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define PORTENSORTIE 0xff
#define PORTENENTREE 0X00
#define rouge 0x02
#define eteint 0x00
#define vert 0x01

void initialisation(void)
{

    DDRD = PORTENSORTIE;
    TCNT1 = 0;
 
}

void ajustementPWM(uint8_t VA, uint8_t VB)
{

    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6

    // page 177 de la description technique du ATmega324PA)

    OCR1A = VA;

    OCR1B = VB;

    // division d'horloge par 8 - implique une frequence de PWM fixe

    TCCR1A |= (1 << WGM10);
    TCCR1A |= (1 << COM1A1);
    TCCR1A |= (1 << COM1B1);

    TCCR1B |= (1 << CS11);

    TCCR1C = 0;
}

int main()
{
    initialisation();
    for (;;){

    ajustementPWM(0, 0);
    _delay_ms(2000);

    ajustementPWM(63, 63);
    _delay_ms(2000);

    ajustementPWM(127, 127);
    _delay_ms(2000);

    ajustementPWM(191, 191);
    _delay_ms(2000);

    ajustementPWM(255, 255);
    _delay_ms(2000);

    }

    return 0;
}
