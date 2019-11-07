/*
Projet S1 2019
Librairie pour les capteurs des robots.
@auteur Jérémy Chenard
@version 1.0 22/10/2019
*/
#ifndef CapteurDistance_H_
#define CapteurDistance_H_

#include <arduino.h>
#include <math.h>

// Defines
#define PINDISTANCEHAUT 1
#define PINDISTANCEBAS 0

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

double getDistance(int capteurChoisi)
{
  // Initialisation des valeurs par defaut.
  double valeursCapteur       = ValeurParDefaut;
  double tensionSortieCapteur = ValeurParDefaut;
  double distanceCapteur      = ValeurParDefaut;
  int iIncrementation         = ValeurParDefaut;

  //valeursCapteur = analogRead(capteurChoisi);
  valeursCapteur = ROBUS_ReadIR(capteurChoisi);

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
  return distanceCapteur;
}
#endif 