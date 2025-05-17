#ifndef EMETTEURIR_H
#define EMETTEURIR_H

#include "Minuterie.h"
#include "Bouton.h"

class EmetteurIR {
public:
	EmetteurIR();
	void EnvoieIR();
	Minuterie minuterie_;
	bool isIRSent_;
	volatile bool BoutonAppuye_;
	volatile bool minuterieExpiree_;
	int compteur_;
	Bouton bouton_;
private:
	void modulation(char c);
	bool fin_;	
};
#endif
