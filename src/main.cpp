#include <librobus.h>

//Initialisation des variables globales.
float vitesse_gauche=0;
float vitesse_droite=0;
int i=0;

void Correction()
{
  //Initialisation des variables.
  float erreur=0;
  float pulseGauche = ENCODER_Read(0);
  float pulseDroite = ENCODER_Read(1);
  
  //Trouver la marge d'erreur. 
  erreur=pulseGauche-pulseDroite;

  //S'il y a une marge d'erreur de 5 pulse alors,
  if(erreur>5)
  {
    //Ajuster la valeur du moteur droite.
    vitesse_droite = erreur*0.00001+vitesse_droite;  
    MOTOR_SetSpeed(1, vitesse_droite);
  }
  //Sinon s'il y a une marge d'erreur de -5 pulse alors,
  else if(erreur<-5)
  {
    //Ajuster la valeur du moteur gauche.
    vitesse_gauche = erreur*-0.00001+vitesse_gauche;
    MOTOR_SetSpeed(0, vitesse_gauche);
  }

  //Réinitialiser la valeur d'erreur.
  erreur = 0;
}

void AvanceToutDroit(int distance)
{
  //Réinitialisation des encodeurs.
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  
  //Initialisation des variables.
  int pulse=0;
  int encodeur=0;

  //Calculer le nombre de pulse par cm.
  pulse=134*distance;

  //Mettre une vitesse dans les moteurs.
  vitesse_gauche=0.315;
  vitesse_droite=0.3;
  MOTOR_SetSpeed(0, vitesse_gauche);
  MOTOR_SetSpeed(1, vitesse_droite);

   //Tant que le moteur gauche n'a pas atteint le nombre de pulse voulu. 
  while (encodeur < pulse)
  { 
    delay(50);
    encodeur = ENCODER_Read(0);
    Correction();
  }

  //Éteintre les moteurs.
  vitesse_gauche = 0;
  vitesse_droite = 0;
  MOTOR_SetSpeed(0, vitesse_gauche);
  MOTOR_SetSpeed(1, vitesse_droite);
}

void TournerGauche(int angleG)
{
  //Réinitialisation des encodeurs.
  ENCODER_Reset(0);
  ENCODER_Reset(1);

  int pulseG = 0;
  float encodeurG=0;
  
  //Calculer le nombres de pulse par degré.
  pulseG = (((angleG * 3.14159)/180)*19)*133.67;

  //Éteindre le moteur gauche
  vitesse_gauche=0;
  vitesse_droite=0.3;
  MOTOR_SetSpeed(0, vitesse_gauche);
  MOTOR_SetSpeed(1, vitesse_droite);

  //Tant que le moteur gauche n'a pas atteint le nombre de pulse voulu. 
  while(encodeurG<pulseG)
  {
     encodeurG = ENCODER_Read(1);
  }

  //Éteintre les moteurs.
  vitesse_droite = 0;
  MOTOR_SetSpeed(0, vitesse_gauche);
  MOTOR_SetSpeed(1, vitesse_droite);
}

void TournerDroite(int angleD)
{
  //Réinitialisation des encodeurs.
  ENCODER_Reset(0);
  ENCODER_Reset(1);

  int pulseD=0;
  float encodeurD=0;
  
  //Calculer le nombres de pulse par degré.
  pulseD = (((angleD * 3.14159)/180)*19)*133.67;

  //Éteindre le moteur droit.
  vitesse_gauche=0.3;
  vitesse_droite=0;
  MOTOR_SetSpeed(0, vitesse_gauche);
  MOTOR_SetSpeed(1, vitesse_droite);

  //Tant que le moteur droite n'a pas atteint le nombre de pulse voulu.
  while(encodeurD<pulseD)
  {
     encodeurD = ENCODER_Read(0);
  }

  //Éteintre les moteurs.
  vitesse_gauche=0;
  MOTOR_SetSpeed(0, vitesse_gauche);
  MOTOR_SetSpeed(1, vitesse_droite);
}

void skkkkkrt()
{
  AvanceToutDroit(10);

  TournerGauche(90);
  
  //Réinitialisation des encodeurs.
  ENCODER_Reset(0);
  ENCODER_Reset(1);

  int pulseD=0;
  float encodeurD=0;
  
  //Calculer le nombres de pulse par degré.
  pulseD = (((84 * 3.14159)/180)*19)*133.67;

  //Éteindre le moteur droit.
  vitesse_gauche=-0.3;
  vitesse_droite=0;
  MOTOR_SetSpeed(0, vitesse_gauche);
  MOTOR_SetSpeed(1, vitesse_droite);

  //Tant que le moteur droite n'a pas atteint le nombre de pulse voulu.
  while(encodeurD<pulseD)
  {
     encodeurD = ENCODER_Read(0) * -1;
  }

  //Éteintre les moteurs.
  vitesse_gauche = 0;
  MOTOR_SetSpeed(0, vitesse_gauche);
  MOTOR_SetSpeed(1, vitesse_droite);

  AvanceToutDroit(29);
}

void setup()
{
  //Initialiser la circuit imprimé.
  BoardInit();
  delay(10);
}

void loop() 
{
  if(i!=1)
  {
    AvanceToutDroit(225);
    TournerGauche(90);

    AvanceToutDroit(80);
    TournerDroite(90);

    AvanceToutDroit(25);
    TournerDroite(90);

    AvanceToutDroit(30);
    TournerGauche(95);

    AvanceToutDroit(85);
    TournerDroite(90);

    AvanceToutDroit(30);
    TournerGauche(90);

    AvanceToutDroit(100);

    //***********************BALLON***********************//
    //Virage
    skkkkkrt();
    TournerDroite(3);
    AvanceToutDroit(215);
    i = 1;
  }
 }