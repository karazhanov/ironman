#include "KRgbLed.h"

KRgbLed::KRgbLed(int ledCount, CRGB offColour, CRGB onColour) {
  this->ledCount = ledCount;
  this->onColour = onColour;
  this->offColour = offColour;
  this->twoColour = true;
  this->on = true;
}

KRgbLed::KRgbLed(int ledCount, CRGB offColour, CRGB onColour[]) {
  this->ledCount = ledCount;
  this->offColour = offColour;
  this->onColours = onColours;
  this->twoColour = false;
  this->on = true;
}

void KRgbLed::turnOn() {
  if(!on) {
    on = true;
    Serial.print("KRgbLed::turnOn() on pin ");
    Serial.println(pin);
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
    Serial.print("KRgbLed::turnOff() on pin ");
    Serial.println(pin);
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
