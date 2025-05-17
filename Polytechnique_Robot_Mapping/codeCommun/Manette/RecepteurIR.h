#ifndef RECEPTEURIR_H
#define RECEPTEURIR_H

#define F_CPU 8000000

#include "Minuterie.h"
#include "can.h"
#include "Bouton.h"

class RecepteurIR {
public:
	RecepteurIR();
	void ReceptionIR();
	int getCommande();
	int getAdresse();
	Minuterie minuterie_;
private:
	int commande_;
	int adresse_;
	void initialisationPort();
	bool getCapteur();
	volatile bool premierBouton_;
	Bouton bouton_;
	can can_;
	int compteur_;

};
#endif
