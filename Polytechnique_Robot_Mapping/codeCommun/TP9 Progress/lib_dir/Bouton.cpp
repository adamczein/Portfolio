/*
 * Nom:Bouton.cpp
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
*/

#include "Bouton.h"

/*************************************************
Nom: Bouton()
Fonction: Constructeur de la classe Bouton
**************************************************/
Bouton::Bouton() {
	boutonPoussoir_ = 0;
	pressed_ = 0x04;
}

/*************************************************
Nom: CheckIfPressed
Fonction: Vérifie si le bouton D est activé.
Debounce intégré.
**************************************************/
bool Bouton::CheckIfPressed() {

	if (PIND & pressed_) { 		//
		_delay_ms(10);			// Debounce
		if (PIND & pressed_) {		//
			return true;
		}
	}
	return false;
}

/*************************************************
Nom: initialisationIntExterne
Fonction: Permet les interruptions au niveau du bouton pressoir
**************************************************/
void Bouton::initialisationIntExterne(void) {
	
	int MODE_SORTIE = 0xff;

	// Bloquer de nouvelles interuptions

	cli();

	// configuration des ports

	DDRB = MODE_SORTIE;

	// Masque qui permet les interruptions externes

	EIMSK |= (1 << INT0);

	// Sensibiliser les interruptions externes au niveau du bouton

	EICRA |= (1 << ISC00);

	// Permettre de nouvelles interruptions

	sei();
}

/*************************************************
Nom: getBoutonPoussoir
Fonction: Retourne le statut (uint8_t) du boutton. Utilisé dans le ISR d'interruption
**************************************************/
uint8_t Bouton::getBoutonPoussoir() {
	return boutonPoussoir_;
}

/*************************************************
Nom: getPressed
Fonction: Retourne le status (En bool) du bouton
**************************************************/
int Bouton::getPressed() {
	return pressed_;
}

// CODE DE L'INTERRUPTION
/*
//volatile uint8_t boutonPoussoir;

ISR(INT0_vect) {
	int MODE_SORTIE = 0xff;
	if (CheckIfPressed()) {
		boutonPoussoir = 1;
		//boutonPoussoir_ = 1;
	}
	EIFR |= (1 << INTF0);
}
*/