#include "Button.h"

Button::Button(uint8_t _pin) {
  this->pin = _pin;
}

void Button::init() {
  pinMode(pin,INPUT);
  pressed = false;
}

void Button::check() {

}

bool Button::isPressed() {
 return pressed;
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
