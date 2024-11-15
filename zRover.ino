#include "motor.h"
#include "sensor.h"
#include "sensors.h"
#include "functions.h"

const long FrontStoppingDistance = 18;
const long SideStoppingDistance = 8;
const long SideSensorError = 0.15; //15% error compensation for side total distance calculation
const int DrivingSpeed = 140;
const int SensorDelayTime = 100;
const int MotorDelayTime = 1000;

Motor motors[4] = {{7, 31, 30}, {6, 33, 32}, {4, 27, 26}, {5, 29, 28}};

//                         front left.   front right.   left.         right         back
Sensors sensors = Sensors({Sensor(22, 23), Sensor(24, 25), Sensor(53, 52), Sensor(28, 29), Sensor(31, 30)});
int totalDistance;

void setup(){
  totalDistance = sensors.sideTotal();
}

void loop() {
  while(sensors.front() > FrontStoppingDistance){
    delay(SensorDelayTime);
    forward();
  }
  stop();
  delay(SensorDelayTime);
  //first part of course
  // int distanceToFront = sensors.front();
  // while(true){
  //   forward(DrivingSpeed);
  //   while(sensors.front() > FrontStoppingDistance){
  //     delay(SensorDelayTime);
  //   }
  //   stop();
  //   delay(MotorDelayTime);

  //   if(totalDistance < (sensors.sideTotal() * (1 - SideSensorError))){
  //     break;
  //   }

  //   bool direction = sensors.right() > sensors.left();
  //   while(sensors.front() * 0.9 < FrontStoppingDistance){
  //     while(sensors.side(direction) > SideStoppingDistance || !(sensors.front() * 0.9 < FrontStoppingDistance)){
  //       moveSide(direction, DrivingSpeed);
  //       delay(SensorDelayTime);
  //     }

  //     stop();
  //     delay(MotorDelayTime);

  //     //THE SECOND PART OF THE IF ELSE NEEDS TO BE ADJUSTED FOR EDGE CASES!!!!!
  //     if(sensors.front() * 0.9 < FrontStoppingDistance){
  //       direction = !direction;
  //     }else{
  //       moveSide(direction, 80);
  //       delay(1000);
  //       stop();
  //       delay(MotorDelayTime);
  //     }
  //   }
  // }

  //Starts from back of course
  
}