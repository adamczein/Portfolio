/*
 * Nom:AffichageMemoire.cpp
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
*/
 #include "AffichageMemoire.h"

/*************************************************
Nom: UART()
Fonction: Constructeur de la classe UART
**************************************************/
UART::UART() {
	modeSortie_ = 0xff;
}
/*************************************************
Nom: initialisationUART
Fonction: Permet la transmission par UART0
**************************************************/
void UART::initialisationUART ( void ) {

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la reception et la transmission par le UART0

    UCSR0A = 0;

    UCSR0B = (1 << RXEN0) | (1 << TXEN0) ; // RXEN0 = Reciever enable, TXEN0 = Transmission enable

    // Format des trames: 8 bits, 1 stop bits, none parity

    UCSR0C = (1 << UCSZ11) | (1 << UCSZ10); // UCSZ11 & UCSZ10 : Character size a 8-bit

}
/*************************************************
Nom: transmissionUART
Fonction: Transmettre la donnee a UDR0 si le transmit buffer est vide (Indiqué par UDRE0) et que le registre de control et statut du UART est prêt 
**************************************************/
void UART::transmissionUART ( uint8_t donnee ) {
    while (!((UCSR0A) & (1 << UDRE0))){        
    }
    UDR0 = donnee; 
}
/*************************************************
Nom: lectureUART
Fonction: Retourne la donnée chargée dans le recieve buffer
**************************************************/
uint8_t UART::lectureUART() {
    while(!((UCSR0A)&(1 << RXC0))); //RXC0 = USART COMPLETRE FLAG
    return UDR0; //UDR0 = RECEIVE BUFFER
}
/*************************************************
Nom: affichageMemoire
Fonction: Fait la lecture de la mémoire et afficher celle-ci par le UART (En faisant usage de la fonction serieViaUSB)
**************************************************/
void UART::affichageMemoire(){
    DDRD = modeSortie_;

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