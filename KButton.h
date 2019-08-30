#ifndef __MY_BUTTON_H__
  #define __MY_BUTTON_H__

#include <stdint.h>
#include "Arduino.h"

class KButton {
  private:
    uint8_t pin;
    bool pressed;
    bool changed;
  public:
    KButton(uint8_t pin);
    void init();
    bool isChange();
    bool isPressed();
};

#endif
