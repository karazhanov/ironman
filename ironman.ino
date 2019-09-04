
#include "KButton.h"
#include "KRgbLed.h"
#include "KServo.h"
#include "KGyro.h"

//KButton repulsorButton(2);
//KButton stonesButton(3);
//KButton servoButton(4);
//KServo servo(10);
KGyro gyro;
// #define DEGUB_MODE

//CRGB stones[] = {CRGB::Red, CRGB::Blue, CRGB::Green};

//KRgbLed led1(6, 3, CRGB::Black, CRGB::Red);
//KRgbLed led2(6, 3, CRGB::Black, CRGB::Blue);

void setup() {
  Serial.begin(9600);
//  repulsorButton.init();
//  stonesButton.init();
//  servoButton.init();
//  servo.init(50, 103);
//  led1.init<6>();
//  led2.init<6>();
  gyro.init();
}




void loop() {
//  check(repulsorButton, led1);
//  check(stonesButton, led2);
//
//  if(servoButton.isChange()) {
//   if(servoButton.isPressed()) {
//    if(servo.isOpen()) {
//     servo.close();
//    } else {
//     servo.open();
//    }
//   }
//  }

  gyro.checkState();

  Serial.print(F("#GYR:"));
  Serial.print(gyro.getX(), 2);        //Gyroscope angle
  Serial.print(F(","));
  Serial.print(gyro.getY(), 2);

   if(gyro.getY() < -60) {
   Serial.print(" ");
   if(gyro.getX() < 50 && gyro.getX() > -50) {
     Serial.print("ON REPULSOR ");
   }
 } else {
   Serial.print(" ");
   if(gyro.getX() < 50 && gyro.getX() > -50) {
     Serial.print("OFF REPULSOR ");
   }
 }
 Serial.println("\n");
}

void check(KButton &b, KRgbLed &l) {
  if(b.isChange()) {
    if(b.isPressed()) {
      l.switchState();
    }
  }
}
