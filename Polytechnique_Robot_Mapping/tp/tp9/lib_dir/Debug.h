/*
 * Nom:Debug.h
 * Auteurs: Dylan Batista-Moniz - 1954776
*/

#define F_CPU 8000000
#include <avr/io.h> 
#include "AffichageMemoire.h"
#include <string.h>
#include "memoire_24.h"

#ifdef	DEBUG
//Si la fonction est precisee, on passe str en parametre a l'ordi
//On envoie un caractere a la fois. Une fois que cest fait, nous pouvons utilise la commande serieViaUSB pour afficher les octets a l'ecran
Memoire24CXXX uart = Memoire24CXXX(); 
#define DEBUG_PRINT(str)
	initialisationUART();
	for (uint8_t i = 0; i < sizeof(str); i++) {
		transmissionUART(str[i]);
	}
#else
//Sinon la fonction ne fait rien
#define DEBUG_PRINT(str) do {} while (0) 
#endif