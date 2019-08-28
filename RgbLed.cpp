#include "RgbLed.h"

#define array_count(array) sizeof(array)/sizeof(array[0])

RgbLed::RgbLed(int pin, CRGB offColor, CRGB onColor, int ledCount) {
  this->ledCount = ledCount;
  this->pin = pin;
}

RgbLed::RgbLed(int pin, CRGB offColor, CRGB[] onColor) {
//
//
//
// void modifyArray( int b[]) {
//   int size = array_count(b);
// }
//

}

void RgbLed::init() {
  leds = new CRGB[ledCount];
  FastLED.addLeds<WS2812B, pin, RGB>(leds, ledCount);
}



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
