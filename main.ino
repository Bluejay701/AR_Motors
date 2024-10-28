class Sensor {
  private:
    int echoPin;
    int trigPin;
    long duration;

    void read(){
      digitalWrite(trigPin, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH);
    }

  public:
    Sensor(){}
    Sensor(int theEchoPin, int theTrigPin){
      echoPin = theEchoPin;
      trigPin = theTrigPin;
      init();
    }

    void init(){
      Serial.begin(9600);
      pinMode(echoPin, INPUT);
      pinMode(trigPin, OUTPUT);
    }

    long readCm(){
      read();
      return (duration/2)/29.1;
    }

    long readInch(){
      read();
      return (duration/2)/74;
    }
};

class Sensors{
  private:
    Sensor frontLeft;
    Sensor frontRight;
    Sensor sLeft;
    Sensor sRight;
    Sensor back;
  public:
    Sensors(){}
    Sensors(Sensor theFrontL, Sensor theFrontR, Sensor theLeft, Sensor theRight, Sensor theBack){
      frontLeft = theFrontL;
      frontRight = theFrontR;
      sLeft = theLeft;
      sRight = theRight;
      back = theBack;
    }

    long sideTotal(){
      return sLeft.readInch() + sRight.readInch();
    }

    long front(){
      return min(frontLeft.readInch(), frontRight.readInch());
    }

    long right(){
      return sRight.readInch();
    }

    long left(){
      return sLeft.readInch();
    }

    long side(bool boolRight){
      return boolRight? right() : left();
    }
};

class Motor{
  private:
    int en;
    int in1;
    int in2;
  public:
    Motor(){}
    Motor(int theEn, int theIn1, int theIn2){
      en = theEn;
      in1 = theIn1;
      in2 = theIn2;
    }

    void init(){
      pinMode(en, OUTPUT);
      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT);
    }

    void go(bool forward){
      digitalWrite(in1, (forward? LOW:HIGH));
      digitalWrite(in2, (forward? HIGH:LOW));
      analogWrite(en, 255);
    }

    void go(bool forward, int speed){
      digitalWrite(in1, (forward? LOW:HIGH));
      digitalWrite(in2, (forward? HIGH:LOW));
      analogWrite(en, speed);
    }

    void stop(){
      analogWrite(en, 0);
    }
};

const long FrontStoppingDistance = 14;
const long SideStoppingDistance = 8;
const long SideSensorError = 0.15; //15% error compensation for side total distance calculation
const int DrivingSpeed = 140;
const int SensorDelayTime = 60;
const int MotorDelayTime = 1000;

//motor 1 (front left)
// #define L_enA 2
// #define L_in1 4
// #define L_in2 5

//motor 2 (back left)
// #define L_enB 3
// #define L_in3 6
// #define L_in4 7

//motor 3 (front right)
// #define R_enA 12
// #define R_in1 11
// #define R_in2 9

//motor 4 (back right)
// #define R_enB 13
// #define R_in3 8
// #define R_in4 10

Motor motors[4] = {{2, 4, 5}, {3, 6, 7}, {12, 11, 9}, {13, 8, 10}};

//                         front left.   front right.   left.         right         back
Sensors sensors = Sensors({Sensor(2, 3), Sensor(4, 5), Sensor(6, 7), Sensor(8, 9), Sensor(10, 11)});
int totalDistance;

void setup(){
  totalDistance = sensors.sideTotal();
}

void loop() {
  //first part of course
  int distanceToFront = sensors.front();
  while(true){
    forward(DrivingSpeed);
    while(sensors.front() > FrontStoppingDistance){
      delay(SensorDelayTime);
    }
    stop();
    delay(MotorDelayTime);

    if(totalDistance > (sensors.sideTotal() * (1 - SideSensorError)) && totalDistance < (sensors.sideTotal() * (1 + SideSensorError))){
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
  
}