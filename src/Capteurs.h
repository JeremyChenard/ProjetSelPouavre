/*
Projet S1 2019
Librairie pour les capteurs des robots.
@auteur Jérémy Chenard
@version 1.0 22/10/2019
*/
#ifndef Capteurs_H_
#define Capteurs_H_

// Includes
#include <arduino.h>
#include <Adafruit_TCS34725.h>

// Defines

// Enumération
enum CouleurCapter
{
    ccRouge,
    ccBleu,
    ccVert,
    ccJaune,
    ccBlancNoir,
    ccOrange,
    ccViolet,
    ccInvalide,

    ccDefaut=ccInvalide,
};

// Fonction
int couleurCapteur();

#endif //LibRobus