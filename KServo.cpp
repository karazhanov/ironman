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

void KServo::inc() {
  int i = servo.read()+1;
  servo.write(i);
  Serial.print("Current angle = ");
  Serial.println(i);
}

void KServo::dec() {
  int i = servo.read()-1;
  servo.write(i);
  Serial.print("Current angle = ");
  Serial.println(i);
}

void KServo::close() {
  servo.write(closeState);
  opened = false;
}

int KServo::getState() {
  return servo.read();
}
