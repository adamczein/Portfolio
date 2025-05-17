
#include "Conducteur.h"

/*************************************************
Nom: Conducteur()
Fonction: Constructeur de la classe Conducteur
**************************************************/
Conducteur::Conducteur() {
	DDRD = 0xF0; // DDRB en mode sortie
	OCR1A = 0;
	OCR1B = 0;

	// TP4 - Pb3
	// Division de l'horlorge par 8 & Phase correct
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10); //Table 16-4.
	TCCR1B |= (1 << CS11);
	TCCR1C = 0;
}

/*************************************************
Nom: PWM
Fonction: Fonction qui permet le contr�le des moteurs � l'aide d'un PWM
**************************************************/
void Conducteur::PWM(uint16_t Droite, uint16_t Gauche, Direction sens) {
	if (Droite > 254)
		Droite = 254;
	if (Gauche > 254)
		Gauche = 254;
	
	switch (sens) {
		case avant:
			PORTD = (1 << 6); // 0x08
			PORTD = (1 << 5); // 0x04
			OCR1A = Droite; // 0.89 est un ajustment d�termin� par essaie-erreur
			OCR1B = 0.94*Gauche;
			break;
		case arriere:
			PORTD = ~(1 << 6); // Inverse pour la polarit�
			PORTD = ~(1 << 5); // Inverse pour la polarit�
			OCR1A = 0.92*Droite; // 0.92 est un ajustment d�termin� par essaie-erreur
			OCR1B = Gauche;
			break;
		case arret:
			PORTD = (1 << 6);
			PORTD = (1 << 5);
			OCR1A = 0;
			OCR1B = 0;
			break;
		case droite:
			PORTD = (1 << 6);
			PORTD = (1 << 5);
			OCR1A = Droite;
			OCR1B = 0; // Moteur gauche d�sactiv�
			break;
		case gauche:
			PORTD = (1 << 6);
			PORTD = (1 << 5);
			OCR1A = 0; // Moteur droit d�sactiv�
			OCR1B = Gauche;
			break;
	}
}
