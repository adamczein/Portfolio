/*
 * Nom:AffichageMemoire.h
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
*/

#ifndef MEMOIRE_H
#define MEMOIRE_H

#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>
#include "memoire_24.h"

class UART {
public:
	UART();
	void initialisationUART(void);
	void transmissionUART(uint8_t donnee);
	void affichageMemoire();
	uint8_t lectureUART();
private:
	int modeSortie_;
};
#endif // !MEMOIRE_H
