#ifndef MOTOR_H
#define MOTOR_H

class Motor{
  private:
    int en;
    int in1;
    int in2;
    bool directionCorrect;
  public:
    Motor();
    Motor(int theEn, int theIn1, int theIn2, bool theDirectionCorrect);

    void init();

    void go(bool forward);

    void go(bool forward, int speed);

    void stop();
};
#endif