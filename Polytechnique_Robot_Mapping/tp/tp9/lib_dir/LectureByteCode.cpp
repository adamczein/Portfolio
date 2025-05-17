/*
 * Nom:LectureByteCode.cpp
 * Auteurs: Dylan Batista-Moniz - 1954776
 *          Jeremy Charland - 1955452
 *
*/
#define F_CPU 8000000
#include "LectureByteCode.h"
#include <util/delay.h>
#include <avr/io.h>

/*************************************************
Nom: ByteCode()
Fonction: Constructeur de la classe ByteCode
**************************************************/
ByteCode::ByteCode(){
    taille_=0;
}

/*************************************************
Nom: LectureByteCode
Fonction: Fonction qui lis le contennu du UART et qui l'écrit sur la mémoire externe
**************************************************/
void ByteCode::LectureByteCode(){
    Memoire24CXXX memoire;
    memoire.init();
    UART uart = UART();
    uart.initialisationUART();
    uint8_t i = 0x00;
    uint8_t tampon1 = uart.lectureUART();
    memoire.ecriture(i,tampon1);
    uint16_t tampon2 = tampon1 << 8;
    taille_ = tampon2;
    tampon1 = uart.lectureUART();
    _delay_ms(5);
    memoire.ecriture(i,tampon1);
    _delay_ms(5);
    tampon2 |= tampon1; 
    
    for(int i =2;i<tampon2;i++){
        uint8_t buffer = uart.lectureUART();
        _delay_ms(5);
        memoire.ecriture(i,buffer);
        _delay_ms(5);
    }
}

/*************************************************
Nom: getTaille
Fonction: Retourne la taille lue par les deux premier octets du fichier
**************************************************/
int ByteCode::getTaille() const{
    return taille_;
}
