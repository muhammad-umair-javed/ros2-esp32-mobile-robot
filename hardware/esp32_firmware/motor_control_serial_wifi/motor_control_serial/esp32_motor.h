#ifndef ESP32_MOTOR_H
#define ESP32_MOTOR_H

#include <Arduino.h>

// ----------------- PINS -----------------
extern const int IN1;
extern const int IN2;
extern const int IN3;
extern const int IN4;
extern const int PWM1;
extern const int PWM2;

// ----------------- SPEED -----------------
extern int MOTOR_SPEED;

// ----------------- FUNCTIONS -----------------
void initMotors();                 // Setup motor pins
void commandMotor(char cmd);       // Execute motor command
void stopMotors();                 // Stop both motors
int clampPWM(int value, int minVal = 0, int maxVal = 255); // Clamp PWM value

#endif