#include "KRgbLed.h"

KRgbLed::KRgbLed(int pin, int ledCount, CRGB offColour, CRGB onColour) {
  this->pin = pin;
  this->ledCount = ledCount;
  this->onColour = onColour;
  this->offColour = offColour;
  this->twoColour = true;
  this->on = true;
}

KRgbLed::KRgbLed(int pin, int ledCount, CRGB offColour, CRGB onColour[]) {
  this->pin = pin;
  this->ledCount = ledCount;
  this->offColour = offColour;
  this->onColours = onColours;
  this->twoColour = false;
  this->on = true;
}

void KRgbLed::turnOn() {
  if(!on) {
    on = true;
    if(twoColour) {
      FastLED.showColor(onColour);
    } else {
      for(int i=0; i<ledCount; i++) {
        leds[i] = onColours[i];
      }
      FastLED.show();
    }
    delay(50);
  }
}

void KRgbLed::turnOff() {
  if(on) {
    on = false;
    FastLED.showColor(offColour);
    delay(50);
  }
}

void KRgbLed::switchState() {
  if(on) {
    turnOff();
  } else {
    turnOn();
  }
}
