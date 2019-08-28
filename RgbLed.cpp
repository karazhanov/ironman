#include "RgbLed.h"

#define array_count(array) sizeof(array)/sizeof(array[0])

RgbLed::RgbLed(int pin, CRGB offColour, CRGB onColour, int ledCount) {
  this->ledCount = ledCount;
  this->pin = pin;
  this->twoColour = true;
  this->onColour = onColour;
  this->offColour = offColour;
}

RgbLed::RgbLed(int pin, CRGB offColour, CRGB onColours[]) {
  this->pin = pin;
  this->twoColour = false;
  this->ledCount = array_count(onColours);
  this->offColour = offColour;
  this->onColours = onColours;
}

//void RgbLed::init() {
//  leds = new CRGB[ledCount];
//  init<pin>();
////  FastLED.addLeds<WS2812B, pin, RGB>(leds, ledCount);
//}

//
// void MySensorsButton::sendState() {
//   bool isPressed = digitalRead(pin)==LOW;
//   if(pressed != isPressed) {
//     sended = false;
//     pressed = isPressed;
//   }
//   if(!sended) {
//     send(message.set(pressed ? true : false));
//     sended = true;
//   }
// }
