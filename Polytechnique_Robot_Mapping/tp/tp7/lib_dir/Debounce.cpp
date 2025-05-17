/*
 * Nom:Debounce.cpp
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
 */

 #include "Debounce.h"
 #include <avr/io.h> 
 #include <util/delay.h>

const int PRESSED = 0x04;

bool CheckIfPressed(){ // Fonction qui verifie si le boutton D est active
    if(PIND & PRESSED){ 		//
        _delay_ms(10);			// Debounce
        if(PIND & PRESSED){		//
            return true;
        }
    }
    return false;
} 
