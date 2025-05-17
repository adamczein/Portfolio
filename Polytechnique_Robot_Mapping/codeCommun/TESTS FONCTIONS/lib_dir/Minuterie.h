/*
 * Nom:Minuterie.h
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452

*/
#ifndef MINUTERIE_H
#define MINUTERIE_H

#include <avr/io.h> 
#include <avr/interrupt.h>

class Minuterie {
public:
	Minuterie();
	void partirMinuterie(uint16_t duree);
	uint8_t getExpiree();
	bool getComencee();
	void setExpiree();
	void initialisation();
private:
	uint8_t minuterieExpiree_;
	bool minuterieCommencee_;
};
#endif