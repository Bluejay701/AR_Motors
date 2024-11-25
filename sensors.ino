#include "sensors.h"

Sensors::Sensors(){}
Sensors::Sensors(Sensor theFrontL, Sensor theFrontR, Sensor theLeft, Sensor theRight, Sensor theBack){
  frontLeft = theFrontL;
  frontRight = theFrontR;
  sLeft = theLeft;
  sRight = theRight;
  tBack = theBack;
}

long Sensors::sideTotal(){
  return sLeft.readInch() + sRight.readInch();
}

long Sensors::front(){
  long readL = frontLeft.readInch();
  long readR = frontRight.readInch();
  // Serial.print("Right: ");
  // Serial.print(readR);
  // Serial.print(" Left: ");
  // Serial.println(readL);
  return min(readL, readR);
}

long Sensors::right(){
  return sRight.readInch();
}

long Sensors::left(){
  return sLeft.readInch();
}

long Sensors::side(bool boolRight){
  return boolRight? right() : left();
}

long Sensors::back(){
  return tBack.readCm();
}