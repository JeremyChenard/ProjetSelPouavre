#include "Capteurs.h"


const String Couleur[] =
{
    "Rouge",
    "Bleu",
    "Vert",
    "Jaune",
    "Blanc/Noir",
    "Violet",
    "Orange",
    "Violet",
    "Invalide",
};

int couleurCapteur()
{

  // Initialisation avec un temps de 700ms et gain de 1.
  Adafruit_TCS34725 CapteurCouleur = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

  // Initialisation des valeurs par defaut.
  uint16_t iRouge = 0;
  uint16_t iVert  = 0;
  uint16_t iBleu  = 0; 
  uint16_t iClear = 0;

  // Coordonéée x,y et z sur le plan des couleurs.
  float X = 0;
  float Y = 0;
  float Z = 0;
  float x = 0;
  float y = 0;

  // Couleur détecter.
  int iCouleur = ccDefaut;

  // Vérification si le capteur est connecté.
  if (CapteurCouleur.begin()) 
  {
    Serial.println("Capteur trouve");
  } 
  else 
  {
    Serial.println("Aucun capteur trouve... Verifiez la connection");
    while (1);
  }
  
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
        Serial.println("=======================");
        Serial.println("BLANC/NOIR");
        Serial.println("=======================");

        iCouleur = ccBlancNoir;
      }
      else if(y>0.4 && y<=0.9)
      {
        Serial.println("=======================");
        Serial.println("VERT");
        Serial.println("=======================");
        
        iCouleur = ccVert;
      }
      else if(x<0.3 && y<=0.4 && y>=0.1)
      {
        Serial.println("=======================");
        Serial.println("BLEU");
        Serial.println("=======================");
        
        iCouleur = ccBleu;
      }
      else if(x<0.2 && y<0.1)
      {
        Serial.println("=======================");
        Serial.println("BLEU");
        Serial.println("=======================");

        iCouleur = ccBleu;
      }
      else if(x>=0.3 && y<0.3 && y>=0.2)
      {
        Serial.println("=======================");
        Serial.println("ROUGE");
        Serial.println("=======================");
        
        iCouleur = ccRouge;
      }
      else 
      {
        Serial.println("=======================");
        Serial.println("VIOLET");
        Serial.println("=======================");
        
        iCouleur = ccViolet;
      }
    }
    else if (x>=0.4 && x<0.9)
    {
      if(x<0.5 && y>=0.3 && y<0.6)
      {
        Serial.println("=======================");
        Serial.println("JAUNE");
        Serial.println("=======================");
        
        iCouleur = ccJaune;
      }
      else if(x<0.6 && x>=0.5 && y>=0.4 && y<0.6)
      {
        Serial.println("=======================");
        Serial.println("ORANGE");
        Serial.println("=======================");
        
        iCouleur = ccOrange;
      }  
      else if(x<0.5 && y>=0.6)
      {
        Serial.println("=======================");
        Serial.println("VERT");
        Serial.println("=======================");
        
        iCouleur = ccVert;
      }          
      else
      {
        Serial.println("=======================");
        Serial.println("ROUGE");
        Serial.println("=======================");

        iCouleur = ccRouge;
      }      
    }
    else 
    {
      Serial.println("=======================");
      Serial.println("Erreur");
      Serial.println("=======================");
      
      iCouleur = ccInvalide;
    }
    
    return iCouleur;   
}