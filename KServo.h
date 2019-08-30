#ifndef __MY_SERVO_H__
  #define __MY_SERVO_H__

#include <stdint.h>
#include "Arduino.h"
#include <Servo.h>

class KServo {
  private:
    uint8_t pin;
    bool opened;
    uint8_t openState;
    uint8_t closeState;
    Servo servo;
  public:
    KServo(uint8_t pin);
    void init(int openAngle, int closeAngle);
    void inc();
    void dec();
    bool isOpen();
    void open();
    void close();
    int getState();
};

#endif
