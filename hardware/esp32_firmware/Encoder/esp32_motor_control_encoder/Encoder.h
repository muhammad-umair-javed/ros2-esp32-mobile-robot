#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

// =============================================================
//  PIN DEFINITIONS
//  GPIO34 and GPIO35 are input-only pins on the ESP32
//  — no internal pull-up/pull-down available on these pins
// =============================================================

#define RIGHT_ENCODER_PIN  34
#define LEFT_ENCODER_PIN   35

// =============================================================
//  FUNCTION DECLARATIONS
// =============================================================

// Call once in setup() — attaches interrupts to encoder pins
void encoder_init();

// Returns current tick count (interrupt-safe read)
int32_t getRightTicks();
int32_t getLeftTicks();

// Resets tick counter to zero (interrupt-safe write)
void resetRightTicks();
void resetLeftTicks();

#endif // ENCODER_H