#include "KRgbLed.h"

KRgbLed::KRgbLed(int ledCount, CRGB offColour, CRGB onColour) {
  this->ledCount = ledCount;
  this->onColour = onColour;
  this->offColour = offColour;
  this->twoColour = true;
  this->on = true;
}

KRgbLed::KRgbLed(int ledCount, CRGB offColour, CRGB onColours[]) {
  this->ledCount = ledCount;
  this->offColour = offColour;
  this->onColours = onColours;
  this->twoColour = false;
  this->on = true;
}

void KRgbLed::turnOn() {
  if(!on) {
    on = true;
      for(int i=0; i<ledCount; i++) {
        leds[i] = twoColour ? onColour : onColours[i];
      }
      needUpdate();
  }
}

void KRgbLed::turnOff() {
  if(on) {
    on = false;
    for(int i=0; i<ledCount; i++) {
        leds[i] = offColour;
    }
    needUpdate();
  }
}

void KRgbLed::switchState() {
  if(on) {
    turnOff();
  } else {
    turnOn();
  }
}
