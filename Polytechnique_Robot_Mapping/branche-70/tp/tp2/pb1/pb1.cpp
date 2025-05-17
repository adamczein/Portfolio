/*
 * Nom:TP
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452

        TABLEAU D'ETAT PROBLEME 1
 CURRENT STATE || ENTREE || NEXT STATE || SORTIE
 -----------------------------------------------
      INIT     ||   0    ||    INIT    || ETEINT
      INIT     ||   1    ||     S0     || ETEINT
       S0      ||   0    ||     S0     || ETEINT
       S0      ||   1    ||     S1     || ETEINT
       S1      ||   0    ||     S1     || ETEINT
       S1      ||   1    ||     S2     || ETEINT
       S2      ||   0    ||     S2     || ETEINT
       S2      ||   1    ||     S3     || ETEINT
       S3      ||   0    ||     S3     || ETEINT
       S3      ||   1    ||     S4     || ETEINT
       S4      ||   0    ||     S4     || ETEINT
       S4      ||   1    ||    INIT    || ROUGE

 */


 #include <avr/io.h> 
 #define F_CPU 8000000
 #include <util/delay.h>

const int ROUGE = 0x01;
const int VERT = 0x02;
const int PRESSED = 0x04;
const int MODE_SORTIE = 0xff;
const int ETEINT = 0x00;

void probleme1(){
    DDRB = MODE_SORTIE; //Le port B est en mode sortie
    enum State : int{state1, state2, state3, state4, state5}; //Les 5 etats sont definis
    State state = state1; //L'etat initial est indique
    bool previousStateIsPressed = false;
    for(;;){ //Loop infinie
        if(PIND & PRESSED){        //
            _delay_ms(10);         // Debounce
            if(PIND & PRESSED){    //
                if(previousStateIsPressed == false){
                    previousStateIsPressed = true;
                    switch(state){
                        case state1 : state = state2;   break;  
                        case state2 : state = state3;   break;
                        case state3 : state = state4;   break;
                        case state4 : state = state5;   break;
                        case state5 : PORTB = ROUGE;
                                     _delay_ms(1000);
                                     PORTB = ETEINT;
                                     state = state2;
                                     break;
                    }
                }
            }
            else{
                previousStateIsPressed = false;
            }
        }
    }    
}

 int main(){
     probleme2();
     return 0;
 }

 
