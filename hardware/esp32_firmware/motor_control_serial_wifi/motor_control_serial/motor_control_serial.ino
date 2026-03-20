#include "esp32_motor.h"


void setup() {
  Serial.begin(115200);
  initMotors(); // Initialize motor pins
  MOTOR_SPEED = 200;
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == '\n' || cmd == '\r') return;

    commandMotor(cmd);
    
  }
  delay(20);
}