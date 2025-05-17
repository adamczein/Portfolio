/*
 * Nom:CapteurLumiere.h
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
*/

#ifndef CAPTEURLUMIERE_H
#define CAPTEURLUMIERE_H
#include <can.h>
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>

class CapteurLumiere {
public:
	CapteurLumiere();
	void CapterLumiere(char port);
private:
	int modeSortie_;
	int modeEntree_;
	int ROUGE_;
	int VERT_;
};
#endif // !CAPTEURLUMIERE_H
