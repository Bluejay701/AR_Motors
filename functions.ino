void forward(){
  for(Motor motor:motors){
    motor.go(true);
  }
}

void forward(int speed){
  for(Motor motor:motors){
    motor.go(true, speed);
  }
}

void backward(){
  for(Motor motor:motors){
    motor.go(false);
  }
}

void backward(int speed){
  for(Motor motor:motors){
    motor.go(false, speed);
  }
}

void moveSide(bool right){
  motors[0].go(right);
  motors[1].go(!right);
  motors[2].go(!right);
  motors[3].go(right);
}

void moveSide(bool right, int speed){
  motors[0].go(right, speed);
  motors[1].go(!right, speed);
  motors[2].go(!right, speed);
  motors[3].go(right, speed);
}

void turn(bool right){
  motors[0].go(right);
  motors[1].go(right);
  motors[2].go(!right);
  motors[3].go(!right);
}

void turn(bool right, int speed){
  motors[0].go(right, speed);
  motors[1].go(right, speed);
  motors[2].go(!right, speed);
  motors[3].go(!right, speed);
}

void stop(){
  for(Motor motor : motors){
    motor.stop();
  }
}