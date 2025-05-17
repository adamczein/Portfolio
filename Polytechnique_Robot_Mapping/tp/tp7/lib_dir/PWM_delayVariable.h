/*
 * Fichier: PWM_delayVariable.h
 * Auteurs: Mohand Allache (1962202) et Azhar AKINOTCHO (1871583)
 * Date: 25 janvier 2019
 * Description: PWM & delay par variable
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#define marche 0x01
#define arret 0x00

void delay_ms_Variable(int delay);

void PWM(int a, int b, int c);
