#include "motor.h"
#include "sensor.h"
#include "sensors.h"
#include "functions.h"
#include <Servo.h>

const long FrontStoppingDistance = 15;
const long SideStoppingDistance = 8;
const long SideSensorError = 0.15; //15% error compensation for side total distance calculation
const int DrivingSpeed = 140;
const int SensorDelayTime = 250;
const int MotorDelayTime = 1000;

//new servo motors for claw
const int servoLPin = 39;
const int servoRPin = 37;
Servo servoL;
Servo servoR;

//bad senosrs: back, front right
//good: front left, right

int totalDistance;
Motor motors[4];
Sensors sensors;
// Sensor extraSensor = Sensor(45, 44);

void setup(){
  //front left
  motors[0] = Motor(7, 31, 30, false);
  //back left
  motors[1] = Motor(6, 33, 32, false);
  //front right
  motors[2] = Motor(4, 27, 26, true);
  //back right
  motors[3] = Motor(5, 29, 28, true);
  //                  front left.     front right.      left.          right            back
  sensors = Sensors({Sensor(47, 46), Sensor(49, 48), Sensor(51, 50), Sensor(53, 52), Sensor(45, 44) });
  // Sensor(45, 44)});


  // Serial.begin(9600);
  // Serial.println("test");
  totalDistance = sensors.sideTotal();

  //servo motors
  servoL.attach(servoLPin);
  servoR.attach(servoRPin);
}

void loop() {
  // int sensorReturn = sensors.front();
  // if(sensorReturn > FrontStoppingDistance){
  //   forward();
  // }else{
  //   stop();
  // }
  // delay(SensorDelayTime);
  //first part of course
  // int distanceToFront = sensors.front();
  while(true){
    forward(DrivingSpeed);
    while(sensors.front() > FrontStoppingDistance){
      delay(SensorDelayTime);
    }
    stop();
    delay(MotorDelayTime);

    if(totalDistance < (sensors.sideTotal() * (1 - SideSensorError))){
      break;
    }

    bool direction = sensors.right() > sensors.left();
    while(sensors.front() * 0.9 < FrontStoppingDistance){
      while(sensors.side(direction) > SideStoppingDistance || !(sensors.front() * 0.9 < FrontStoppingDistance)){
        moveSide(direction, DrivingSpeed);
        delay(SensorDelayTime);
      }

      stop();
      delay(MotorDelayTime);

      //THE SECOND PART OF THE IF ELSE NEEDS TO BE ADJUSTED FOR EDGE CASES!!!!!
      if(sensors.front() * 0.9 < FrontStoppingDistance){
        direction = !direction;
      }else{
        moveSide(direction, 80);
        delay(1000);
        stop();
        delay(MotorDelayTime);
      }
    }
  }

  //Starts from back of course

  //To close claw from open position
  servoL.write(30);
  delay(1000);    
  servoR.write(-30);
  delay(1000);
  
}
