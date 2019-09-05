#ifndef __MY_RGB_LED_H__
  #define __MY_RGB_LED_H__

#include <stdint.h>
#include <FastLED.h>

class KRgbLed {
  private:
    int ledCount;
    CRGB* leds;
    bool twoColour;
    CRGB onColour;
    CRGB* onColours;
    CRGB offColour;
    bool on;
  public:
    KRgbLed(int ledCount, CRGB offColour, CRGB onColour);
    KRgbLed(int ledCount, CRGB offColour, CRGB onColours[]);
    template< uint8_t PIN = 0> void init() {
      leds = new CRGB[ledCount];
      FastLED.addLeds< WS2812B, PIN, RGB >(leds, ledCount);
      turnOff();
    }
    void turnOn();
    void turnOff();
    void switchState();
};

#endif
