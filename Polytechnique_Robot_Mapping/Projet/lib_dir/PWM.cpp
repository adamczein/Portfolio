#include "PWM.h"
#include <avr/io.h> 

void PWM(int valeur)
{
	//PORTC, 3e pin?
	// 40KHz
	// 8000000/40000??
	TCCR0A |= (1 << WGM01);
    TCCR0A |= (1 << COM0A0);
    TCCR0B |= (1 << CS00);

    OCR0A = valeur;
}
