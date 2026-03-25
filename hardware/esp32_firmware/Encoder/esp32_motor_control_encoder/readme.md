# ESP32 Encoder Module

## Overview

This project provides a modular encoder tick counting system for the ESP32 using interrupt-based pulse counting. The system is designed for a differential drive robot where separate encoders are used for the right and left motors.

The encoder signals are connected to ESP32 interrupt-capable input pins, and tick counts are updated inside Interrupt Service Routines (ISR) for accurate counting.

---

## Pin Assignment

| Motor               | ESP32 Pin |
| ------------------- | --------- |
| Right Motor Encoder | GPIO 34   |
| Left Motor Encoder  | GPIO 35   |

Note: GPIO34 and GPIO35 are input-only pins on the ESP32.

---

## File Structure

```
main.ino
encoder.h
encoder.cpp
README.md
```

---

## Module Description

### encoder.h

Contains:

* Pin definitions
* Function declarations
* Public interface for encoder initialization, tick reading, and reset

### encoder.cpp

Contains:

* Tick counter variables
* Interrupt Service Routines
* Encoder initialization function
* Functions to get and reset tick counts

### main.ino

Responsible for:

* Initializing the encoder module
* Reading right and left motor tick counts
* Using tick data for further processing (RPM, control, odometry, etc.)

---

## Working Principle

1. Motor encoder generates pulses while the wheel rotates.
2. Pulses are connected to ESP32 interrupt pins.
3. On every rising edge, an interrupt occurs.
4. The interrupt routine increments the tick counter.
5. The main program reads the tick values when needed.

Flow:

```
Encoder Pulse → Interrupt → Tick Counter → Main Program
```

---

## Summary

This module provides a clean and modular way to read encoder ticks for right and left motors using ESP32 interrupts. It can be used in robotics projects such as line fol
