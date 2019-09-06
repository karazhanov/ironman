#include "KButton.h"
#include "KRgbLed.h"
#include "KServo.h"
#include "KGyro.h"
#include "UTILS.h"

 KButton repulsorButton(2);
 KButton stonesButton(3);
KButton servoButton(4);
//KServo servo(10);
KGyro gyro;

CRGB stonesColors[] = {CRGB::Red, CRGB::Blue, CRGB::Green, CRGB::Yellow, CRGB::Purple, CRGB::Orange};
//KRgbLed repulsorLeft(3, CRGB::Black, CRGB::WhiteSmoke);
KRgbLed repulsorRight(3, CRGB::Black, CRGB::White);
KRgbLed stones(6, CRGB::Black, stonesColors);
//KRgbLed arcReactor(6, CRGB::Black, CRGB::WhiteSmoke);

bool repulsorOn = false;
float onRepulsorAngle = 0xFFFFFF;

bool KRgbLed::_needUpdate = false;

void setup() {
  Serial.begin(9600);

  repulsorButton.init();
  stonesButton.init();
  servoButton.init();

//  servo.init(50, 103);

//  repulsorLeft.init<5>();
  repulsorRight.init<9>();

  stones.init<11>();
  stones.turnOn();
//  arcReactor.init<6>();

//  gyro.init();
//  arcReactor.turnOn();
  KRgbLed::updateIfNeed();
}

void loop() {
//  checkButton(repulsorButton, repulsorRight);
//  checkButton(stonesButton, arcReactor);
//  checkButton(servoButton, stones);

//if(stonesButton.isChange() && stonesButton.isPressed()) {
//  repulsorLeft.switchState();
//  repulsorRight.switchState();
//}
//
//if(repulsorButton.isChange() && repulsorButton.isPressed()) {
//  repulsorLeft.switchState();
//  repulsorRight.switchState();
//}
//
//if(servoButton.isChange() && servoButton.isPressed()) {
//  repulsorLeft.switchState();
//  repulsorRight.switchState();
//}

//  checkServo();
//  checkGyro();


repulsorRight.switchState();
stones.switchState();

KRgbLed::updateIfNeed();
delay(1000);
}

inline void checkButton(KButton &b, KRgbLed &l) {
  if(b.isChange() && b.isPressed()) l.switchState();
}

//inline void checkServo() {
//   if(servoButton.isChange() && servoButton.isPressed())
//     if(servo.isOpen()) servo.close();
//     else servo.open();
//}

inline void checkGyro() {
  gyro.checkState();
//  print(F("#GYR:"));
//  print(gyro.getX(), 2);
//  print(F(","));
//  print(gyro.getY(), 2);

  if(gyro.getY() < -60) {
    if(!repulsorOn) {
      print("ON REPULSOR ");
//      repulsorLeft.turnOn();
      repulsorRight.turnOn();
//      stones.turnOff();
      repulsorOn = true;
      onRepulsorAngle = gyro.getX();
    } else {
      // if(gyro.getX() < 50 && gyro.getX() > -50) {
      //
      // }
    }
 } else {
   if(repulsorOn) {
//   if(gyro.getX() < 50 && gyro.getX() > -50) {
     print("OFF REPULSOR ");
//     repulsorLeft.turnOff();
     repulsorRight.turnOff();
//     stones.turnOn();
     repulsorOn = false;
     onRepulsorAngle = 0xFFFFFF;
   }
 }
// print("\n");
}
// resetFunc();  //call reset
// void(* resetFunc) (void) = 0;//declare reset function at address 0
