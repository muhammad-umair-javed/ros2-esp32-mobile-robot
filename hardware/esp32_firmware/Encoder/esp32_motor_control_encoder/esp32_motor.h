#ifndef ESP32_MOTOR_H
#define ESP32_MOTOR_H

#include <Arduino.h>

// =============================================================
//  PIN DECLARATIONS (defined in esp32_motor.cpp)
// =============================================================

extern const int IN1;    // Motor A direction pin 1
extern const int IN2;    // Motor A direction pin 2
extern const int IN3;    // Motor B direction pin 1
extern const int IN4;    // Motor B direction pin 2

extern const int PWM1;   // Motor A PWM pin
extern const int PWM2;   // Motor B PWM pin

// =============================================================
//  SPEED (defined in esp32_motor.cpp)
// =============================================================

extern int MOTOR_SPEED;  // default drive speed (0–255)

// =============================================================
//  FUNCTION DECLARATIONS
// =============================================================

void initMotors();

// direction: 'F' forward | 'B' backward | 'L' left | 'R' right | 'S' stop
void commandMotor(char direction, uint8_t pwm);

void stopMotors();

#endif // ESP32_MOTOR_H