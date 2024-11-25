#ifndef SENSORS_H
#define SENSORS_H

class Sensors{
  private:
    Sensor frontLeft;
    Sensor frontRight;
    Sensor sLeft;
    Sensor sRight;
    Sensor tBack;
  public:
    Sensors();
    Sensors(Sensor theFrontL, Sensor theFrontR, Sensor theLeft, Sensor theRight, Sensor theBack);

    long sideTotal();

    long front();

    long right();

    long left();

    long side(bool boolRight);

    long back();
};
#endif