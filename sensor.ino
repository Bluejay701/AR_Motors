#include "sensor.h"

Sensor::Sensor(){}
Sensor::Sensor(int theEchoPin, int theTrigPin){
  echoPin = theEchoPin;
  trigPin = theTrigPin;
  init();
}

void Sensor::init(){
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void Sensor::read(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
}

long Sensor::readCm(){
  read();
  return (duration/2)/29.1;
}

long Sensor::readInch(){
  read();
  return (duration/2)/74;
}