/*
Projet S1 2019
Librairie pour les capteurs des robots.
@auteur Jérémy Chenard
@version 1.0 22/10/2019
*/
#ifndef CapteurCouleur_H_
#define CapteurCouleur_H_

// Includes
#include <arduino.h>
#include <Adafruit_TCS34725.h>

void printColor (int);

// Enumération
enum CouleurCapteur
{
    ccRouge,
    ccVert,
    ccBleu,
    ccJaune,
    ccBlancNoir,
    ccOrange,
    ccViolet,
    ccInvalide,
    ccDefaut=ccInvalide,
};

const String Couleur[] =
{
    "Rouge",
    "Vert",
    "Bleu",
    "Jaune",
    "Blanc/Noir",
    "Violet",
    "Orange",
    "Violet",
    "Invalide",
};

// Initialisation des valeurs par defaut.
uint16_t iRouge = ValeurParDefaut;
uint16_t iVert  = ValeurParDefaut;
uint16_t iBleu  = ValeurParDefaut; 
uint16_t iClear = ValeurParDefaut;

// Coordonéée x,y et z sur le plan des couleurs.
float X = ValeurParDefaut;
float Y = ValeurParDefaut;
float Z = ValeurParDefaut;
float x = ValeurParDefaut;
float y = ValeurParDefaut;

Adafruit_TCS34725 CapteurCouleurInit()
{
  Adafruit_TCS34725 CapteurCouleur = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
  // Vérification si le capteur est connecté.
  while (!CapteurCouleur.begin()) 
  {
    Serial.println("Aucun capteur trouve... Verifiez la connection");
    delay(5000);
  }
  return CapteurCouleur;
} 

void resetValeurCouleur ()
{
  iRouge = ValeurParDefaut;
  iVert  = ValeurParDefaut;
  iBleu  = ValeurParDefaut; 
  iClear = ValeurParDefaut;
  X = ValeurParDefaut;
  Y = ValeurParDefaut;
  Z = ValeurParDefaut;
  x = ValeurParDefaut;
  y = ValeurParDefaut;
} 

// Fonction
int getColor()
{
    Adafruit_TCS34725 CapteurCouleur = CapteurCouleurInit();
    resetValeurCouleur();
    CapteurCouleur.getRawData(&iRouge, &iVert, &iBleu, &iClear);

    // Convertion des valeurs RGB en valeur x et y. 
    X = (-0.14282*iRouge) + (1.54924*iVert) + (-0.95641*iBleu);
    Y = (-0.32466*iRouge) + (1.57837*iVert) + (-0.73191*iBleu);
    Z = (-0.68202*iRouge) + (0.77073*iVert) + (0.56332*iBleu);   
    x = X/(X+Y+Z);
    y = Y/(X+Y+Z);

    // Sélection des couleurs.
    if(x>=0 && x<0.4)
    {
        if(x>=0.3 && y>=0.3 && y<=0.4)
        {
            printColor(ccBlancNoir);
            return ccBlancNoir;
        }
        if(y>0.4 && y<=0.9)
        {
            printColor(ccVert);
            return ccVert;
        }
        if(x<0.3 && y<=0.4 && y>=0.1)
        {
            printColor(ccBleu);
            return ccBleu;
        }
        if(x<0.2 && y<0.1)
        {
            printColor(ccBleu);
            return ccBleu;
        }
        if(x>=0.3 && y<0.3 && y>=0.2)
        {
            printColor(ccRouge);
            return ccRouge;
        }
        printColor(ccViolet);
        return ccViolet;
    }

    if (x>=0.4 && x<0.9)
    {
        if(x<0.5 && y>=0.3 && y<0.6)
        {
            printColor(ccJaune);
            return ccJaune;
        }
        if(x<0.6 && x>=0.5 && y>=0.4 && y<0.6)
        {
            printColor(ccOrange);
            return ccOrange;
        }  
        if(x<0.5 && y>=0.6)
        {
            printColor(ccVert);
            return ccVert;
        }          
        printColor(ccRouge);
        return ccRouge;
    }

    printColor(ccInvalide);
    return ccInvalide;
}

void printColor(int color) 
{
    Serial.println("=======================");
    Serial.println(Couleur[color]);
    Serial.println("=======================");
} 

#endif //LibRobus