
#include "Button.h"
#include "RgbLed.h"

Button repulsorButton(2);
Button stonesButton(3);
Button servoButton(4);
RgbLed led(6, CRGB::Black, CRGB::Red, 3);

void setup() {
  repulsorButton.init();
  stonesButton.init();
  servoButton.init();
  led.init();
  
//  FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, LED_COUNT);
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
//  Serial.print("1 = ");
//  Serial.print(digitalRead(2));
//  Serial.print(" 2 = ");
//  Serial.print(digitalRead(3));
//  Serial.print(" 3 = ");
//  buttonState = digitalRead(4);
//  Serial.println(buttonState);
//  if(buttonState == HIGH) {
//    FastLED.showColor(CHSV(130, 150, buttonState * 200));
//  } else {
//    FastLED.showColor(CHSV(130, 150, 0));
//  }

//  checkButton(2, 0);
//  checkButton(3, 1);
//  checkButton(4, 2);
  delay(50);
//  FastLED.show();
}

//
//void checkButton(int pin, int led) {
//  leds[led] = (digitalRead(pin) == HIGH) ? CRGB::Green : CRGB::Red;
//}
