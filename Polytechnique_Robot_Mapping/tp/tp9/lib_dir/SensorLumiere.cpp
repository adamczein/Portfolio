/*
 * Nom:CapteurLumiere.cpp
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
*/

#include "SensorLumiere.h"

/*************************************************
Nom: CapterLumiere()
Fonction: Constructeur de la classe CapteurLumiere
**************************************************/
CapteurLumiere::CapteurLumiere() {
	modeSortie_ = 0xff;
	modeEntree_ = 0x00;
	ROUGE_ = 0x01;
	VERT_ = 0x02;
}

/*************************************************
Nom: CapterLumiere
Fonction: Fonction qui prend en parametre le port où le capteur est connecté.
		  Allume la DEL à une certaine couleur selon l'intensité de la lumière captée.
**************************************************/
void CapteurLumiere::CapterLumiere(char port){
    DDRA = modeEntree_;
    DDRB = modeSortie_;
    can sensor = can();

    uint16_t tampon;
    uint8_t tampon2;
	if (port == ('A' | 'a')) {
		tampon = sensor.lecture(1); //Nous obtennons une valeur 16bits dont les 10lsb possedent la valeur du sensor
		tampon2 = tampon >> 2; //Nous shiftons de 2bits vers la droite pour eliminer les 2 bits sans signification
							   // la valeur est convertie en 8bits
		if (tampon2 < 175) { //150 determine par essaie-erreur
			PORTA = VERT_;
		}
		else if (tampon2 > 245) { //250 determine par essaie-erreur
			PORTA = ROUGE_;
		}
		else {
			PORTA = VERT_;
			_delay_ms(1); //Temps du delay determine par essaie-erreur
			PORTA = ROUGE_;
		}
	}
	if (port == ('B' | 'b')) {
		tampon = sensor.lecture(1); //Nous obtennons une valeur 16bits dont les 10lsb possedent la valeur du sensor
		tampon2 = tampon >> 2; //Nous shiftons de 2bits vers la droite pour eliminer les 2 bits sans signification
							   // la valeur est convertie en 8bits
		if (tampon2 < 175) { //150 determine par essaie-erreur
			PORTB = VERT_;
		}
		else if (tampon2 > 245) { //250 determine par essaie-erreur
			PORTB = ROUGE_;
		}
		else {
			PORTB = VERT_;
			_delay_ms(1); //Temps du delay determine par essaie-erreur
			PORTB = ROUGE_;
		}
	}
	if (port == ('C' | 'c')) {
		tampon = sensor.lecture(1); //Nous obtennons une valeur 16bits dont les 10lsb possedent la valeur du sensor
		tampon2 = tampon >> 2; //Nous shiftons de 2bits vers la droite pour eliminer les 2 bits sans signification
							   // la valeur est convertie en 8bits
		if (tampon2 < 175) { //150 determine par essaie-erreur
			PORTC = VERT_;
		}
		else if (tampon2 > 245) { //250 determine par essaie-erreur
			PORTC = ROUGE_;
		}
		else {
			PORTC = VERT_;
			_delay_ms(1); //Temps du delay determine par essaie-erreur
			PORTC = ROUGE_;
		}
	}
	else if (port == ('D' | 'd')) {
		tampon = sensor.lecture(1); //Nous obtennons une valeur 16bits dont les 10lsb possedent la valeur du sensor
		tampon2 = tampon >> 2; //Nous shiftons de 2bits vers la droite pour eliminer les 2 bits sans signification
							   // la valeur est convertie en 8bits
		if (tampon2 < 175) { //150 determine par essaie-erreur
			PORTD = VERT_;
		}
		else if (tampon2 > 245) { //250 determine par essaie-erreur
			PORTD = ROUGE_;
		}
		else {
			PORTD = VERT_;
			_delay_ms(1); //Temps du delay determine par essaie-erreur
			PORTD = ROUGE_;
		}
	}
}
