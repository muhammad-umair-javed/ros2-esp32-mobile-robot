// ESP32 Motor Control – Phase 1 (compatible with ESP32 core 3.1.1)
// Motors controlled via serial commands
// Pins:
// IN1 – 25, IN2 – 26, IN3 – 27, IN4 – 14
// PWM1 – 32, PWM2 – 33

const int IN1 = 25;
const int IN2 = 26;
const int IN3 = 27;
const int IN4 = 14;

const int PWM1 = 32;
const int PWM2 = 33;

const int MOTOR_SPEED = 155; // default speed
int pwm1Value = MOTOR_SPEED;
int pwm2Value = MOTOR_SPEED;

void setup() {
  Serial.begin(115200); // Start serial communication

  // Motor direction pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Motor PWM pins
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);

  stopMotors(); // Ensure motors are stopped at start
}

void loop() {
  if (pwm1Value == 0){
    pwm1Value = MOTOR_SPEED;
    pwm2Value = MOTOR_SPEED;
  }
  if (Serial.available()) {
    char command = Serial.read();
    
    // Ignore newline or carriage return characters
    if (command == '\n' || command == '\r') return;

    commandMotor(command);
    Serial.print("Command Executed: ");
    Serial.println(command);
  }
  delay(20);
}

void commandMotor(char cmd) {
  switch (cmd) {
    case 'F': // Forward
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

      // Increase speed gradually
      pwm1Value = clampPWM(pwm1Value + 20, 0, 255);
      pwm2Value = pwm1Value;
      analogWrite(PWM1, pwm1Value);
      analogWrite(PWM2, pwm2Value);
      break;

    case 'B': // Backward
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

      // Decrease speed gradually
      pwm1Value = clampPWM(pwm1Value - 20, 150, 255);
      pwm2Value = pwm1Value;
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
}

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

// Clamp a value between minVal and maxVal
int clampPWM(int value, int minVal, int maxVal) {
  if (value < minVal) return minVal;
  if (value > maxVal) return maxVal;
  return value;
}