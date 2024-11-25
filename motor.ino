#include "motor.h"

Motor::Motor(){}
Motor::Motor(int theEn, int theIn1, int theIn2, bool theDirectionCorrect){
  en = theEn;
  in1 = theIn1;
  in2 = theIn2;
  directionCorrect = theDirectionCorrect;
}

void Motor::init(){
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void Motor::go(bool forward){
  digitalWrite(in1, ((directionCorrect?forward:!forward)? LOW:HIGH));
  digitalWrite(in2, ((directionCorrect?forward:!forward)? HIGH:LOW));
  analogWrite(en, 255);
}

void Motor::go(bool forward, int speed){
  digitalWrite(in1, ((directionCorrect?forward:!forward)? LOW:HIGH));
  digitalWrite(in2, ((directionCorrect?forward:!forward)? HIGH:LOW));
  analogWrite(en, speed);
}

void Motor::stop(){
  analogWrite(en, 0);
}