#include "KButton.h"

KButton::KButton(uint8_t _pin) {
  this->pin = _pin;
}

void KButton::init() {
  pinMode(pin,INPUT);
  pressed = false;
  changed = false;
}

bool KButton::isChange() {
  bool tmp = digitalRead(pin);
  changed = (tmp != pressed);
  if(changed) {
    pressed = tmp;
  }
  return changed;
}

bool KButton::isPressed() {
 return pressed;
}
