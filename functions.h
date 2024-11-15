#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void forward();
void forward(int speed);

void backward();
void backward(int speed);

void moveSide(bool right);
void moveSide(bool right, int speed);

void turn(bool right);
void turn(bool right, int speed);

void stop();

#endif