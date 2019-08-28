#ifndef __MY_BUTTON_H__
  #define __MY_BUTTON_H__

#include <stdint.h>
#include "Arduino.h"

class Button {
  private:
    uint8_t pin;
    bool pressed;
  public:
    Button(uint8_t pin);
    void init();
    void check();
    bool isPressed();
};

#endif
