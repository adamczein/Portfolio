/*
 * Nom:Bouton.cpp
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          
*/
#ifndef DEL_H
#define DEL_H

#include <avr/io.h> 

class DEL {
public:
	DEL();
	void allumerDEL(uint8_t couleurHexa, char port, int rangeePin);
private:
	int modeSortie_;
};
#endif /* DEL_H */
