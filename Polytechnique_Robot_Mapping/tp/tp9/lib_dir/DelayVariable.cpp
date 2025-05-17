/*
 * Fichier: DelayVariable.cpp
 * Auteurs: Dylan Batista-Moniz - 1954776
 * Date: 18 mars 2019
 * Description: delay par variable
*/
#include "DelayVariable.h"

/*************************************************
Nom: DelayVariable()
Fonction: Constructeur de la classe DelayVariable
**************************************************/
DelayVariable::DelayVariable(){}

/*************************************************
Nom: delayMsVariable
Fonction: Fontion qui permet un delay prennant en parametre une variable au lieux d'une constante
**************************************************/
void DelayVariable::delayMsVariable(int delay) {
	for (int i = 0; i < delay; i++)
		_delay_ms(1);
}