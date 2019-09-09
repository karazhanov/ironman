#include "KServo.h"

KServo::KServo(uint8_t pin) {
  this->pin = pin;
}

void KServo::init(int openAngle, int closeAngle) {
  openState = openAngle;
  closeState = closeAngle;
  servo.attach(pin);
  close();
}

bool KServo::isOpen() {
  return opened;
}

void KServo::open() {
  servo.write(openState);
  opened = true;
}

void KServo::close() {
  servo.write(closeState);
  opened = false;
}

int KServo::getState() {
  return servo.read();
}

void KServo::inc() {
  servo.write(servo.read()+1);
  delay(15);
}

void KServo::dec() {
  servo.write(servo.read()-1);
  delay(15);
}
