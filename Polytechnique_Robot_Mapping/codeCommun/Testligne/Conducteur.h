
#ifndef CONDUCTEUR_H
#define CONDUCTEUR_H

#include <avr/io.h>
#include <util/delay.h>

enum Direction { avant, arriere, arret, droite, gauche };

class Conducteur {
public:
	Conducteur();
	void PWM(uint16_t Droite, uint16_t Gauche, Direction sens);
private:
	int modeSortie_ = 0xFF;
};
#endif // !CONDUCTEUR_H
