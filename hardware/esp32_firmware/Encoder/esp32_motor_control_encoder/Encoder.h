#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

// ==========================
// Pin Definitions
// ==========================
// GPIO34 → Right Motor Encoder
// GPIO35 → Left Motor Encoder

#define RIGHT_ENCODER_PIN 34   // GPIO34 – Right Motor Encoder Input
#define LEFT_ENCODER_PIN  35   // GPIO35 – Left Motor Encoder Input

// ==========================
// Function Prototypes
// ==========================

// Initialization
void encoder_init();

// Get ticks
int32_t getRightTicks();
int32_t getLeftTicks();

// Reset ticks
void resetRightTicks();
void resetLeftTicks();

#endif