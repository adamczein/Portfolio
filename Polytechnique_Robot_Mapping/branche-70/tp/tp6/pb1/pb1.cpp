/*
 * Nom:TP6 PB1
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
const int MODE_ENTREE = 0x00;
const int MODE_SORTIE = 0xff;
const int ETEINT = 0x00;
volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;
volatile bool currentStateIsPressed = false;
volatile bool MinuterieCommencee = false;
volatile int compteur =0;
volatile bool fin = false;

void CheckIfPressed(){ // Fonction qui verifie si le bouton blanc est active
    if(PIND & PRESSED){ 		//
        _delay_ms(10);			// Debounce
        if(PIND & PRESSED){		//
            currentStateIsPressed = false; //Dans ce setup, la polarite du courant du bouton est inversee. Alors, si le bouton est detecte comme pese, mettre false.
        }
    }
    else
        currentStateIsPressed = true; //Si le bouton est detecte comme pas pese, il est en fait pese
}

void partirMinuterie ( uint16_t duree ) {

    MinuterieCommencee = true;
    minuterieExpiree = 0;

    TCNT1 = 0; //Initialisation du compteur

    OCR1A = duree; //Valeur a laquelle le timer est comparee

    TCCR1A |= (1 << COM1A0) ; //Activation du "compare match"

    TCCR1B |= (1 << CS12) | (1 << CS10) ; //Clock select /1024

    TCCR1C = 0;

    TIMSK1 |= (1 << OCIE1A) ; //Output compare A match interrupt enable

}

ISR (TIMER1_COMPA_vect) { //Interrupteur lorsque le timer est fini
    minuterieExpiree = 1;
    MinuterieCommencee = 0;
}

void initialisation ( void ) {

    cli(); //Cli empeche les interruptions

    DDRB = MODE_SORTIE; //Port B en mode sortie
    DDRD = MODE_ENTREE; //Port D en mode entree

    EICRA |= (1 << ISC00); //Permet les inetrruptions externes aux changement de niveau du bouton-poussoir

    sei (); //Permet les interruptions
}

void finProgramme(){ //Fonction qui execute la routine de couleurs
    minuterieExpiree = 0;
    partirMinuterie(3907);
    while(!minuterieExpiree){
        PORTB = VERT;
        _delay_ms(50); 
        PORTB = ETEINT;
        _delay_ms(20);
    }
    _delay_ms(2000);
    for(int i=0;i <= (compteur/2); i++){
        PORTB = ROUGE;
        _delay_ms(250);
        PORTB = ETEINT;
        _delay_ms(250);
    }
    PORTB = VERT;
    _delay_ms(1000);
    PORTB = ETEINT;

    minuterieExpiree = 0;
    MinuterieCommencee = 0;
    compteur = 0;
    fin = false;
}

int main(){
    initialisation(); //Initialisation des pots et flags
    for(;;){ //Loop infini
        CheckIfPressed();
        while(currentStateIsPressed && compteur <= 120){
            CheckIfPressed();
            if(!MinuterieCommencee){
                partirMinuterie(781);
                compteur++;
                fin = true;
            }            
        }
        if(fin){
            finProgramme();
        }        
    }
    
    return 0;
}