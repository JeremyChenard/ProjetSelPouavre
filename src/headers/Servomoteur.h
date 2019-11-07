#ifndef Servomoteur_H_
#define Servomoteur_H_

//#define ANGLEPINCE 25
//#define ANGLEPINCE 40

void fermerPinces(int anglePince)
{
    SERVO_Enable(0);
    for(int i = 0; i < anglePince; i++) {
        SERVO_SetAngle(0, i);
        delay(5);
    }
    delay(1000);
    if(anglePince == 25)
    {
        SERVO_Disable(0);
    }   
}

// Ouvre les pinces
void ouvrirPinces(int anglePince)
{
    SERVO_Enable(0);
    for(int i = anglePince; i > 0; i--) {
        SERVO_SetAngle(0, i);
        delay(5);
    }
    delay(1000);
    if(anglePince == 40)
    {
        SERVO_Disable(0);
    }   
}

#endif 