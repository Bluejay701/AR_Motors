#include "sensors.h"

Sensors::Sensors(){}
Sensors::Sensors(Sensor theFrontL, Sensor theFrontR, Sensor theLeft, Sensor theRight, Sensor theBack){
  frontLeft = theFrontL;
  frontRight = theFrontR;
  sLeft = theLeft;
  sRight = theRight;
  back = theBack;
}

long Sensors::sideTotal(){
  return sLeft.readInch() + sRight.readInch();
}

long Sensors::front(){
  return min(frontLeft.readInch(), frontRight.readInch());
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