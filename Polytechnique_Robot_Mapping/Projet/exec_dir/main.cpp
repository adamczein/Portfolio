/*
 * Nom:main.cpp
 * Auteurs: Akinotcho Azhar  - 1871583
 *          Allache Mohand - 1962202
 *          Batista Dylan - 1954776          
*/
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include "../lib_dir/can.h"
#include "../lib_dir/Conducteur.h"
#include "../lib_dir/Sonorite.h"
#include "../lib_dir/Minuterie.h"
#include "../lib_dir/Bouton.h"

#define IR1 0 //1
#define IR2 1 //2
#define IR3 2 //0x04
#define IR4 3 //0x08
#define IR5 4 //0x10

#define ETEINT 0X00

#define CAPTEUR1 0x01
#define CAPTEUR2 0x02
#define CAPTEUR3 0x04
#define CAPTEUR4 0x08
#define CAPTEUR5 0x10

//projet
can can;
//DEL del;
Conducteur conducteur;
Sonorite son;
Minuterie minuterie;
Bouton bouton;

//Compteur de la section 3_2
uint8_t compteur3_2 = 0;

//booleen permettant de debuter et d'arreter un parcours
bool detectionSection1_1 = true;
bool detectionSection1_3 = true;
bool detectionSection2 = true;
bool detectionSection3_1 = true;
bool detectionSection3_2 = true;
bool detectionSection3_3 = true;
bool detectionSection4 = true;
bool ligneGauche = false;
bool compteurGO = false;
bool suivre3_2 = true;

//bool detectionSection4 = true;
bool tourne = true;

// Volatiles selection de la section
volatile bool parcoursGO = true;
volatile bool boolParcours1 = false;
volatile bool boolParcours3 = false;
volatile uint8_t compteurBouton = 0;
// Volatiles pour minuterie
volatile uint8_t compteurMinuteries = 150;
volatile bool compteurEnd = false;

//ISR de minuterie
ISR(TIMER2_COMPA_vect)
{
    minuterie.setExpiree();
    if (minuterie.getExpiree() && (compteurMinuteries != 0))
    {
        minuterie.partirMinuterie(250);
        compteurMinuteries--;
    }
    else
    {
        compteurMinuteries = 150;
        compteurEnd = true;
    }
}

//ISR de bouton
ISR(INT0_vect)
{
    if (PIND & 0x04)
    {
        _delay_ms(30);
        if (PIND & 0x04)
        {
            son.notePWM(45, 10);
            _delay_ms(50);
            son.arretNote();
            minuterie.byeMinuterie();
            if (parcoursGO && (compteurBouton == 4))
            {
                minuterie.partirMinuterie(250);
                compteurBouton = 1;
            }
            else if (parcoursGO && (compteurBouton != 4))
            {
                minuterie.partirMinuterie(250);
                compteurBouton++;
            }
            else if (boolParcours1 && (compteurBouton == 9))
            {
                minuterie.partirMinuterie(250);
                compteurBouton = 1;
            }
            else if (boolParcours1 && (compteurBouton != 9))
            {
                minuterie.partirMinuterie(250);
                compteurBouton++;
            }
            else if (boolParcours3 && (compteurBouton == 1))
            {
                compteurBouton = 0;
            }
            else if (boolParcours3 && (compteurBouton == 0))
            {
                compteurBouton++;
            }
        }
    }
    EIFR |= (1 << INTF0);
}

/****************************************************************************
 * Fonction:    initialisationPort()
 * Description: Elle ajuste bien tous les ports utilisés afin de
 *              bien manipulé notre robot. Une partie du port D est utilisée 
 *              en mode entré, l'autre partie en mode sortie ,ce qui nous 
 *              permet de manipuler le bouton poussoir en meme temps que les
 *              roues.             
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void initialisationPort()
{
    DDRA = 0X00;
    DDRB = 0xFF;
    DDRC = 0XFF;
    DDRD = 0xF0;
}

/****************************************************************************
 * Fonction:    getCapteur1()
 * Description: Elle retourne un true si le capteur 1 detecte du noir
 *              et un false dans le cas contraire .
 * Paramètres:  Aucun
 * Retour:  bool
 ****************************************************************************/
bool getCapteur1()
{
    if (can.lecture(IR1) < 700)
        return true;
    else
        return false;
}

/****************************************************************************
 * Fonction:    getCapteur2()
 * Description: Elle retourne un true si le capteur 2 detecte du noir
 *              et un false dans le cas contraire .
 * Paramètres:  Aucun
 * Retour:      bool
 ****************************************************************************/
bool getCapteur2()
{
    if (can.lecture(IR2) < 970)
        return true;
    else
        return false;
}

/****************************************************************************
 * Fonction:    getCapteur3()
 * Description: Elle retourne un true si le capteur 3 detecte du noir
 *              et un false dans le cas contraire .
 * Paramètres:  Aucun
 * Retour:      bool
 ****************************************************************************/
bool getCapteur3()
{
    if (can.lecture(IR3) < 850)
        return true;
    else
        return false;
}

/****************************************************************************
 * Fonction:    getCapteur4()
 * Description: Elle retourne un true si le capteur 4 detecte du noir
 *              et un false dans le cas contraire .
 * Paramètres:  Aucun
 * Retour:      bool
 ****************************************************************************/
bool getCapteur4()
{
    if (can.lecture(IR4) < 850)
        return true;
    else
        return false;
}

/****************************************************************************
 * Fonction:    getCapteur5()
 * Description: Elle retourne un true si le capteur 5 detecte du noir
 *              et un false dans le cas contraire .
 * Paramètres:  Aucun
 * Retour:      bool
 ****************************************************************************/
bool getCapteur5()
{
    if (can.lecture(IR5) < 800)
        return true;
    else
        return false;
}

/****************************************************************************
 * Fonction:    detectionCapteur()
 * Description: La detection de capteur nous permet de trouver le capteur et 
 *              d'allumer la del qui lui correspond .
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void detectionCapteur()
{
    if (getCapteur1())
    {
        PORTC = CAPTEUR1;
    }
    if (!getCapteur1())
    {
        PORTC = ETEINT;
    }

    if (getCapteur2())
    {
        PORTC = CAPTEUR2;
    }
    if (!getCapteur2())
    {
        PORTC = ETEINT;
    }
    if (getCapteur3())
    {
        PORTC = CAPTEUR3;
    }
    if (!getCapteur3())
    {
        PORTC = ETEINT;
    }
    if (getCapteur4())
    {
        PORTC = CAPTEUR4;
    }
    if (!getCapteur4())
    {
        PORTC = ETEINT;
    }
    if (getCapteur5())
    {
        PORTC = CAPTEUR5;
    }
    if (!getCapteur5())
    {
        PORTC = ETEINT;
    }
}

/****************************************************************************
 * Fonction:    rotation90()
 * Description: Elle nous permet de faire une rotation de 90 degré frolant la 
 *              perfection. En effet, elle fait avancer le robot pendant un 
 *              court delai , puis le fait tourner jusqu'à ce qu'il detecte le 
 *              capteur du milieu. Cependant , il est utilisé uniquement pour 
 *              la rotation  à gauche dans le coin après le parcours 4. 
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void rotation90()
{
    bool trouverLigne = true;
    conducteur.PWM(140, 140, avant);
    _delay_ms(900);
    conducteur.PWM(130, 0, avant);
    _delay_ms(300);
    while (trouverLigne)
    {
        conducteur.PWM(110, 0, avant);
        if (!getCapteur1() && !getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5())
        {
            trouverLigne = false;
        }
    }
    conducteur.PWM(0, 0, arret);
    _delay_ms(500);
}

/****************************************************************************
 * Fonction:    rotation91()
 * Description: Elle nous permet de faire une rotation de 90 degré frolant la 
 *              perfection. En effet, elle fait avancer le robot pendant un 
 *              court delai , puis le fait tourner jusqu'à ce qu'il detecte le 
 *              capteur du milieu.
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void rotation91()
{
    bool trouverLigne = true;
    conducteur.PWM(140, 140, avant);
    _delay_ms(900);
    while (trouverLigne)
    {
        conducteur.PWM(120, 0, avant);
        if (!getCapteur1() && !getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5())
        {
            trouverLigne = false;
        }
    }
    conducteur.PWM(0, 0, arret);
    _delay_ms(500);
}

/****************************************************************************
 * Fonction:    rotation12()
 * Description: Elle nous permet de faire une tourner le robot jusqu'à ce 
 *              qu'il détecte le capteur du milieu. Elle est utilisée 
 *              uniquement dans le parcours 1, au niveau des points.
 *             
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void rotation12()
{
    bool trouverLigne = true;
    while (trouverLigne)
    {
        conducteur.PWM(120, 0, avant);
        if (!getCapteur1() && !getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5())
        {
            trouverLigne = false;
        }
    }
    conducteur.PWM(0, 0, arret);
    _delay_ms(500);
}

/****************************************************************************
 * Fonction:    suivreLigneSection1_1()
 * Description: Elle nous permet de faire suivre la ligne commencant a la 
 *              section 1 , et s'arretant au niveau du segment  S2
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection1_1()
{
    if (!getCapteur1() && !getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5()) // C3 : DROIT DEVANT
    {
        conducteur.PWM(120, 120, avant);
    }
    else if (!getCapteur1() && getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5()) // C2 : TOURNER DROITE +
    {
        conducteur.PWM(120, 90, avant);
    }
    /*else if (getCapteur1() && !getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5()) // C1 : TOURNER DROITE ++ ?????POURQUOI CE CAS???????
    {
        conducteur.PWM(120, 90, avant);
    }*/
    else if (!getCapteur1() && getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5()) //  C2 - C3 : TOURNER DROITE
    {
        conducteur.PWM(80, 110, avant);
    }
    else if (!getCapteur1() && !getCapteur2() && !getCapteur3() && getCapteur4() && !getCapteur5()) // C4 : TOURNER GAUCHE +
    {
        conducteur.PWM(90, 120, avant);
    }
    else if (!getCapteur1() && !getCapteur2() && getCapteur3() && getCapteur4() && !getCapteur5()) // C3 - C4 : TOURNER GAUCHE
    {
        conducteur.PWM(80, 110, avant);
    }
    else if (getCapteur1() && getCapteur2() && getCapteur3() && getCapteur4() && getCapteur5())
    {
        conducteur.PWM(0, 0, arret);
        detectionSection1_1 = false;
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection1_2Point1()
 * Description: Elle nous permet de  mener notre robot jusqu'au point 1, tout
 *              en se positionnant son centre de gravité sur ce dernier , en 
 *              faisant ses rotations de 90 degre et en jouant un son grave. 
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection1_2Point1()
{
    bool suivre = true;
    while (suivre)
    {

        conducteur.PWM(0, 0, arret);
        _delay_ms(1000);
        conducteur.PWM(140, 150, avant);
        _delay_ms(2300);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(150, 0, avant);
        _delay_ms(1600);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(140, 150, avant);
        _delay_ms(2000);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(150, 160, avant);
        _delay_ms(1500);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        rotation12();
        suivre = false;
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection1_2Point2()
 * Description: Elle nous permet de  mener notre robot jusqu'au point 2, tout
 *              en se positionnant son centre de gravité sur ce dernier , en 
 *              faisant ses rotations de 90 degre et en jouant un son grave. 
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection1_2Point2()
{
    bool suivre = true;
    while (suivre)
    {

        conducteur.PWM(0, 0, arret);
        _delay_ms(1000);
        conducteur.PWM(140, 150, avant);
        _delay_ms(2100);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(150, 0, avant);
        _delay_ms(1600);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(140, 150, avant);
        _delay_ms(1300);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(150, 160, avant);
        _delay_ms(1100);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        rotation12();
        suivre = false;
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection1_2Point3()
 * Description: Elle nous permet de  mener notre robot jusqu'au point 3, tout
 *              en se positionnant son centre de gravité sur ce dernier , en 
 *              faisant ses rotations de 90 degre et en jouant un son grave. 
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection1_2Point3()
{
    bool suivre = true;
    while (suivre)
    {

        conducteur.PWM(0, 0, arret);
        _delay_ms(1000);
        conducteur.PWM(140, 150, avant);
        _delay_ms(2100);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(150, 0, avant);
        _delay_ms(1600);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(140, 150, avant);
        _delay_ms(800);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(150, 160, avant);
        _delay_ms(750);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        rotation12();
        suivre = false;
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection1_2Point4()
 * Description: Elle nous permet de  mener notre robot jusqu'au point 4, tout
 *              en se positionnant son centre de gravité sur ce dernier , en 
 *              faisant ses rotations de 90 degre et en jouant un son grave. 
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection1_2Point4()
{
    bool suivre = true;
    while (suivre)
    {

        conducteur.PWM(0, 0, arret);
        _delay_ms(1000);
        conducteur.PWM(140, 150, avant);
        _delay_ms(1550);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(150, 0, avant);
        _delay_ms(1600);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(140, 150, avant);
        _delay_ms(2000);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(140, 160, avant);
        _delay_ms(1500);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        rotation12();
        suivre = false;
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection1_2Point5()
 * Description: Elle nous permet de  mener notre robot jusqu'au point 5, tout
 *              en se positionnant son centre de gravité sur ce dernier , en 
 *              faisant ses rotations de 90 degre et en jouant un son grave. 
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection1_2Point5()
{
    bool suivre = true;
    while (suivre)
    {

        conducteur.PWM(0, 0, arret);
        _delay_ms(1000);
        conducteur.PWM(140, 150, avant);
        _delay_ms(1700);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(150, 0, avant);
        _delay_ms(1600);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(140, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(160, 140, avant);
        _delay_ms(1000);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        rotation12();
        suivre = false;
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection1_2Point6()
 * Description: Elle nous permet de  mener notre robot jusqu'au point 6, tout
 *              en se positionnant son centre de gravité sur ce dernier , en 
 *              faisant ses rotations de 90 degre et en jouant un son grave. 
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection1_2Point6()
{
    bool suivre = true;
    while (suivre)
    {

        conducteur.PWM(0, 0, arret);
        _delay_ms(1000);
        conducteur.PWM(140, 150, avant);
        _delay_ms(1650);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(150, 0, avant);
        _delay_ms(1600);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(140, 150, avant);
        _delay_ms(700);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(150, 120, avant);
        _delay_ms(1500);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        rotation12();
        suivre = false;
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection1_2Point7()
 * Description: Elle nous permet de  mener notre robot jusqu'au point 7, tout
 *              en se positionnant son centre de gravité sur ce dernier , en 
 *              faisant ses rotations de 90 degre et en jouant un son grave. 
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection1_2Point7()
{
    bool suivre = true;
    while (suivre)
    {

        conducteur.PWM(0, 0, arret);
        _delay_ms(1000);
        conducteur.PWM(140, 150, avant);
        _delay_ms(900);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(150, 0, avant);
        _delay_ms(1450);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(150, 150, avant);
        _delay_ms(2000);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(160, 150, avant);
        _delay_ms(2500);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        rotation12();
        suivre = false;
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection1_2Point8()
 * Description: Elle nous permet de  mener notre robot jusqu'au point 8, tout
 *              en se positionnant son centre de gravité sur ce dernier , en 
 *              faisant ses rotations de 90 degre et en jouant un son grave. 
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection1_2Point8()
{
    bool suivre = true;
    while (suivre)
    {

        conducteur.PWM(0, 0, arret);
        _delay_ms(1000);
        conducteur.PWM(140, 150, avant);
        _delay_ms(900);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(150, 0, avant);
        _delay_ms(1600);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(142, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(160, 130, avant);
        _delay_ms(2400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        rotation12();
        suivre = false;
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection1_2Point9()
 * Description: Elle nous permet de  mener notre robot jusqu'au point 9, tout
 *              en se positionnant son centre de gravité sur ce dernier , en 
 *              faisant ses rotations de 90 degre et en jouant un son grave. 
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection1_2Point9()
{
    bool suivre = true;
    while (suivre)
    {

        conducteur.PWM(0, 0, arret);
        _delay_ms(1000);
        conducteur.PWM(140, 150, avant);
        _delay_ms(900);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(150, 0, avant);
        _delay_ms(1600);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(142, 150, avant);
        _delay_ms(800);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(0, 150, avant);
        _delay_ms(1400);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        son.notePWM(45, 30);
        _delay_ms(3000);
        son.arretNote();
        conducteur.PWM(140, 150, avant);
        _delay_ms(1500);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(150, 0, avant);
        _delay_ms(1500);
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        conducteur.PWM(140, 150, avant);
        _delay_ms(1500);
        rotation12();
        suivre = false;
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection1_2Case()
 * Description: Elle nous permet d'aller a un point précis du parcours 1.
 * Paramètres:  (int) point  
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection1_2Case(int point)
{
    switch (point)
    {
    case 1:
        suivreLigneSection1_2Point1();
        break;
    case 2:
        suivreLigneSection1_2Point2();
        break;
    case 3:
        suivreLigneSection1_2Point3();
        break;
    case 4:
        suivreLigneSection1_2Point4();
        break;
    case 5:
        suivreLigneSection1_2Point5();
        break;
    case 6:
        suivreLigneSection1_2Point6();
        break;
    case 7:
        suivreLigneSection1_2Point7();
        break;
    case 8:
        suivreLigneSection1_2Point8();
        break;
    case 9:
        suivreLigneSection1_2Point9();
        break;
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection1_3()
 * Description: Elle nous permet de  suivre la ligne partant du segment 
 *              S3 et s'arretant au coin C2.
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection1_3()
{
    if (!getCapteur1() && !getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5()) // C3 : DROIT DEVANT
    {
        conducteur.PWM(130, 130, avant);
    }
    else if (!getCapteur1() && getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5()) // C2 : TOURNER DROITE +
    {
        conducteur.PWM(130, 90, avant);
    }
    else if (getCapteur1() && !getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5()) // C1 : TOURNER DROITE ++ ?????POURQUOI CE CAS???????
    {
        conducteur.PWM(130, 90, avant);
    }
    else if (!getCapteur1() && getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5()) //  C2 - C3 : TOURNER DROITE
    {
        conducteur.PWM(130, 90, avant);
    }
    else if (!getCapteur1() && !getCapteur2() && !getCapteur3() && getCapteur4() && !getCapteur5()) // C4 : TOURNER GAUCHE +
    {
        conducteur.PWM(90, 130, avant);
    }
    else if (!getCapteur1() && !getCapteur2() && getCapteur3() && getCapteur4() && !getCapteur5()) // C3 - C4 : TOURNER GAUCHE
    {
        conducteur.PWM(80, 130, avant);
    }
    else if (getCapteur1() && getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5())
    {
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        detectionSection1_3 = false;
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection2()
 * Description: Elle nous permet de  suivre la ligne partant du coin 
 *              C2 et s'arretant au coin C3. Les vitesses du moteur du robots
 *              son considerablement réduites à l'entrée des courbes.
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection2()
{
    if (!getCapteur1() && !getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5())
    {

        conducteur.PWM(130, 130, avant);
    }
    else if (!getCapteur1() && getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5())
    {

        conducteur.PWM(110, 70, avant); //110 70
    }
    else if (!getCapteur1() && !getCapteur2() && !getCapteur3() && getCapteur4() && !getCapteur5())
    {

        conducteur.PWM(70, 110, avant); //70,110
    }
    else if (getCapteur1() && !getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5())
    {

        conducteur.PWM(70, 15, avant);
    }
    else if (!getCapteur1() && !getCapteur2() && getCapteur3() && getCapteur4() && getCapteur5())
    {

        bool trouverLigne = true;
        conducteur.PWM(130, 130, avant);
        _delay_ms(600);
        while (trouverLigne)
        {
            conducteur.PWM(0, 100, avant);
            if (!getCapteur1() && !getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5())
            {
                trouverLigne = false;
            }
        }
        conducteur.PWM(0, 0, arret);
    }
    else if (getCapteur1() && getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5())
    {
        conducteur.PWM(0, 0, arret);
        detectionSection2 = false;
        
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection3_1()
 * Description: Elle nous permet de  suivre la ligne partant du coin C3 
 *               et s'arretant au segment S5.
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection3_1() 
{

    if (!getCapteur1() && !getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5()) // C3 : DROIT DEVANT
    {
        conducteur.PWM(150, 150, avant);
    }
    else if (!getCapteur1() && getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5()) // C2 : TOURNER DROITE +
    {
        conducteur.PWM(150, 100, avant);
    }
    else if (getCapteur1() && !getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5()) // C1 : TOURNER DROITE ++ ?????POURQUOI CE CAS???????
    {
        conducteur.PWM(150, 90, avant);
    }
    else if (!getCapteur1() && getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5()) //  C2 - C3 : TOURNER DROITE
    {
        conducteur.PWM(150, 110, avant);
    }
    else if (!getCapteur1() && !getCapteur2() && !getCapteur3() && getCapteur4() && !getCapteur5()) // C4 : TOURNER GAUCHE +
    {
        conducteur.PWM(100, 150, avant);
    }
    else if (!getCapteur1() && !getCapteur2() && getCapteur3() && getCapteur4() && !getCapteur5()) // C3 - C4 : TOURNER GAUCHE
    {
        conducteur.PWM(110, 150, avant);
    }
    else if (!getCapteur1() && getCapteur2() && getCapteur3() && getCapteur4() && !getCapteur5()) // C2 - C3 - C4 : TOURNER DROITE ++ ???????????????????????
    {
        conducteur.PWM(110, 60, avant);
    }

    else if (getCapteur1() && getCapteur2() && getCapteur3() && getCapteur4() && getCapteur5()) // C1 - C2 - C3 - C4 - C5 : ARRET
    {
        conducteur.PWM(0, 0, arret);
        detectionSection3_1 = false;
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection3_2()
 * Description: Elle nous permet de  suivre la droite D1, D2, D3, ou D4  
 *              et s'arrete lorsqu'elle ne detecte plus rien. Par suite , 
 *              elle allume la del correspondant à la droite prise.
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection3_2() 
{
    if (getCapteur1() && getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5()) // C1 - C2 - C3 : SEGMENT AU COTE GAUCHE DU ROBOT
    {
        _delay_ms(10);
        if (getCapteur1() && getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5())
        {
            conducteur.PWM(160, 170, avant);
            ligneGauche = true; // LA VARIABLE ligneGauche AGIT COMME UN REPERE INDIQUANT SI LE SEGMENT GAUCHE DU PARCOURS EST AVANT OU APRES LE SEGMENT DROIT
            if (compteurGO)
                compteur3_2 += 2;
        }
    }
    else if (getCapteur1() && getCapteur2() && getCapteur3() && getCapteur4() && !getCapteur5()) // C1 - C2 - C3 - C4 : SEGMENT AU COTE GAUCHE DU ROBOT
    {
        _delay_ms(10);
        if (getCapteur1() && getCapteur2() && getCapteur3() && getCapteur4() && !getCapteur5())
        {
            conducteur.PWM(160, 170, avant);
            ligneGauche = true;
            if (compteurGO)
                compteur3_2 += 2;
        }
    }
    else if (!getCapteur1() && !getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5()) // C3 : RIEN, AVANCER
    {
        _delay_ms(10);
        if (!getCapteur1() && !getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5())
        {
            conducteur.PWM(160, 170, avant);
            if (compteurGO)
                compteur3_2 += 2;
        }
    }

    else if (!getCapteur1() && !getCapteur2() && getCapteur3() && getCapteur4() && getCapteur5()) // C3 - C4 - C5 : SEGMENT AU COTE DROIT DU ROBOT
    {
        _delay_ms(10);
        if (!getCapteur1() && !getCapteur2() && getCapteur3() && getCapteur4() && getCapteur5())
        {
            conducteur.PWM(160, 170, avant);
            ligneGauche = false;
            if (compteurGO)
                compteur3_2 += 2;
        }
    }

    else if (!getCapteur1() && getCapteur2() && getCapteur3() && getCapteur4() && getCapteur5()) // C2 - C3 - C4 - C5 : SEGMENT AU COTE DROIT DU ROBOT
    {
        _delay_ms(10);
        if (!getCapteur1() && getCapteur2() && getCapteur3() && getCapteur4() && getCapteur5())
        {
            conducteur.PWM(160, 170, avant);
            ligneGauche = false;
            if (compteurGO)
                compteur3_2 += 2;
        }
    }
    else if (!getCapteur1() && getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5()) // C2 : TOURNER DROITE
    {
        _delay_ms(10);
        if (!getCapteur1() && getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5())
        {
            conducteur.PWM(160, 80, avant);
            if (compteurGO)
                compteur3_2++;
        }
    }
    else if (!getCapteur1() && !getCapteur2() && !getCapteur3() && getCapteur4() && !getCapteur5()) // C4 : TOURNER GAUCHE
    {
        _delay_ms(10);
        if (!getCapteur1() && !getCapteur2() && !getCapteur3() && getCapteur4() && !getCapteur5())
        {
            conducteur.PWM(80, 170, avant);
            if (compteurGO)
                compteur3_2++;
        }
    }
    else if (getCapteur1() && getCapteur2() && getCapteur3() && getCapteur4() && getCapteur5()) // C1 - C2 -C3 - C4 - C5 : DEBUT MINUTERIE, AVANCER
    {
        _delay_ms(10);
        if (getCapteur1() && getCapteur2() && getCapteur3() && getCapteur4() && getCapteur5())
        {
            conducteur.PWM(160, 170, avant);
            compteurGO = true; // DEBUT DE L'INCREMENTATION DU COMPTEUR
            compteur3_2 += 2;
        }
    }
    else if (!getCapteur1() && !getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5()) // RIEN = ARRET
    {
        _delay_ms(100);
        if ((!getCapteur1() && !getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5())) // SI RIEN
        {
            conducteur.PWM(0, 0, arret); // ARRET DES MOTEUR

            if ((compteur3_2 > 150) && ligneGauche)
                PORTC = CAPTEUR3;

            else if ((compteur3_2 < 150) && ligneGauche)
                PORTC = CAPTEUR4;

            else if ((compteur3_2 > 160) && !ligneGauche)
                PORTC = CAPTEUR1;

            else if ((compteur3_2 < 160) && !ligneGauche)
                PORTC = CAPTEUR2;

            detectionSection3_2 = false;
        }
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection3_3()
 * Description: Elle nous permet de  suivre la ligne partant du point PA  
 *               et s'arretant au coin C4.
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection3_3()
{
    if (!getCapteur1() && !getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5()) // C3 : DROIT DEVANT
    {
        conducteur.PWM(130, 130, avant);
    }
    else if (!getCapteur1() && getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5()) // C2 : TOURNER DROITE +
    {
        conducteur.PWM(130, 90, avant);
    }
    else if (getCapteur1() && !getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5()) // C1 : TOURNER DROITE ++ ?????POURQUOI CE CAS???????
    {
        conducteur.PWM(130, 90, avant);
    }
    else if (!getCapteur1() && getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5()) //  C2 - C3 : TOURNER DROITE
    {
        conducteur.PWM(130, 90, avant);
    }
    else if (!getCapteur1() && !getCapteur2() && !getCapteur3() && getCapteur4() && !getCapteur5()) // C4 : TOURNER GAUCHE +
    {
        conducteur.PWM(90, 130, avant);
    }
    else if (!getCapteur1() && !getCapteur2() && getCapteur3() && getCapteur4() && !getCapteur5()) // C3 - C4 : TOURNER GAUCHE
    {
        conducteur.PWM(80, 130, avant);
    }
    else if (getCapteur1() && getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5())
    {
        conducteur.PWM(0, 0, arret);
        _delay_ms(500);
        detectionSection3_3 = false;
    }
}

/****************************************************************************
 * Fonction:    suivreLigneSection4()
 * Description: Elle nous permet de  suivre la ligne partant du coin C4 
 *               et s'arretant au coin C1. Toute les fois ou le robot 
 *              rencontrera les 5 capteurs a la fois , il emmet une bip bip.
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void suivreLigneSection4()
{
    if (!getCapteur1() && !getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5())
    {
        conducteur.PWM(130, 130, avant);
    }
    else if (!getCapteur1() && getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5())
    {
        conducteur.PWM(130, 90, avant); //150,100
    }
    else if (!getCapteur1() && !getCapteur2() && !getCapteur3() && getCapteur4() && !getCapteur5())
    {
        conducteur.PWM(90, 130, avant);
    }

    else if (getCapteur1() && getCapteur2() && getCapteur3() && getCapteur4() && getCapteur5())
    {
        son.notePWM(45, 1);
        _delay_ms(50);
        son.arretNote();
        _delay_ms(20);
        son.notePWM(45, 1);
        _delay_ms(50);
        son.arretNote();
        _delay_ms(20);

        conducteur.PWM(130, 130, avant);
    }
    else if (getCapteur1() && !getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5())
    {
        conducteur.PWM(90, 130, avant);
    }
    else if (!getCapteur1() && !getCapteur2() && !getCapteur3() && !getCapteur4() && getCapteur5())
    {
        conducteur.PWM(130, 90, avant);
    }
    else if (!getCapteur1() && !getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5())
    {
        conducteur.PWM(130, 130, avant);
    }
    else if (getCapteur1() && getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5())
    {
        conducteur.PWM(0, 0, avant);
        _delay_ms(100);
        while (getCapteur1() && getCapteur2() && getCapteur3() && !getCapteur4() && !getCapteur5())
            detectionSection4 = false;
    }
    else if (getCapteur1() && getCapteur2() && getCapteur3() && getCapteur4() && !getCapteur5())
    {
        conducteur.PWM(0, 0, avant);
        _delay_ms(100);
        while (getCapteur1() && getCapteur2() && getCapteur3() && getCapteur4() && !getCapteur5())
            detectionSection4 = false;
    }
    else if (getCapteur1() && getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5())
    {
        conducteur.PWM(0, 0, avant);
        _delay_ms(100);
        while (getCapteur1() && getCapteur2() && !getCapteur3() && !getCapteur4() && !getCapteur5())
            detectionSection4 = false;
    }
}

/****************************************************************************
 * Fonction:    parcours1_1()
 * Description: Elle nous permet de faire suivreLigneSection1_1 tout en allumant 
 *              les capteurs corespondant . Le booléeen detectectionSection1_1 
 *              devient fausse lorsque suivreLigne1_1 est fini, ce qui lui permet
 *              de sortir de la boucle while .              
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void parcours1_1()
{
    while (detectionSection1_1)
    {
        detectionCapteur();
        suivreLigneSection1_1();
    }
}

/****************************************************************************
 * Fonction:    parcours1_3()
 * Description: Elle nous permet de faire suivreLigneSection1_3 tout en allumant 
 *              les capteurs corespondant . Le booléeen detectectionSection1_3 
 *              devient fausse lorsque suivreLigne1_3 est fini, ce qui lui permet
 *              de sortir de la boucle while .              
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void parcours1_3()
{
    while (detectionSection1_3)
    {
        detectionCapteur();
        suivreLigneSection1_3();
    }
}

/****************************************************************************
 * Fonction:    parcours2()
 * Description: Elle nous permet de faire suivreLigneSection2 tout en allumant 
 *              les capteurs corespondant . Le booléeen detectectionSection2 
 *              devient fausse lorsque suivreLigne2 est fini, ce qui lui permet
 *              de sortir de la boucle while .              
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void parcours2()
{
    while (detectionSection2)
    {
        detectionCapteur();
        suivreLigneSection2();
    }
}

/****************************************************************************
 * Fonction:    parcours3_1()
 * Description: Elle nous permet de faire suivreLigneSection3_1 tout en allumant 
 *              les capteurs corespondant . Le booléeen detectectionSection3_1 
 *              devient fausse lorsque suivreLigne3_1 est fini, ce qui lui permet
 *              de sortir de la boucle while .              
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void parcours3_1()
{
    while (detectionSection3_1)
    {
        detectionCapteur();
        suivreLigneSection3_1();
    }
}

/****************************************************************************
 * Fonction:    parcours3_2()
 * Description: Elle nous permet de faire suivreLigneSection3_2 tout en allumant 
 *              les capteurs corespondant . Le booléeen detectectionSection3_2 
 *              devient fausse lorsque suivreLigne3_2 est fini, ce qui lui permet
 *              de sortir de la boucle while .              
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void parcours3_2()
{
    while (detectionSection3_2)
    {
        detectionCapteur();
        suivreLigneSection3_2();
    }
}

/****************************************************************************
 * Fonction:    parcours3_3()
 * Description: Elle nous permet de faire suivreLigneSection3_3 tout en allumant 
 *              les capteurs corespondant . Le booléeen detectectionSection3_3 
 *              devient fausse lorsque suivreLigne3_3 est fini, ce qui lui permet
 *              de sortir de la boucle while .              
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void parcours3_3()
{
    while (detectionSection3_3)
    {
        detectionCapteur();
        suivreLigneSection3_3();
    }
}

/****************************************************************************
 * Fonction:    parcours4()
 * Description: Elle nous permet de faire suivreLigneSection4 tout en allumant 
 *              les capteurs corespondant . Le booléeen detectectionSection4 
 *              devient fausse lorsque suivreLigne4 est fini, ce qui lui permet
 *              de sortir de la boucle while .              
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void parcours4()
{
    while (detectionSection4)
    {
        detectionCapteur();
        suivreLigneSection4();
    }
}
/****************************************************************************
 * Fonction:    parcours()
 * Description: Elle nous permet de faire tous les parcours successivement 
 *               et de s'arreter quand tous les parcours sont finis.  
 * Paramètres:  (int) debutParcours 
 * Retour:      Aucun
 ****************************************************************************/
void parcours(int debutParcours)
{
    int Compteur = 1;
    int i = debutParcours;
    compteurBouton = 0;
    while (Compteur < 5)
    {

        switch (i)
        {

        case 1:
            parcours1_1();
            while (!compteurEnd)
            {
            };
            _delay_ms(4000);
            suivreLigneSection1_2Case(compteurBouton);
            compteurBouton = 0;
            parcours1_3();
            if (Compteur < 4)
            {
                rotation91();
                boolParcours3 = 1;
            }
            boolParcours1 = 0;
            i++;
            Compteur++;
            break;
        case 2:
            parcours2();
            if (Compteur < 4)
            {
                rotation91();
            }
            i++;
            Compteur++;
            break;
        case 3:
            parcours3_1();
            while (compteurBouton == 0)
            {
            };
            parcours3_2();
            while (compteurBouton == 1)
            {
            };
            parcours3_3();
            compteurBouton = 0;
            if (Compteur < 4)
            {
                rotation91();
                boolParcours1 = 1;
            }
            boolParcours3 = 0;
            i++;
            Compteur++;
            break;
        case 4:
            parcours4();
            i = 1;
            if (Compteur < 4)
            {
                rotation90();
            }
            Compteur++;
            break;
        }
    }
}

/****************************************************************************
 * Fonction:    signalDebut()
 * Description: Elle nous permet de marquer le debut de l'épreuve en allumant
 *              la del correspondand au parcours retenus. 
 *                
 * Paramètres:  (int) debutParcours
 * Retour:      Aucun
 ****************************************************************************/
void signalDebut(int debutParcours)
{
    int i = debutParcours;
    if (i == 1)
    {
        PORTC = CAPTEUR1;
        _delay_ms(3000);
    }
    else if (i == 2)
    {
        PORTC = CAPTEUR2;
        _delay_ms(3000);
    }
    else if (i == 3)
    {
        PORTC = CAPTEUR3;
        _delay_ms(3000);
    }
    else if (i == 4)
    {
        PORTC = CAPTEUR4;
        _delay_ms(3000);
    }
}

/****************************************************************************
 * Fonction:    signalFin()
 * Description: Elle nous permet de marquer la fin de l'épreuve en faisant un 
 *              son aigu.                
 * Paramètres:  Aucun
 * Retour:      Aucun
 ****************************************************************************/
void signalFin()
{
    minuterie.byeMinuterie();
    son.notePWM(45, 1);
    _delay_ms(2000);
    son.arretNote();
}

int main()
{

    initialisationPort();
    bouton.initialisationIntExterne();

    while (!compteurEnd)
    {
    };
    parcoursGO = false;
    if ((compteurBouton == 1) || (compteurBouton > 3))
        boolParcours1 = true;
    else
        boolParcours3 = true;
    signalDebut(compteurBouton);

    parcours(compteurBouton);
    signalFin();
}
