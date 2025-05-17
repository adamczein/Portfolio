/*
*	Nom: RecepteurIR.cpp
*	Auteur: Dylan Batista-Moniz
*			Jeremy Charland
*/
#define F_CPU 8000000

#include "RecepteurIR.h"

#define CAPTEUR 0x01

RecepteurIR::RecepteurIR()
{
	commande_ = 0;
	adresse_ = 0;
	compteur_ = 0;
	premierBouton_ = false;
}

int RecepteurIR::getCommande()
{
	return commande_;
}
int RecepteurIR::getAdresse()
{
	return adresse_;
}

void RecepteurIR::ReceptionIR(){ 
	
	//Initialisations
	//À changer dépendamment du port
	
	int valeurLue[12]; // tableau de 0 à 11, 12 valeurs ???
	
	while(!getCapteur() || premierBouton_){}
	
	if (!premierBouton_)
	{
		for(int i = -1; i <= 11; i++) //Comptant le start
		{
			if(i == -1)
			{
				while(getCapteur()){}
			}
			else
			{
				while(!getCapteur()){}
				minuterie_.partirMinuterie(1);//?????
				while(getCapteur()){}
				valeurLue[i] = minuterie_.getExpiree();
			}
		}
		for (int i=0; i <=6; i++)
		{
			commande_ += valeurLue[i] << i; //????
		}
		for (int i=7; i <=11; i++)
		{
			adresse_ += valeurLue[i] << (i-7); //????
		}
		}
	else
	{
		while(!minuterie_.getExpiree()){}
			
		commande_ = compteur_;
		adresse_ = 1;
	}
}

void initialisationPort()
{
    DDRD = 0X00; //PORTD en entrée
}

//Ces fonctions prennent le capteur
bool RecepteurIR::getCapteur()
{
    if (can_.lecture(CAPTEUR) < 700)
        return true;
    else
        return false;
}
