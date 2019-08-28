#ifndef __MY_RGB_LED_H__
  #define __MY_RGB_LED_H__

#include <stdint.h>
#include <FastLED.h>

// #define LED_COUNT 3
// #define LED_PIN 6
// CRGB leds[LED_COUNT];

class RgbLed {
  private:
    int ledCount;
    int pin;
    CRGB* leds;
    bool twoColour;
    CRGB onColour;
    CRGB* onColours;
    CRGB offColour;
  public:
    RgbLed(int pin, CRGB offColour, CRGB onColour, int ledCount);
    RgbLed(int pin, CRGB offColour, CRGB onColours[]);
    //void init();
    template< uint8_t PIN = 0>
    void init() {
      leds = new CRGB[ledCount];
      FastLED.addLeds< WS2812B, PIN, RGB >(leds, ledCount);
    }
    // void check();
    // bool isPressed();
};

#endif
