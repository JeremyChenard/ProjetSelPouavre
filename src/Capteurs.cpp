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

const double tensionADistance[15][15] =
{
  {2.21, 10}, 
  {1.56, 15},
  {1.25, 20},
  {1.02, 25},
  {0.87, 30},
  {0.75, 35},
  {0.68, 40},
  {0.60, 45},
  {0.55, 50},
  {0.51, 55},
  {0.49, 60},
  {0.44, 65},
  {0.43, 70},
  {0.41, 75},
  {0.39, 80},
};

int capteurCouleur()
{

  // Initialisation avec un temps de 700ms et gain de 1.
  Adafruit_TCS34725 CapteurCouleur = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

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

double capteurDistance(int capteurChoisi)
{
  // Initialisation des valeurs par defaut.
  double valeursCapteur       = ValeurParDefaut;
  double tensionSortieCapteur = ValeurParDefaut;
  double distanceCapteur      = ValeurParDefaut;
  int iIncrementation         = ValeurParDefaut;

  valeursCapteur = analogRead(capteurChoisi);

  // Convertion valeur analogue (0 à 1023) en tension (0 à 5V)
  tensionSortieCapteur = valeursCapteur * (5.0 / 1023.0 );

  /*
  //Valeur distance théorique. Fonction exponentielle.
  distanceCapteur = log((tensionSortieCapteur - 0.35) / 4.23) / log(0.93);
  */

  //Valeur distance pratique. Comparaison avec un tableau de valeur.
  while (distanceCapteur == ValeurParDefaut)
  {
    if (tensionADistance[iIncrementation][0] < tensionSortieCapteur)
    {
      distanceCapteur = tensionADistance[iIncrementation - 1][1];
    }
    // Sinon si la tension est inférieure à 0.39V, dire que la tension est 80cm., 
    else if (iIncrementation > 15)
    {
      distanceCapteur = tensionADistance[14][1];
    }
    else
    {
      // Incrémenter la valeur d'incrémentation.
      iIncrementation ++;
    }  
  }   
  
  Serial.print("Tension dans fonction: ");
  Serial.println(tensionSortieCapteur);
  Serial.print("Distance: ");
  Serial.println(distanceCapteur);
  Serial.println(valeursCapteur);
  
  return distanceCapteur;
}