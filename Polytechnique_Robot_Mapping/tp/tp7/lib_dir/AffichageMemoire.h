/*
 * Nom:AffichageMemoire.h
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
*/

#define F_CPU 8000000
#include <avr/io.h> 


void initialisationUART(void);

void transmissionUART( uint8_t donnee );

void affichageMemoire();