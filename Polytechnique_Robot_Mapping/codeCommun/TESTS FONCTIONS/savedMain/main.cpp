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
int adresseDebut = 0x00;

// Constantes
const uint8_t DBT = 0x01;   // Debut des instructions
const uint8_t ATT = 0x02;   // Attendre
const uint8_t DAL = 0x44;   // Alumer DEL
const uint8_t DET = 0x45;   // Eteindre DEL
const uint8_t SGO = 0x48;   // Sonorite GO
const uint8_t SAR = 0x09;   // Sonorite Arret
const uint8_t MAR = 0x60;   // Arret des moteurs
const uint8_t MAR1 = 0x61;  // Arret des moteurs
const uint8_t MAV = 0x62;   // Avancer
const uint8_t MRE = 0x63;   // Reculer
const uint8_t TRD = 0x64;   // Tourner a droite
const uint8_t TRG = 0x65;   // Tourner a gauche
const uint8_t DBC = 0xC0;   // Debut de boucle
const uint8_t FBC = 0xC1;   // Fin de boucle
const uint8_t FIN = 0xFF;   // Fin des instructions

int main() {

    DDRD = 0xFF; //Conducteur
    DDRA = 0xFF; //DEL
	DDRB = 0xFF; //Son
	
    // Objets
    DEL del = DEL();
    Conducteur conducteur;
	Sonorite son;
    Memoire24CXXX memoire;
    memoire.init();
    UART uart;
    uart.initialisationUART();


    // Variables
    uint8_t action;
    uint8_t op;
    bool debut = false;
    bool boucle = false;
    int nbLoop = 0;
    int adresseParcours = adresseDebut + 0;
    int adresseTampon;
    
    /*
    INSTR OP
    INSTR OP
    INSTR OP
    
    memoire.ecriture(i++,0x01);
    memoire.ecriture(i++,0x00);
    memoire.ecriture(i++,0x48);
    memoire.ecriture(i++,60);
    memoire.ecriture(i++,0x02);
    memoire.ecriture(i++,200);
    memoire.ecriture(i++,0x09);
    memoire.ecriture(i++,0x00);
    memoire.ecriture(i++,0xFF);
    */

    while(action != DBT){
        memoire.lecture(adresseParcours, &action);
        _delay_ms(5);
        uart.transmissionUART(action);
        _delay_ms(5);
        adresseParcours += 2; // On passe le code d'operation
    }   

    if(action == DBT) { 
        debut = true;
        //PORTA = 0x01;
        del.Allumer(0x02,'A',0);
        _delay_ms(500);
        //PORTA = 0x00;
        del.Allumer(0x00,'A',0); 
        _delay_ms(500);
        //PORTA = 0x01;
        del.Allumer(0x02,'A',0);
        _delay_ms(500);
        del.Allumer(0x00,'A',0);
        //PORTA = 0x00;
    }
    while(debut == true) {
        memoire.lecture(adresseParcours, &action);
        _delay_ms(5);
        uart.transmissionUART(action);
        _delay_ms(5);
        adresseParcours++;
        switch(action){   
            case ATT:
                memoire.lecture(adresseParcours, &op);
                _delay_ms(5);
                uart.transmissionUART(op);
                _delay_ms(5);
                adresseParcours++;
                //DELAI DE 25MS EN FONCTION DE L'OPERANDE
                for (int i = 0; i < op; i++)	
                    _delay_ms(25);
                break;
            case DAL:
                adresseParcours++; // On passe le code d'operation vide 0x00
                //Allumer LA DEL EN VERT 
                //PORTA = 0x01;
                del.Allumer(0x01,'A',0);
                break;
            case DET:
                adresseParcours++; // On passe le code d'operation vide 0x00
                //ETEINDRE LA DEL
                //PORTA = 0x00;
                del.Allumer(0x00,'A',0);
                break;
            case SGO:
                memoire.lecture(adresseParcours, &op);
                _delay_ms(5);
                uart.transmissionUART(op);
                _delay_ms(5);
                adresseParcours++;
                son.jouerNote(op,1000); //////////////////////////////////////////////////////////
                break;
            case SAR:
                adresseParcours++; // On passe le code d'operation vide 0x00
                son.arretNote();
                break;
            case MAR:
                adresseParcours++; // On passe le code d'operation vide 0x00
                //ARRETER LE ROBOT
                conducteur.PWM(0, 0, arret);
                break;
            case MAR1: //2 FOIS LA MEME CHOSE
                adresseParcours++; // On passe le code d'operation vide 0x00
                conducteur.PWM(0, 0, arret);
                break;           
            case MAV:
                memoire.lecture(adresseParcours, &op);
                _delay_ms(5);
                uart.transmissionUART(op);
                _delay_ms(5);
                adresseParcours++;
                op = op/255;
                //FAIRE AVANCER LE ROBOT
                conducteur.PWM(op, op, avant);
                break;
            case MRE:
                memoire.lecture(adresseParcours, &op);
                _delay_ms(5);
                uart.transmissionUART(op);
                _delay_ms(5);
                adresseParcours++;
                op = op/255;
                //RECULER LE ROBOT
                conducteur.PWM (op, op, arriere);
                break;
            case TRD:
                adresseParcours++; // On passe le code d'operation vide 0x00
                //FAIRE TOURNER LE ROBOT A DROITE
                conducteur.PWM (0, 255, gauche);
                _delay_ms(1300);
                conducteur.PWM (0, 0, arret);
                break;
            case TRG:
                //FAIRE TOURNER LE ROBOT A DROITE
                 conducteur.PWM (255, 0, droite);
                _delay_ms(1300);
                conducteur.PWM (0, 0, arret);
                break;
            case DBC:
                if(boucle == false){
                    memoire.lecture(adresseTampon, &op);
                    _delay_ms(5);
                    uart.transmissionUART(op);
                    _delay_ms(5);
                    adresseParcours++;
                    adresseTampon = adresseParcours + 2;
                    boucle = true;
                    nbLoop = op;
                }
                break;
            case FBC:
                adresseParcours++; // On passe le code d'operation vide 0x00
                if(nbLoop > 0){
                    adresseParcours = adresseTampon;
                    nbLoop--;
                }
                else
                    boucle = false;
                break;
            case FIN:
                adresseParcours++; // On passe le code d'operation vide 0x00
                //ARRETER LES MOTEURS DU ROBOT
                conducteur.PWM (0, 0, arret);
                //ARRETER LE SON DU ROBOT
                son.arretNote();
                //FIN (NE PLUS CONTINUER A LIRE)
                debut= false;
                break;            
        }
    }
    return 0;
}
