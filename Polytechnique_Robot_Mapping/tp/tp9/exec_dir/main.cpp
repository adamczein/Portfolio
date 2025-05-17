#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "../lib_dir/DEL.h"
#include "../lib_dir/Sonorite.h"
#include "../lib_dir/memoire_24.h"
#include "../lib_dir/Conducteur.h"
#include "../lib_dir/Bouton.h"
#include "../lib_dir/AffichageMemoire.h"

int addresseDebut = 0x00;
const uint8_t DBT = 0x01;
const uint8_t ATT = 0x02;
const uint8_t DAL = 0x44;
const uint8_t DET = 0x45;
const uint8_t SGO = 0x48;
const uint8_t SAR = 0x09;
const uint8_t MAR = 0x60;
const uint8_t MAR1 = 0x61;
const uint8_t MAV = 0x62;
const uint8_t MRE = 0x63;
const uint8_t TRD = 0x64;
const uint8_t TRG = 0x65;
const uint8_t DBC = 0xC0;
const uint8_t FBC = 0xC1;
const uint8_t FIN = 0xFF;

int main() {

    DDRD = 0xFF; //Conducteur
    DDRA = 0xFF; //DEL
	DDRB = 0xFF; //Son
	
    // Appel des objets
    DEL del;
    Conducteur conducteur;
	Sonorite son;
    Memoire24CXXX memoire;
    memoire.init();
    UART uart;
    uart.initialisationUART();


    // Appel des variables
    uint8_t action;
    uint8_t op;
    bool debut = false;
    bool boucle = false;
    int nbLoop = 0;
    int adresseParcours = addresseDebut + 2;
    int adresseTampon;
    
	// Lecture de la m�moire sans executer les actions tant que DBT n'est pas d�tect�
    while(action != DBT){
        memoire.lecture(adresseParcours, &action);
        _delay_ms(5);
        uart.transmissionUART(action);
        _delay_ms(5);
        adresseParcours++;
    }   

	// Routine du d�but (Clignotement de la DEL) et debut mis � true
    if(action == DBT) { 
        debut = true;
            del.Allumer(0x01,'A',0);
            _delay_ms(500);
            del.Allumer(0x00,'A',0); 
            _delay_ms(500);
            del.Allumer(0x01,'A',0);
            _delay_ms(500);
            del.Allumer(0x00,'A',0);
    }
	// Tant que debut est true (Donc tant que FIN n'est pas atteint), lire la m�moire et ex�cuter l'action
    while(debut == true) {
        memoire.lecture(adresseParcours, &action);
        _delay_ms(5);
        uart.transmissionUART(action);
        _delay_ms(5);
        adresseParcours++;
        switch(action){   
            case ATT: // Atendre un moment d'�termin� par l'op�rateur
                memoire.lecture(adresseParcours, &op);
                _delay_ms(5);
                uart.transmissionUART(op);
                _delay_ms(5);
                adresseParcours++;
                //Delai de 25ms en fonction de l'operande
                for (int i = 0; i < op; i++)	
                    _delay_ms(25);
                break;

            case DAL: //Allumer la DEL � vert 
                del.Allumer(0x01,'A',0);
                break;

            case DET: //�teindre la DEL
                del.Allumer(0x00,'A',0);
                break;

            case SGO: //Allumer le haut-parleur et jouer la note sp�cifi�e par l'op�rateur
                memoire.lecture(adresseParcours, &op);
                _delay_ms(5);
                uart.transmissionUART(op);
                _delay_ms(5);
                adresseParcours++;
                son.jouerNote(op,1000);
                break;

            case SAR: //Arr�ter le haut-parleur
                son.arretNote();
                break;

            case MAR: //Arr�ter les moteurs
                conducteur.PWM(0, 0, arret);
                break;

            case MAR1: //Arr�ter les moteurs
                conducteur.PWM(0, 0, arret);
                break; 

            case MAV: //Allumer les moteurs et ce d�placer vers l'avant
                memoire.lecture(adresseParcours, &op);
                _delay_ms(5);
                uart.transmissionUART(op);
                _delay_ms(5);
                adresseParcours++;
                op = op/255;
                //FAIRE AVANCER LE ROBOT
                conducteur.PWM(op, op, avant);
                break;

            case MRE: //Allumer les moteurs et ce d�placer vers l'arri�re
                memoire.lecture(adresseParcours, &op);
                _delay_ms(5);
                uart.transmissionUART(op);
                _delay_ms(5);
                adresseParcours++;
                op = op/255;
                //RECULER LE ROBOT
                conducteur.PWM (op, op, arriere);
                break;

            case TRD: //Allumer les moteurs et ce d�placer vers la droite
                conducteur.PWM (0, 255, gauche);
                _delay_ms(1300);
                conducteur.PWM (0, 0, arret);
                break;

            case TRG: //Allumer les moteurs et ce d�placer vers la gauche
                 conducteur.PWM (255, 0, droite);
                _delay_ms(1300);
                conducteur.PWM (0, 0, arret);
                break;

            case DBC: //D�buter la boucle. Prendre en note l'adresse et le nombre de r�p�titions d�sir�es
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

            case FBC: //Si le nombre de r�p�titions effectuer est inf�rieur � celui demand�, revenir � l'adresse du d�but + 1.
					  //Sinon, fin de la boucle.
                if(nbLoop > 0){
                    adresseParcours = adresseTampon;
                    nbLoop--;
                }
                else
                    boucle = false;
                break;

            case FIN: //Fin du programme, mettre debut � false pour sortir du while
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
