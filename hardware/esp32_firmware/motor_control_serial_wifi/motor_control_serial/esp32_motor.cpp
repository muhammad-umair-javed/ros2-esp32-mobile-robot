#include "esp32_motor.h"

// ----------------- PINS -----------------
const int IN1 = 25;
const int IN2 = 26;
const int IN3 = 27;
const int IN4 = 14;

const int PWM1 = 32;
const int PWM2 = 33;

// ----------------- SPEED -----------------
const int MOTOR_SPEED = 155;
int pwm1Value = MOTOR_SPEED;
int pwm2Value = MOTOR_SPEED;

// ----------------- INITIALIZATION -----------------
void initMotors() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);

  stopMotors(); // Ensure motors stopped initially
}

// ----------------- MOTOR COMMAND -----------------
void commandMotor(char cmd) {
  switch (cmd) {
    case 'F': // Forward
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

      analogWrite(PWM1, pwm1Value);
      analogWrite(PWM2, pwm2Value);
      break;

    case 'B': // Backward
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

      analogWrite(PWM1, pwm1Value);
      analogWrite(PWM2, pwm2Value);
      break;

    case 'L': // Turn Left
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

      analogWrite(PWM1, pwm1Value);
      analogWrite(PWM2, pwm2Value);
      break;

    case 'R': // Turn Right
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

      analogWrite(PWM1, pwm1Value);
      analogWrite(PWM2, pwm2Value);
      break;

    case 'S': // Stop
      stopMotors();
      break;

    default:
      Serial.println("Invalid command");
  }
  Serial.print("Command Executed: ");
  Serial.println(cmd);
}

// ----------------- STOP MOTORS -----------------
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  pwm1Value = 0;
  pwm2Value = 0;

  analogWrite(PWM1, pwm1Value);
  analogWrite(PWM2, pwm2Value);
}

// ----------------- CLAMP FUNCTION -----------------
int clampPWM(int value, int minVal, int maxVal) {
  if (value < minVal) return minVal;
  if (value > maxVal) return maxVal;
  return value;
}