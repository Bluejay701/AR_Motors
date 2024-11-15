#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
  private:
    int echoPin;
    int trigPin;
    long duration;

    void read();

  public:
    Sensor();
    Sensor(int theEchoPin, int theTrigPin);

    void init();

    long readCm();

    long readInch();
};
#endif