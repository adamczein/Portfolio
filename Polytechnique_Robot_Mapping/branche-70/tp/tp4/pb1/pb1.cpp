/*
 * Nom:TP4 pb1
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
*/

 #include <avr/io.h> 
 #define F_CPU 8000000
 #include <util/delay.h>
 #include <avr/interrupt.h>

const int ROUGE = 0x01;
const int VERT = 0x02;
const int PRESSED = 0x04;
const int MODE_SORTIE = 0xff;
const int ETEINT = 0x00;
volatile bool currentStateIsPressed = false;
enum State {state0, state1, state2, state3, state4, state5, state6}; //Les 7 etat sont definis
volatile State state = state0; //Etat initial indique

// placer le bon type de signal d'interruption

// à prendre en charge en argument

void CheckIfPressed(){ // Fonction qui verifie si le boutton D est active
    _delay_ms(10);
    if(PIND & PRESSED)	//
        currentStateIsPressed = true;
    else
        currentStateIsPressed = false;
}

void lumieres(){
    switch(state){ //Switch case qui suit les etats du probleme
        case state0 :  //DEL libre : ROUGE
            PORTC = 0x01;
            if (currentStateIsPressed == true)
            {
                state = state1; 
            }
            break;
        case state1 : //Bouton pese : AMBRE
            while (currentStateIsPressed == true){  //While-loop pour Ambre 
                PORTC = 0x01;
                _delay_ms(500); //Temps du delay determine par essaie-erreur
                PORTC = 0x02;
                CheckIfPressed();
                }
            state = state2;
            break;
        case state2 : //Bouton relache : VERT 
            if(currentStateIsPressed == false){                              
                PORTC = 0x02;
            }
            else
                state = state3;
            break;
        case state3 : //Bouton pese : ROUGE
            //if (currentStateIsPressed == trueotePW{                              
            //    PORTC = 0x01;
            //}
            //else
            //    state = state4;
            break;
        case state4 : //Bouton relache : ETEINT
            if(currentStateIsPressed == false){                               
               // PORTB = ETEINT;
            }
            else
                state = state5;
            break;
        case state5 : //Bouton pese : VERT 
            if (currentStateIsPressed == true){                           
               // PORTB = VERT;
            }
            else
                state = state6;
            break;
        case state6 : //Bouton relache : ROUGE                              
            state = state0;
            //PORTB = ROUGE;
            break;
    }
}

ISR(INT0_vect) {

    // laisser un delai avant de confirmer la réponse du

    // bouton-poussoir: environ 30 ms (anti-rebond)

        //Debounce integre dans CheckIfPressed()

    // se souvenir ici si le bouton est pressé ou relâché

    CheckIfPressed();

    // changements d'états tels que ceux de la

    // semaine précédente

    lumieres();

    // Voir la note plus bas pour comprendre cette instruction et son rôle

    EIFR |= (1 << INTF0) ;

}

void initialisation ( void ) {

    // cli est une routine qui bloque toutes les interruptions.

    // Il serait bien mauvais d'être interrompu alors que

    // le microcontroleur n'est pas prêt...

    cli();


    // configurer et choisir les ports pour les entrées

    // et les sorties. DDRx... Initialisez bien vos variables

    DDRC = MODE_SORTIE;

    // cette procédure ajuste le registre EIMSK

    // de l’ATmega324PA pour permettre les interruptions externes

    EIMSK |= (1 << INT0);

    // il faut sensibiliser les interruptions externes aux

    // changements de niveau du bouton-poussoir

    // en ajustant le registre EICRA

    EICRA |= (1 << ISC00);

    // sei permet de recevoir à nouveau des interruptions.

    sei ();

}

int main(){
	DDRD = 0xF0;
    initialisation();
    for(;;){
        lumieres();
    }
    return 0;
}

 
