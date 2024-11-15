#ifndef MOTOR_H
#define MOTOR_H

class Motor{
  private:
    int en;
    int in1;
    int in2;
  public:
    Motor();
    Motor(int theEn, int theIn1, int theIn2);

    void init();

    void go(bool forward);

    void go(bool forward, int speed);

    void stop();
};
#endif