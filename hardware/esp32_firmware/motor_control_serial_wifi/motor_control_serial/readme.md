# ESP32 Motor Control Module

## 📌 Overview

This project implements a **modular motor control system** for ESP32, allowing motors to be controlled via serial commands. The code is designed to be **clean, reusable, and easy to integrate** into larger robotics projects.

It provides:

* Initialization of motor pins
* PWM-based speed control
* Directional control (Forward, Backward, Left, Right)
* Stop functionality
* Serial command interface for testing and debugging

---

## ⚙️ Features

* ✅ Modular design (`esp32_motor.h` and `esp32_motor.cpp`)
* ✅ Supports 2 DC motors with H-bridge driver
* ✅ PWM-based speed control
* ✅ Serial command interface (F, B, L, R, S)
* ✅ Clean `setup()` and `loop()` in main program
* ✅ Easy integration with other modules (e.g., WiFi/UDP)

---

## 🔌 Pin Configuration

| Motor   | Direction Pins     | PWM Pin   |
| ------- | ------------------ | --------- |
| Motor 1 | IN1 = 25, IN2 = 26 | PWM1 = 32 |
| Motor 2 | IN3 = 27, IN4 = 14 | PWM2 = 33 |

* These pins can be modified in `esp32_motor.cpp` to match your hardware setup.
* Ensure H-bridge or motor driver supports PWM input.

---

## 📡 Serial Command Interface

* Commands sent via serial control motor movement:

| Command | Action        |
| ------- | ------------- |
| F       | Move Forward  |
| B       | Move Backward |
| L       | Turn Left     |
| R       | Turn Right    |
| S       | Stop Motors   |

* Example usage: Send `F` to move forward. ESP32 prints back `Command Executed: F`.

---

## ⚡ PWM Speed Control

* Default motor speed is defined by `MOTOR_SPEED` (default: 155)
* PWM values can be set in `main.ino`:

```cpp
PWM1 = 150;
PWM2 = 150;
```

* Speed is applied using `analogWrite(PWMx, pwmValue);`.

---

## 🧩 Modular Functions

### `initMotors()`

Initializes motor direction and PWM pins and stops motors.

### `commandMotor(char cmd)`

Executes motor action based on a serial command.

### `stopMotors()`

Stops both motors immediately.

### `clampPWM(int value, int minVal, int maxVal)`

Ensures PWM values stay within safe bounds.


## 🚀 Future Improvements

* Integrate with sensor feedback for closed-loop control
* Add gradual acceleration/deceleration
* Support additional motor configurations
* Integrate with WiFi/UDP communication module for remote control

## Notes

* This code is compatible with **ESP32 core version 3.1.1**. For newer versions, the PWM functionality uses `ledcSetup` and `ledcAttachPin` instead of `analogWrite`.
* Motors are driven using the **L298 motor driver** and **B0 DIY motors**.
* Ensure motor driver power requirements are met.
* Use resistors if needed for sensors or signal conditioning.
* This phase focuses only on motor control; sensor integration will be done in later phases.