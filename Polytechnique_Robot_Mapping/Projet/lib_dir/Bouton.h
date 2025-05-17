/*
 * Nom:Bouton.h
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
 */

#ifndef BOUTON_H
#define BOUTON_H

#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>

class Bouton {
public:
	Bouton();
	bool CheckIfPressed();
	void initialisationIntExterne(void);
	uint8_t getBoutonPoussoir();
	int getPressed();
private:
	uint8_t boutonPoussoir_;
	int pressed_;
};
#endif