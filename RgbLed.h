#ifndef __MY_RGB_LED_H__
  #define __MY_RGB_LED_H__

#include <stdint.h>
#include "FastLED.h"

// #define LED_COUNT 3
// #define LED_PIN 6
// CRGB leds[LED_COUNT];

class RgbLed {
  private:
    int ledCount;
    int pin;
    CRGB* leds;
  public:
    RgbLed(int pin, CRGB offColor, CRGB onColor, int ledCount);
    RgbLed(int pin, CRGB offColor, CRGB[] onColor);
    // void init();
    // void check();
    // bool isPressed();
};

#endif
