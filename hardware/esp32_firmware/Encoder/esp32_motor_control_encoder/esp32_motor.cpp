#include "esp32_motor.h"

// =============================================================
//  PIN DEFINITIONS
// =============================================================

const int IN1  = 27;   // Motor A — direction
const int IN2  = 26;
const int IN3  = 25;   // Motor B — direction
const int IN4  = 33;

const int PWM1 = 14;   // Motor A — speed
const int PWM2 = 32;   // Motor B — speed

// =============================================================
//  SPEED
// =============================================================

int MOTOR_SPEED = 170;   // default speed (0–255)

// =============================================================
//  HELPERS
// =============================================================

static int clampPWM(int value) {
  if (value < 0)   return 0;
  if (value > 255) return 255;
  return value;
}

// =============================================================
//  INITIALIZATION
// =============================================================

void initMotors() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  stopMotors();   // always start in stopped state
}

// =============================================================
//  MOTOR COMMAND
//  direction: 'F' | 'B' | 'L' | 'R' | 'S'
//  pwm:        0–255
// =============================================================

void commandMotor(char direction, uint8_t pwm) {
  MOTOR_SPEED = clampPWM(pwm);
  direction   = toupper(direction);

  switch (direction) {

    case 'F':   // Forward — both motors forward
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
      break;

    case 'B':   // Backward — both motors reverse
      digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
      break;

    case 'L':   // Turn Left in-place — A reverse, B forward
      digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
      break;

    case 'R':   // Turn Right in-place — A forward, B reverse
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
      break;

    case 'S':
    default:    // Stop (unknown command also stops for safety)
      stopMotors();
      return;   // return early — don't apply PWM after stopping
  }

  analogWrite(PWM1, MOTOR_SPEED);
  analogWrite(PWM2, MOTOR_SPEED);
}

// =============================================================
//  STOP MOTORS
// =============================================================

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
}