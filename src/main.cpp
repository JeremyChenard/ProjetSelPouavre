#include <LibRobus.h>
#include <headers/Capteurs.h>
#include <headers/FonctionsSuiveur.h>


//#define PINSUIVEURLIGNE A7
#define ROUGE 0
#define VERT 1
#define BLEU 2
#define JAUNE 3

#define ROBOTA 1
#define ROBOTB 0

#define ANGLEROBOTA 25
#define ANGLEROBOTB 40

#define COLORBUTBALLON BLEU
#define BUTFINAL ROUGE

bool hasBall = false;

String color;
int indexOfBall = 0;
int indexOfGoal = 1;
const int robotId = 0;
int direction = -1;
int lastDirection;
int otherRobotPosition; // todo peut etre pratique d integrer cela pour bien se tasser du chemin avec le robot A 
bool done = false;
bool ibal = false;
bool f = false;

int i = 0;

void AvanceToutDroit(int distance)
{
  //Réinitialisation des encodeurs.
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  
  //Initialisation des variables.
  int pulse=0;
  int encodeur=0;
  float speed = 0;

  //Calculer le nombre de pulse par cm.
  pulse=134*distance;

   //Tant que le moteur gauche n'a pas atteint le nombre de pulse voulu. 
  while (encodeur < pulse)
  { 
    speed += 0.1;
    if (speed > maxSpeed) speed = maxSpeed;
    currentSpeed = speed;

    pid(currentSpeed);
   
    delay(50);

#if ANGLEROBOTA
    encodeur = ENCODER_Read(0);
#endif

#if ANGLEROBOTA
    encodeur = ENCODER_Read(0);
#endif
  }

  decelerate();
}

void setup()
{
  BoardInit();
  SERVO_Disable(0);
  delay(10);

  pinMode(PIN_SUIVEUR, INPUT);
}

//exemple de ce que ca pourrait avoir l air (peut etre plus simple si on utilise pas le capteur de couleur)
void loop() 
{
  //Toucher le bumper arrière pour qu'il commence.
  while (!ROBUS_IsBumper(3) && !done);

  done = true;
#if ROBOTA   
  do
  {
  //Si le ballon est dans le but rouge.
  if(COLORBUTBALLON == ccRouge)
  {
    //Positionnement devant le rouge.
    rotate(0, 90);
    AvanceToutDroit(45);
    rotate(1, 90);
    AvanceToutDroit(89);
    rotate(0, 45);
    delay(500);

    //Aller chercher la balle.
    AvanceToutDroit(14);
    delay(100);
    ouvrirPinces(ANGLEROBOTA);
    rotate(1, 180);
    delay(100);
    AvanceToutDroit(25);

    //Esquive de l'autre robot.
    rotate(1, 35);
    AvanceToutDroit(20);
    rotate(0, 35);

    //Aller porter la balle au centre.
    AvanceToutDroit(15);
    fermerPinces(ANGLEROBOTA);

    //Aller ce cacher
    backward(20);
    rotate(0, 45);
    backward(50);
  }
  //Si le ballon est dans le but vert.
  if(COLORBUTBALLON == ccVert)
  {
    //Positionnement devant le vert.
    rotate(1, 90);
    AvanceToutDroit(45);
    rotate(0, 90);
    AvanceToutDroit(89);
    rotate(1, 43);
    delay(500);

    //Aller chercher la balle.
    AvanceToutDroit(18);
    delay(100);
    ouvrirPinces(ANGLEROBOTA);
    rotate(1, 180);
    delay(100);
    AvanceToutDroit(25);

    //Esquive de l'autre robot.
    rotate(0, 45);
    AvanceToutDroit(40);
    rotate(1, 90);

    //Aller porter la balle au centre.
    AvanceToutDroit(15);
    fermerPinces(ANGLEROBOTA);

    //Aller ce cacher
    backward(70);
  }
  //Si le ballon est dans le but bleu.
  if(COLORBUTBALLON == ccBleu)
  {
    //Positionnement devant le bleu.
    rotate(1, 90);
    AvanceToutDroit(28);
    rotate(1, 45);

    //Aller chercher la balle.
    AvanceToutDroit(43);
    delay(100);
    ouvrirPinces(ANGLEROBOTA);
    rotate(1, 180);
    delay(100);
    AvanceToutDroit(70);

    //Aller porter la balle au centre.
    fermerPinces(ANGLEROBOTA);

     //Aller ce cacher
    backward(20);
    rotate(0, 45);
    backward(50);
  }
  //Si le ballon est dans le but jaune.
  if(COLORBUTBALLON == ccJaune)
  {
    //Positionnement devant le jaune.
    rotate(0, 90);
    AvanceToutDroit(28);
    rotate(0, 45);

    //Aller chercher la balle.
    AvanceToutDroit(48);
    delay(100);
    ouvrirPinces(ANGLEROBOTA);
    rotate(1, 170);
    delay(100);
    AvanceToutDroit(70);

    //Aller porter la balle au centre.
    fermerPinces(ANGLEROBOTA);

    //Aller ce cacher
    backward(20);
    rotate(1, 45);
    backward(50);
  }
  i = 1;
  } while (i==0);
#endif

#if ROBOTB 
  //Attendre 1 munite avant de commencer.
  delay(60000);

  //Si le but est le jaune.
  if(BUTFINAL == ccRouge)
  {
    //Possitionnement 
    rotate(0, 90);
    AvanceToutDroit(40);
    rotate(1, 90);
    AvanceToutDroit(78);

    //Le but.
    rotate(1, 135);
    AvanceToutDroit(180);
    delay(1000);
  }
  //Si le but est le jaune.
  if(BUTFINAL == ccVert)
  {
    //Possitionnement.
    rotate(1, 90);
    AvanceToutDroit(40);
    rotate(0, 90);
    AvanceToutDroit(78);


    //Le but.
    rotate(0, 135);
    AvanceToutDroit(180);
    delay(1000); 
  }
  //Si le but est le jaune.
  if(BUTFINAL == ccBleu)
  {
    //Possitionnement
    rotate(1, 90);
    AvanceToutDroit(40);

    //Le but.
    rotate(0, 135);
    AvanceToutDroit(180);
  
  }
  //Si le but est le jaune.
  if(BUTFINAL == ccJaune)
  {
    //Possitionnement
    rotate(0, 90);
    AvanceToutDroit(40);

    //Le but.
    rotate(1, 135);
    AvanceToutDroit(180);
  
  }
#endif
/*
//ROUGE
rotate(0, 90);
AvanceToutDroit(45);
rotate(1, 90);
AvanceToutDroit(89);
rotate(0, 45);

delay(500);

AvanceToutDroit(25);

delay(100);

ouvrirPinces(ANGLEROBOTB);

rotate(1, 180);
delay(100);

AvanceToutDroit(30);

delay(2000);

suivreLigne();

delay(10000);

*/
 /*
  //fermerPinces(ANGLEROBOTA);
  ouvrirPinces(ANGLEROBOTA);
  backward(25); 

  delay(500);

  turn(0, 45);
  backward(10); 

  rotate(1, 45);
  backward(10); 

  fermerPinces(ANGLEROBOTA);
  //ouvrirPinces(ANGLEROBOTA);
  delay(20000);
  */
  
  /*
  suivreLigne();
  delay(1000);
  */

/*
  ouvrirPinces();
  while (!ROBUS_IsBumper(3) && !done);

  done = true;  
  //backward(5); 

  f = forward(ibal);
  
  if (f == true)
  {
    ibal = true;
    //ouvrirPinces();
    fermerPinces();
    //delay(1000);
  }

  f = forward(ibal);

  if(f == false)
  {
    //fermerPinces();
    ouvrirPinces();
    backward(20);
  }
  
  delay(100000);
*/
  /*
  Couleur[getColor()];
  delay(5000);
  
  double AnalSuiveurLigne = ValeurParDefaut;
  double TensionSuiveurLigne = ValeurParDefaut;
  
  AnalSuiveurLigne = analogRead(PINSUIVEURLIGNE);

  Serial.println(AnalSuiveurLigne);

  // Convertion valeur analogue (0 à 1023.0) en tension (0 à 5V)
  TensionSuiveurLigne = AnalSuiveurLigne * (5.0 / 1023.0);

  Serial.println(TensionSuiveurLigne);

  //Noir
  if (TensionSuiveurLigne <= tensionSuiveurLigne[0])
  {
    Serial.println("[X][X][X]");
  }
  if (TensionSuiveurLigne <= tensionSuiveurLigne[1] && TensionSuiveurLigne > tensionSuiveurLigne[0])
  {
    Serial.println("[][X][X]");
  }
  if (TensionSuiveurLigne <= tensionSuiveurLigne[2] && TensionSuiveurLigne > tensionSuiveurLigne[1])
  {
    Serial.println("[X][][X]");
  }
  if (TensionSuiveurLigne <= tensionSuiveurLigne[3] && TensionSuiveurLigne > tensionSuiveurLigne[2])
  {
    Serial.println("[][][X]");
    do
    {
      turn(1, 10);
      forward();
    }while(TensionSuiveurLigne <= tensionSuiveurLigne[5] && TensionSuiveurLigne > tensionSuiveurLigne[4]);
  }
  if (TensionSuiveurLigne <= tensionSuiveurLigne[4] && TensionSuiveurLigne > tensionSuiveurLigne[3])
  {
    Serial.println("[X][X][]");
  }
  if (TensionSuiveurLigne <= tensionSuiveurLigne[5] && TensionSuiveurLigne > tensionSuiveurLigne[4])
  {
    Serial.println("[][X][]");
    forward();
  }
  if (TensionSuiveurLigne <= tensionSuiveurLigne[6] && TensionSuiveurLigne > tensionSuiveurLigne[5])
  {
    Serial.println("[X][][]");
    do
    {
      turn(0, 10);
      forward();
    }while(TensionSuiveurLigne <= tensionSuiveurLigne[5] && TensionSuiveurLigne > tensionSuiveurLigne[4]);
  }
  if (TensionSuiveurLigne <= tensionSuiveurLigne[7] && TensionSuiveurLigne > tensionSuiveurLigne[6])
  {
    Serial.println("[][][]");
  }
  

  delay(1000);
*/
  /*
  if ( robotId == 0 ) 
  {
    
    //Si le ballon est dans le but rouge.
    if(COLORBUTBALLON == Couleur[ccRouge])
    {
      rotate(0,90);
      forward();
      rotate(1,90);
      forward();
    }
    //Si le ballon est dans le but vert.
    if(COLORBUTBALLON == Couleur[ccVert])
    {

    }
    //Si le ballon est dans le but bleu.
    if(COLORBUTBALLON == Couleur[ccBleu])
    {

    }
    //Si le ballon est dans le but jaune.
    if(COLORBUTBALLON == Couleur[ccJaune])
    {

    }
    
    //Tourne sur lui même
    rotate(0,180);
    forward();
    rotate(0,90);
    forward();

    do 
    {
      direction = getDirections(Couleur[getColor()]);
      if(direction != 3) 
      {
        lastDirection = direction;
      }
      rotate(direction,90);
      forward();
    }while(direction != 3);

    rotate((lastDirection == 0)? 1 : 0, 90);
    fermerPinces();
    turn((lastDirection == 0)? 1 : 0, 180);
    forward(); // suivre la ligne 
    ouvrirPinces();
    backward(30);
    rotate(1,90);
    backward(30);
  }
  else 
  {
    delay(60000);
    forward();
    fermerPinces();
    turn(0,180);
    forward();
    turn(0,90);
    forward();
    do 
    {
      direction = getDirections(Couleur[getColor()]);
      if(direction != 3) 
      {
        lastDirection = direction;
      }
      turn(direction,90);
      forward();
    }while(direction != 3);
    
    rotate((turn == 0)? 1 : 0, 90);
    forward();
    ouvrirPinces();
    backward(10);
  }*/
}