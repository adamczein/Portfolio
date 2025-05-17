/*
 * Nom:TP
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452

        TABLEAU D'ETAT PROBLEME 2
 CURRENT STATE || ENTREE || NEXT STATE || SORTIE
 -----------------------------------------------
      INIT     ||   0    ||    INIT    || ROUGE
      INIT     ||   1    ||     S1     || ROUGE
       S1      ||   0    ||     S2     || AMBRE
       S1      ||   1    ||     S1     || AMBRE
       S2      ||   0    ||     S2     || VERT
       S2      ||   1    ||     S3     || VERT
       S3      ||   0    ||     S4     || ROUGE
       S3      ||   1    ||     S3     || ROUGE
       S4      ||   0    ||     S4     || ETEINT
       S4      ||   1    ||     S5     || ÉTEINT
       S5      ||   0    ||     S6     || VERT
       S5      ||   1    ||     S5     || VERT
       S6      ||   0    ||    INIT    || ROUGE
       S6      ||   1    ||    INIT    || ROUGE
 */


 #include <avr/io.h> 
 #define F_CPU 8000000
 #include <util/delay.h>

const int ROUGE = 0x01;
const int VERT = 0x02;
const int PRESSED = 0x04;
const int MODE_SORTIE = 0xff;
const int ETEINT = 0x00;
bool currentStateIsPressed = false;

void CheckIfPressed(){ // Fonction qui verifie si le boutton D est active
    if(PIND & PRESSED){ 		//
        _delay_ms(10);			// Debounce
        if(PIND & PRESSED){		//
            currentStateIsPressed = true;
        }
    }
    else
        currentStateIsPressed = false;
}

void probleme2(){
    DDRB = MODE_SORTIE;
    enum State : int{state0, state1, state2, state3, state4, state5, state6}; //Les 7 etat sont definis
    State state = state0; //Etat initial indique
    
    for(;;){ //Loop infinie
        CheckIfPressed();
        switch(state){ //Switch case qui suit les etats du probleme
            case state0 :  //DEL libre : ROUGE
                PORTB = ROUGE;
                if (currentStateIsPressed == true)
                {
                    state = state1; 
                }
                break;
            case state1 : //Bouton pese : AMBRE
                while (currentStateIsPressed == true){  //While-loop pour Ambre 
                    PORTB = VERT;
                    _delay_ms(16); //Temps du delay determine par essaie-erreur
                    PORTB = ROUGE;
                    CheckIfPressed();
                }
                state = state2;
                break;
            case state2 : //Bouton relache : VERT 
                if(currentStateIsPressed == false){                              
                    PORTB = VERT;
                }
                else
                    state = state3;
                break;
            case state3 : //Bouton pese : ROUGE
                if (currentStateIsPressed == true){                              
                    PORTB = ROUGE;
                }
                else
                    state = state4;
                break;
            case state4 : //Bouton relache : ETEINT
                if(currentStateIsPressed == false){                               
                    PORTB = ETEINT;
                }
                else
                    state = state5;
                break;
            case state5 : //Bouton pese : VERT 
                if (currentStateIsPressed == true){                           
                    PORTB = VERT;
                }
                else
                    state = state6;
                break;
            case state6 : //Bouton relache : ROUGE                              
                state = state0;
                PORTB = ROUGE;
                break;
        }
    }
}

 int main(){
     probleme2();
     return 0;
 }

 
