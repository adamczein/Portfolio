
#define F_CPU 8000000

#include "AffichageMemoire.h"
#include "RecepteurIR.h"
#include "EmetteurIR.h"
#include "DEL.h"
#include <util/delay.h>

UART uart;
RecepteurIR recepteur;
EmetteurIR emetteur;
int compteur = 0; // Compteur pour répéter la minuterie (250 max) jusqu'à une valeur voulue (8)

int main()
{ 
	emetteur.EnvoieIR();
	recepteur.ReceptionIR();
	int commande = recepteur.getCommande();
	//Test
	while (commande == 1)
	{
		PORTA = 0x01;
		uart.transmissionUART(1);
	}
	while (commande == 2)
	{
		PORTA = 0x01;
		_delay_ms(500);
		PORTA = 0x02;
		_delay_ms(1000);
		uart.transmissionUART(2);
	}
	while (commande == 3)
	{
		PORTA = 0x01;
		_delay_ms(100);
		PORTA = 0x02;
		_delay_ms(100);
		uart.transmissionUART(3);
	}
	while (commande == 4)
	{
		PORTA = 0x01;
		_delay_ms(500);
		PORTA = 0x00;
		_delay_ms(500);
		uart.transmissionUART(4);
	}
	//else
		PORTA = 0x01;
		_delay_ms(5000);
		PORTA = 0x00;
		_delay_ms(5000);
		uart.transmissionUART(0);
			
}

ISR(TIMER1_COMPA_vect)
{
	compteur++;
	if(emetteur.isIRSent_ && compteur == 8)
	{
		recepteur.minuterie_.setExpiree();
		compteur = 1;
	}
	else
	{
		emetteur.minuterie_.setExpiree();
		compteur = 1;
	}
	
}

ISR(INT0_vect) {
	if (emetteur.bouton_.CheckIfPressed()) 
	{
		emetteur.BoutonAppuye_ = true;
		emetteur.compteur_++;
		if (emetteur.compteur_ > 9)
		{
			emetteur.compteur_ = 1;
		}
		emetteur.minuterie_.partirMinuterie(250); //1/4 de seconde
	}
	EIFR |= (1 << INTF0);
}
