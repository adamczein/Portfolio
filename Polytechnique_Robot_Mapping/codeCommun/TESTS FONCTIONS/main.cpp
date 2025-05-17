#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "../lib_dir/DEL.h"
#include "../lib_dir/Sonorite.h"
#include "../lib_dir/memoire_24.h"
#include "../lib_dir/Conducteur.h"
#include "../lib_dir/Bouton.h"
#include "../lib_dir/AffichageMemoire.h"

// Adresse du debut de parcours
int main(){
    Sonorite son;
    DDRB = 0xFF;
    for(;;){
        son.jouerNote(60, 1000);
        _delay_ms(1000);
        son.arretNote();
        _delay_ms(1000);
        son.jouerNote(60, 1000);
        _delay_ms(1000);
        son.arretNote();
        _delay_ms(1000);
    }
}
