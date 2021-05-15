#include <Servo.h>
// #include <ServoEasing.h> // TODO set up the easing lib
#include <Stepper.h>

#define pinX  A2
#define pinY  A3

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

// MPU6050 accelerometer; // TODO accelerometer

int servoPin = 3;
Servo servo;
// ServoEasing base_rotation, base_lift, middle_lift, grip;  //  TODO Create 4 servos for each joint

float movementX;
bool isConnected;  // TODO accelerometer connection

void setup() {
  Serial.begin(9600);
  Serial.println("Initialize sketch");

  accelerometer.initialize(); // Initialize accelerometer

  servo.attach(servoPin);

  // TODO Set up the base rotation

  myStepper.setSpeed(60);

  // do {
  //   isConnected = accelerometer.testConnection();  //  Test connection with accelerometer
  //   Serial.println("[!] Not connected.");

  // } while (!isConnected);

  // Serial.println("[*] Connected successfully.");
}

void loop() {
  float X = analogRead(pinX);
  float Y = analogRead(pinY);
  Serial.print(Y); // inspect the `Y` value

  if (Y > 600) {
    myStepper.step(128);
  }
  if (Y < 400) {
    myStepper.step(-128);
  }

  movementX = (float) (X/1024*180);

  servo.write(movementX);

  // TODO remove tests for deploy
  delay(100);
  //  Serial.println(accelerometer.testConnection());
}