/*
 * Fichier: DelayVariable.h
 * Auteurs: Dylan Batista-Moniz - 1954776
 * Date: 18 mars 2019
 * Description: delay par variable
*/
#ifndef DELAY_H
#define DELAY_H
#include <avr/io.h>
#include <util/delay.h>
class DelayVariable {
public:
	DelayVariable();
	void delayMsVariable(int delay);
};
#endif
