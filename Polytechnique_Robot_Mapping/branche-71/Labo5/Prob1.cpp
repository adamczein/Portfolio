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