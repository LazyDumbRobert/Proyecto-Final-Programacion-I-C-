#include <Stepper.h>
int STEPS = 2848;
Stepper stepper(STEPS, 8,10,9,11);
const int trigpin = 7; //cafe 
const int echopin = 6; //morado
long duracion;
int distancia;

void setup()
{
Serial.begin(9600);
pinMode(trigpin, OUTPUT);
pinMode(echopin, INPUT);

}

void loop()
{
digitalWrite(trigpin, LOW);
delayMicroseconds(2);
digitalWrite(trigpin, HIGH);
delayMicroseconds(10);
digitalWrite(trigpin, LOW);
duracion = pulseIn(echopin,HIGH);
distancia = duracion / 58.2;   //V=2

if(distancia <=20 && distancia >= 0)
  {
    stepper.setSpeed(10);
    stepper.step(2848*2.5);
   
    }
  }
