#include <Servo.h>
#include "ServoEasing.h"
#include <Stepper.h>

#define pinX A2
#define pinY A3

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int servoPin1 = 4;
int servoPin2 = 2;
int servoPin3 = 3;
float incline ;
ServoEasing servo1;
ServoEasing servo2;
Servo servo3;

float movementX;

void changeIncline(ServoEasing engine) {
  float incline = engine.read();
  
  if (digitalRead(7) == 0 && incline < 180) {
    engine.write(++incline);
  } else if (digitalRead(6) == 0 && incline > 0) {
    engine.write(--incline);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initialize sketch");

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);

  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  myStepper.setSpeed(60);
}

void loop() {
  delay(20);

  float X = analogRead(pinX); // joystick axis X
  float Y = analogRead(pinY); // joystick axis Y

  if (digitalRead(12) == 0) { // btn pressed
    changeIncline(servo1);
  } else {
    changeIncline(servo2);
  }

  if (X > 650 && incline < 180) {
    servo3.write(++incline);
  } else if (X < 350 && incline > 0) {
    servo3.write(--incline);
  }
  
  if (Y > 650) {
    myStepper.step(32);
  } else if (Y < 350) {
    myStepper.step(-32);
  }
}
