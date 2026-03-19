# ESP32 Robot – Phase 1: Motor Control via Serial Communication

## Overview

This is the first phase of the ESP32 robot project. This phase implement basic motor control using an ESP32 microcontroller. Motors are controlled through GPIO pins, with PWM signals managing speed and digital pins controlling direction. Serial communication is used to send commands to the ESP32. The motors are driven using an **L298 motor driver**, connected to **B0 DIY motors**.

## Hardware Connections

| Device | Function | ESP32 Pin |
| ------ | -------- | --------- |
| Motor  | IN1      | 25        |
| Motor  | IN2      | 26        |
| Motor  | IN3      | 27        |
| Motor  | IN4      | 14        |
| Motor  | PWM1     | 32        |
| Motor  | PWM2     | 33        |

### Pin Functions

* **IN1 – IN4:** Digital pins used to control motor direction through the L298 motor driver.
* **PWM1, PWM2:** PWM pins used to control motor speed.

## Serial Communication

Serial communication allows sending commands to the ESP32 to control motor behavior. Commands can be sent from a PC via USB or other UART devices.

**Example Commands:**

* `F` – Move forward
* `B` – Move backward
* `L` – Turn left
* `R` – Turn right
* `S` – Stop motors

## Notes

* This code is compatible with **ESP32 core version 3.1.1**. For newer versions, the PWM functionality uses `ledcSetup` and `ledcAttachPin` instead of `analogWrite`.
* Motors are driven using the **L298 motor driver** and **B0 DIY motors**.
* Ensure motor driver power requirements are met.
* Use resistors if needed for sensors or signal conditioning.
* This phase focuses only on motor control; sensor integration will be done in later phases.
