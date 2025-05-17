/*
 * Nom:Sonorite.cpp
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          
*/
#include "Sonorite.h"

/*************************************************
Nom: Sonorite()
Fonction: Constructeur de la classe Sonorite
**************************************************/
Sonorite::Sonorite(){}

/*************************************************
Nom: notePWM
Fonction: Fonction PWM du haut-parleur. Le PWM permet d'atteindre diff�rentes fr�quences selon le temps actif et inactif dans la p�riode d'une note
**************************************************/
void Sonorite::notePWM(int indice, int octave){
	//DDRB = 0xFF;
	
	TCCR0A |= (1 << WGM01);
    TCCR0A |= (1 << COM0A0);
    TCCR0B |= (1 << CS02);

    OCR0A = actif[indice-45]*octave;
}

/*************************************************
Nom: arretNote
Fonction: Fonction qui �teint le haut-parleur en mettant le output compare register � 0
**************************************************/
void Sonorite::arretNote() {
	TCCR0A&=(0<<COM0A0);
}

/*
void Sonorite::jouerNote(int indice, double duree, int octave){
	int inactif = (int)((periode[45 - indice]/octave) - actif[45 - indice]);
	int actif2 = (int)(actif[45 - indice]);
	int nbRepetitions = (int)(duree / (periode[45 - indice] / octave));
	DelayVariable delay = DelayVariable();
	for (int i = 0; i < nbRepetitions; i++) {
		PORTB = 0x01;
		delay.delayMsVariable(actif2);
		PORTB = 0x00;
		delay.delayMsVariable(inactif);
	}
}
*/
