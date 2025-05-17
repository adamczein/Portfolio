/*
 * Nom:TP4 pb1
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
*/

 #include <avr/io.h> 
 #define F_CPU 8000000
 #include <util/delay.h>
 #include <avr/interrupt.h>
 #include <memoire_24.h>
 
 const int MODE_SORTIE = 0xFF;
 const int ETEINT = 0x00;
 const int VERT = 0x01;
 const int ROUGE = 0x02;

int main(){
    DDRB = MODE_SORTIE;
    const int longueur = 45;
    Memoire24CXXX memoire;
    char* tableEcrite = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    char* tableLue    = "000000000000000000000000000000000000000000000";
    
    memoire.ecriture(0x00,(uint8_t*) &tableEcrite, longueur);
    _delay_ms(5);

    bool identique = true;
    
    memoire.lecture(0x00,(uint8_t*) &tableLue, longueur);
    _delay_ms(5);
    
    for (int i =0; i < sizeof(tableEcrite); i++){
        if(tableLue[i]!=tableEcrite[i]){
            identique = false;
        }
    }

    //PAS IDENTIQUE
    if(identique)
        PORTB = VERT;
    else
        PORTB = ROUGE;
    return 0;
}
