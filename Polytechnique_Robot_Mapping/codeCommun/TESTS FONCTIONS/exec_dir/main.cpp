#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "../lib_dir/DEL.h"
#include "../lib_dir/Sonorite.h"
#include "../lib_dir/memoire_24.h"
#include "../lib_dir/Conducteur.h"
#include "../lib_dir/Bouton.h"
#include "../lib_dir/AffichageMemoire.h"
#include "../lib_dir/Minuterie.h"

int main(){
    Conducteur conducteur;
    //DDRB = 0xFF;
    for(;;){
        conducteur.PWM(150,150,avant);
        _delay_ms(1000);
        //conducteur.PWM(150,150,arret);
        //_delay_ms(1000);
    }
}
