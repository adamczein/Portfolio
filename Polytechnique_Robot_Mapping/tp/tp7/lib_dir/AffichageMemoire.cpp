/*
 * Nom:AffichageMemoire.cpp
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
*/
 #include "AffichageMemoire.h"
 #include <avr/io.h> 
 #include <util/delay.h>
 #include <avr/interrupt.h>
 #include <memoire_24.h>

const int MODE_SORTIE = 0xff;

void initialisationUART ( void ) {

    // 2400 bauds. Nous vous donnons la valeur des deux

    // premier registres pour vous éviter des complications

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la reception et la transmission par le UART0

    UCSR0A = 0;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0) ; // RXEN0 = Reciever enable, TXEN0 = Transmission enable

    // Format des trames: 8 bits, 1 stop bits, none parity

    UCSR0C = (1 << UCSZ11) | (1 << UCSZ10); // UCSZ11 & UCSZ10 : Character size a 8-bit

}

void transmissionUART ( uint8_t donnee ) {
    while (!((UCSR0A) & (1 << UDRE0))){        
    }
    UDR0 = donnee; 
}

void affichageMemoire(){
    DDRD = MODE_SORTIE;

    initialisationUART();

    Memoire24CXXX memoire = Memoire24CXXX();
    uint8_t tampon;
    uint16_t i = 0x0000;

    while(tampon!=0xFF){
        memoire.lecture(i++, &tampon);
        if(tampon!=0xFF) {
            transmissionUART(tampon);
        }
    }
}
 
