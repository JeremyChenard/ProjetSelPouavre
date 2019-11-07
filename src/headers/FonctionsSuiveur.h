/*
Projet S1 2019
Librairie pour le suiveur de ligne.
@auteur Pedro Maria Scoccimarro
@version 1.0 22/10/2019
*/
#include <Arduino.h>
#include <headers/Movements.h>

#define PIN_SUIVEUR A7  //À CHANGER POUR LA BONNE PIN

int input_value_AX;

double AnalSuiveurLigne = 0;
double TensionSuiveurLigne = 0;

float tensionSuiveurLigne[8] = 
{
  0,
  0.71,
  1.42,
  2.12,
  2.85,
  3.55,
  4.26,
  4.97,
};

// MAP

//ROUGE             VERT
//          B
//        CENTRE
//          A
//JAUNE             BLEU

void aucunCapteur()
{
    // Cas: les trois capteurs sont sur la ligne ou sur une couleur
    //tourner à droite/gauche ou trouver balle
    decelerate();
    fermerPinces(25);
    //arrêt des moteurs
}

void capteurG(){
    // Cas: Juste le capteur gauche est en dehors de la ligne
    //tourner à droite
    turn(1, 1);
    //arrêt des moteurs
}

void capteurC()
{
    // Cas: ?? impossible
   forward(TensionSuiveurLigne, tensionSuiveurLigne[2], tensionSuiveurLigne[1]);
}

void capteurD(){
    // Cas: Juste le capteur droit est en dehors de la ligne
    //tourner à gauche
    turn(0, 1);
    //arrêt des moteurs
}

void capteurG_C(){
    // Cas: Juste le capteur droit est sur la ligne
    //tourner à droite
    turn(1, 1);
    //arrêt des moteurs
}

void capteurG_D(){
    // Cas: "centrer" sur la ligne
    //avancer tout droit    
    //while (TensionSuiveurLigne <= tensionSuiveurLigne[5] && TensionSuiveurLigne > tensionSuiveurLigne[4])
    //{
        forward(TensionSuiveurLigne, tensionSuiveurLigne[5], tensionSuiveurLigne[4]);
        
        /*
        AnalSuiveurLigne = analogRead(PIN_SUIVEUR);

        // Convertion valeur analogue (0 à 1023.0) en tension (0 à 5V)
        TensionSuiveurLigne = AnalSuiveurLigne * (5.0 / 1023.0);
        */
    //}

    /*
    while(input_value_AX > 638 && input_value_AX < 764){
        //fonction avancer tout droit
        forward();
        input_value_AX = analogRead(PIN_SUIVEUR);
    }*/
    //arrêt des moteurs
}

void capteurC_D(){
    // Cas: Juste le capteur gauche est sur la ligne
    //tourner à gauche
    turn(0, 1);
    //arrêt des moteurs
}

void capteurG_C_D(){
    // Cas: Les trois capteurs sont en dehors de la ligne ou sur une couleur
    //Avancer/tourner jusqu'à trouver une ligne ou trouver balle
   forward(TensionSuiveurLigne, tensionSuiveurLigne[7], tensionSuiveurLigne[6]);
    //arrêt des moteurs
}

int suivreLigne()
{
    // MODIFIER LA PIN ANALOGUE LUE 
    AnalSuiveurLigne = analogRead(PIN_SUIVEUR);

    // Convertion valeur analogue (0 à 1023.0) en tension (0 à 5V)
    TensionSuiveurLigne = AnalSuiveurLigne * (5.0 / 1023.0);
    //input_value_AX = analogRead(PIN_SUIVEUR);

    //input_value_AX = 0-5V --> valeur entre 0 et 1023
    //À TESTER POUR CONNAITRE CHIFFRES EXACTS    
    
    if (TensionSuiveurLigne <= tensionSuiveurLigne[0])
    {
        aucunCapteur();
        return 1;
    }
    if (TensionSuiveurLigne <= tensionSuiveurLigne[1] && TensionSuiveurLigne > tensionSuiveurLigne[0])
    {
        capteurG();
        return 0;
    }
    if (TensionSuiveurLigne <= tensionSuiveurLigne[2] && TensionSuiveurLigne > tensionSuiveurLigne[1])
    {
        capteurC();
        return 0;
    }
    if (TensionSuiveurLigne <= tensionSuiveurLigne[3] && TensionSuiveurLigne > tensionSuiveurLigne[2])
    {
        capteurG_C();
        return 0;
    }
    if (TensionSuiveurLigne <= tensionSuiveurLigne[4] && TensionSuiveurLigne > tensionSuiveurLigne[3])
    {
        capteurD();
        return 0;
    }
    if (TensionSuiveurLigne <= tensionSuiveurLigne[5] && TensionSuiveurLigne > tensionSuiveurLigne[4])
    {
        capteurG_D();
        return 0;
    }
    if (TensionSuiveurLigne <= tensionSuiveurLigne[6] && TensionSuiveurLigne > tensionSuiveurLigne[5])
    {
        capteurC_D();
        return 0;
    }
    if (TensionSuiveurLigne <= tensionSuiveurLigne[7] && TensionSuiveurLigne > tensionSuiveurLigne[6])
    {
        capteurG_C_D();
        return 0;
    }
    else
    {
        return 0;
    }
    
  /*
    switch(TensionSuiveurLigne){
        case 0 ... 0.71:
        aucunCapteur();//les trois capteurs sont sur la ligne
        break;

        case 0.71 ... 1.42:
        capteurD();//seulement le capteur droit est hors ligne
        break;

        case 1.42 ... 2.12:
        capteurC();//seulement le capteur central est hors ligne *?? impossible ??*
        break;

        case 2.12 ... 2.85:
        capteurC_D();//seulement le capteur gauche est sur la ligne
        break;

        case 2.85 ... 3.55:
        capteurG();//le capteur gauche est hors ligne
        break;

        case 3.55 ... 4.26:
        capteurG_D();//le robot est enligné
        break;

        case 4.26 ... 4.97:
        capteurG_C();//le capteur droit est sur la ligne
        break;

        case 893 ... 1023:
        capteurG_C_D();//les trois capteurs sont hors ligne
        break;
    }
*/
}

void depart(){
    //fonction avancer de x mètres jusqu'au milieu du cercle

    //fonction tourner vers couleur

    /*while(couleur != couleur_recherché){
        suivreLigne();
    }*/
}