 /*
*	Nom: EmetteurIR.cpp
*	Auteur: Dylan Batista-Moniz
*			Jeremy Charland
*	Description:	Code du second robot agissant comme manette du premier robot.
*					Cette manette ne fait qu'emettre le signal pour le point de depart.
*					Une fois que c'est fait, la communication est finie
*					Le robot recepteur doit commencer la routine au point donne et continuer la routine
*					EX:	Depart = 3
*						Robot routine = 3, 4, 1, 2
*
*						Deprat = 2
*						Robot routine = 2, 3, 4, 1
*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include "PWM.h"
#include "EmetteurIR.h"


EmetteurIR::EmetteurIR()
{
	isIRSent_ = false;
	BoutonAppuye_ = false;
	minuterieExpiree_ = false;
	compteur_ = 0;
	fin_ = false;	
}

void EmetteurIR::modulation(char c) {
	PWM(F_CPU/38000);
	//PORTC = 0x01;
	if (c == '1')
		_delay_us(1200);
	else if (c == '0')
		_delay_us(600);
	else if (c == 'S') // S pour Start
		_delay_us(2400);
	PWM(0);
	_delay_us(600); //Delay 600us
}

//Main
void EmetteurIR::EnvoieIR(){ 
	//Initialisations
	DDRB = 0xFF; // PORTB mode sortie
	bouton_.initialisationIntExterne(); //PORTB EN MODE SORTIE
	
	while (!BoutonAppuye_) {
		;
	}

	//LES COMMANDES ET ADRESSES SONT TOUTES LITTLE ENDIAN
	while (!fin_) {
		if (minuterie_.getExpiree()) {
			modulation('S');	//Start
			switch (compteur_) {
			case(1):			//1000000
				modulation('1');
				for (int i = 0; i < 6; i++) {
					modulation('0');
				}
				fin_ = true;
				break;
			case(2):			//0100000
				modulation('0');
				modulation('1');
				for (int i = 0; i < 5; i++) {
					modulation('0');
				}
				fin_ = true;
				break;
			case(3):			//1100000
				modulation('1');
				modulation('1');
				for (int i = 0; i < 5; i++) {
					modulation('0');
				}
				fin_ = true;
				break;
			case(4):			//0010000
				modulation('0');
				modulation('0');
				modulation('1');
				for (int i = 0; i < 4; i++) {
					modulation('0');
				}
				fin_ = true;
				break;
			case(5):			//1010000
				modulation('S');
				modulation('1');
				modulation('0');
				modulation('1');
				for (int i = 0; i < 4; i++) {
					modulation('0');
				}
				fin_ = true;
				break;
			case(6):			//0110000
				modulation('0');
				modulation('1');
				modulation('1');
				for (int i = 0; i < 4; i++) {
					modulation('0');
				}
				fin_ = true;
				break;
			case(7):			//1110000
				for (int i = 0; i < 3; i++) {
					modulation('1');
				}
				for (int i = 0; i < 4; i++) {
					modulation('0');
				}
				fin_ = true;
				break;
			case(8):			//0001000
				for (int i = 0; i < 3; i++) {
					modulation('0');
				}
				modulation('1');
				for (int i = 0; i < 3; i++) {
					modulation('0');
				}
				fin_ = true;
				break;
			case(9):			//1001000
				modulation('1');
				modulation('0');
				modulation('0');
				modulation('1');
				for (int i = 0; i < 3; i++) {
					modulation('0');
				}
				fin_ = true;
				break;
			}
			//adresse
			//10000
			modulation('1');
			for (int i = 0; i < 4; i++) {
				modulation('0');
			}
		}
	}
	isIRSent_ = true;
}

/*
void sircPWM(int commande) {
	TCCR1A |= (1 << WGM01);
	TCCR1A |= (1 << COM0A0);
	TCCR1B |= (1 << CS02);

	OCR1A = commande;
}

void finalPWM(double duree) {
	sircPWM(1);

}

void forLoopPWM(int nbDeZeros) {
	for (int i = 0; i < nbDeZeros; i++) { //0000
		sircPWM(0.6);
		_delay_us(600);
	}
}
*/
