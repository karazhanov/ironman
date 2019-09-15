#include "KButton.h"
#include "KRgbLed.h"
#include "KServo.h"
#include "KGyro.h"
#include "UTILS.h"

 KButton repulsorButton(2);
 KButton stonesButton(3);
KButton servoButton(4);
KServo servo(10);
KGyro gyro;

CRGB stonesColors[] = {CRGB::Orange, CRGB::Red, CRGB::Purple, CRGB::Blue, CRGB::Green, CRGB::Yellow};

KRgbLed repulsorLeft(3, CRGB::Black, CRGB::WhiteSmoke);
KRgbLed repulsorRight(3, CRGB::Black, CRGB::White);
KRgbLed stones(6, CRGB::Black, stonesColors);
KRgbLed arcReactor(6, CRGB::Black, CRGB::WhiteSmoke);

bool KRgbLed::_needUpdate = false;

void setup() {
  #ifdef DEGUB_MODE
    Serial.begin(9600);
  #endif

  repulsorButton.init();
  stonesButton.init();
  servoButton.init();

  servo.init(55, 110);

  repulsorLeft.init<5>();
  repulsorRight.init<9>();

  stones.init<11>();
  arcReactor.init<6>();

  gyro.init();
  arcReactor.turnOn();

  KRgbLed::updateIfNeed();
}

void loop() {
  checkServo();
//    if(repulsorButton.isChange() && repulsorButton.isPressed()) servo.inc();
//
//  if(stonesButton.isChange() && stonesButton.isPressed()) servo.dec();
//
//  if(servoButton.isChange() && servoButton.isPressed()) {
//    Serial.println(servo.getState());
//  }
//  delay(100);
 checkGyro();
 checkButton(stonesButton, stones);
 KRgbLed::updateIfNeed();
 delay(100);

}

inline void checkButton(KButton &b, KRgbLed &l) {
  if(b.isChange() && b.isPressed()) l.switchState();
}

 inline void checkServo() {
   if(servoButton.isChange() && servoButton.isPressed()) {
     if(servo.isOpen()) {
      servo.close();
     } else {
      servo.open();
     }
     delay(1000);
   }
 }

 inline void checkGyro() {
   static bool repulsorOn = false;
   static float onRepulsorAngle = 0xFFFFFF;
   gyro.checkState();
   print(F("#GYR:"));
   print(gyro.getX(), 2);
   print(F(","));
   print(gyro.getY(), 2);

   if(gyro.getY() < -60) {
     if(!repulsorOn) {
       print("ON REPULSOR ");
       repulsorLeft.turnOn();
       repulsorRight.turnOn();
//       stones.turnOff();
       repulsorOn = true;
       onRepulsorAngle = gyro.getX();
     } else {
 //      if(gyro.getX() < 50 && gyro.getX() > -50) {
 //        stones.turnOn();
 //        repulsorLeft.turnOff();
 //        repulsorRight.turnOff();
 //      } else {
 //        stones.turnOff();
 //        repulsorLeft.turnOn();
 //        repulsorRight.turnOn();
 //      }
     }
  } else {
    if(repulsorOn) {
      print("OFF REPULSOR ");
      repulsorLeft.turnOff();
      repulsorRight.turnOff();
//      stones.turnOff();
      repulsorOn = false;
      onRepulsorAngle = 0xFFFFFF;
    }
  }
  print("\n");
 }
// resetFunc();  //call reset
// void(* resetFunc) (void) = 0;//declare reset function at address 0
