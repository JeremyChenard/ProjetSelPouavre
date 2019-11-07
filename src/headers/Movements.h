#ifndef Movements_H_
#define Movements_H_

#include <headers/Servomoteur.h>

int pulsesToAccelerate (float speed);
int pulsesToDecelerate(float speed);
float chooseAccordingSpeed(int pulses);
void decelerate ();
void pid(float currentSpeed);

float maxSpeed = 0.5;
float currentSpeed = 0;

float wheelDiameter = 7.62;
float pi = PI;
float ppr = 3200;
float distancePerTurn = pi * wheelDiameter;
int pulsesPerCm = ppr / distancePerTurn;

bool searching = false;
bool isBackward = false;

int accelerationMsDelay = 100; //25 or higher (tenir compte que le maximum de boucle est 10)

const int decelerationPulses[10]=
{
    0,
    0,
    32,
    57,
    74,
    96,
    123,
    145,
    165,
    185
};


#if 1
void forward(double suiveurLigne, double maxLigne, double minLigne) {
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  bool accelerate = true;
  float speed = 0;

  double analogue = 0;

  while(accelerate) 
  {
    speed += 0.1;
    if (speed > maxSpeed) speed = maxSpeed;
    currentSpeed = speed;
    
    if(suiveurLigne >= maxLigne || suiveurLigne < minLigne || (getDistance(PINDISTANCEBAS) <= 20 && getDistance(PINDISTANCEHAUT) <= 20))
    {
        accelerate = false;
        decelerate();
    }
    else 
    {
      pid(currentSpeed);
    } 
    analogue = analogRead(A7);
    Serial.println(analogue);

    // Convertion valeur analogue (0 à 1023.0) en tension (0 à 5V)
    suiveurLigne = analogue * (5.0 / 1023.0);

    Serial.println(suiveurLigne);
    delay(accelerationMsDelay); 
   
  #else
  void forward(int temps) 
  {
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  bool accelerate = true;
  float speed = 0;
  int i = 0;

  while(accelerate) 
  {
    speed += 0.1;
    if (speed > maxSpeed) speed = maxSpeed;
    currentSpeed = speed;
    
    if(i == temps) 
    {
      accelerate = false;
      decelerate();
    }
    else 
    {
      pid(currentSpeed);
    } 
    delay(accelerationMsDelay); 
    i ++;
    #endif

    /*if(getDistance(PINDISTANCEBAS) <= 20 && getDistance(PINDISTANCEHAUT) >= 20 && ballon == false) 
    {
      accelerate = false;
      ballon = true;
      decelerate();
    }

    if(getDistance(PINDISTANCEBAS) <= 20 && getDistance(PINDISTANCEHAUT) <= 20) {
      accelerate = false;
      //ballon = false;
      decelerate();
    }
    else 
    {
      pid(currentSpeed);
    } 
    delay(accelerationMsDelay); 
    */
  }

  //return ballon;
}

void backward (float distance) {
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  bool accelerate = true;
  float speed = 0;
  int decelerationPulses = 0;
  long distanceInPulses = 0;
  distanceInPulses = (long) pulsesPerCm * (long) distance;
  while(accelerate) {
    speed -= 0.1;
    if (speed < maxSpeed * -1) speed = maxSpeed * -1;
    currentSpeed = speed;
    decelerationPulses = pulsesToDecelerate((currentSpeed * -1)) * 100 / accelerationMsDelay;
    if(ENCODER_Read(0) * -1 > distanceInPulses - decelerationPulses) {
      accelerate = false;
      decelerate();
    }else {
      pid(currentSpeed);
    } 
    delay(accelerationMsDelay); 
  } 
}

void decelerate () {
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  while (currentSpeed != 0) {
    if(isBackward) {
      currentSpeed = currentSpeed + 0.1;
      if(currentSpeed > 0) currentSpeed = 0;
      pid(currentSpeed);
    }else { 
      currentSpeed = currentSpeed - 0.1;
      if(currentSpeed < 0) currentSpeed = 0;
      pid(currentSpeed);
    }
    delay(accelerationMsDelay);
  } 
  isBackward = false; 
}

void pid(float currentSpeed) //reculons longue distance ca bug.
{
  if(currentSpeed != (float) 0) {
    float proportionnalControl = 0.001;

    float leftPulse = ENCODER_Read(0);
    float rightPulse = ENCODER_Read(1);
    float error = leftPulse - rightPulse;
    float rightSpeed = 0;
    float leftSpeed = 0;
    int backwardFactor = 0;
    if(isBackward) {
      backwardFactor = -1;
      error = (leftPulse + rightPulse);
    }else { 
      backwardFactor = 1;
    }
    if(error>5)
    {
      rightSpeed = (error * proportionnalControl * backwardFactor) + currentSpeed;  
      MOTOR_SetSpeed(1, rightSpeed);
      MOTOR_SetSpeed(0, currentSpeed);
    }
    else if(error<-5)
    {
      leftSpeed = (error * -1 * proportionnalControl * backwardFactor) + currentSpeed;
      MOTOR_SetSpeed(0, leftSpeed);
      MOTOR_SetSpeed(1, currentSpeed);
    }else{
      MOTOR_SetSpeed(0, currentSpeed);
      MOTOR_SetSpeed(1, currentSpeed);
    }
    error = 0;
  }else {
      MOTOR_SetSpeed(0, 0);
      MOTOR_SetSpeed(1, 0);
  } 
}

int pulsesToDecelerate (float speed) {
  return decelerationPulses[((int)(speed * 10))-1];
}

void turn (int side, int angle) {
  ( side == 0 ) ? side = 1 : side = 0;
  ENCODER_Reset(0);
  ENCODER_Reset(1);

  int pulses = 0;
  float encoder = 0;
  pulses = (((angle * PI) / 180) * 19) * pulsesPerCm;

  MOTOR_SetSpeed(side, 0.4);

  while(encoder <pulses)
  {
     encoder= ENCODER_Read(side);
  }
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
}

void rotate (int side, int angle) {
  ENCODER_Reset(0);
  ENCODER_Reset(1);

  int pulses = 0;
  float encoder = 0;
  pulses = (((angle * PI) / 180) * 19) * pulsesPerCm;
  int otherSide = 0;
  (side == 0) ? otherSide = 1 : otherSide = 0;

  MOTOR_SetSpeed(side, -0.2);
  MOTOR_SetSpeed(otherSide, 0.2);
 
  while(encoder <pulses)
  {
     encoder= (ENCODER_Read(side) * -1) + ENCODER_Read(otherSide) ;
  }
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
}


#endif 