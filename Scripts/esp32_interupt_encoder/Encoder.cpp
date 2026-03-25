#include "Encoder.h"

// ==========================
// Global Variables (ISR shared)
// ==========================

volatile int32_t rightTicks = 0;   // Right Motor Tick Counter
volatile int32_t leftTicks  = 0;   // Left Motor Tick Counter

// ==========================
// Interrupt Service Routines
// ==========================

// GPIO34 → Right Motor Encoder
void IRAM_ATTR rightEncoderISR() {
    rightTicks++;
}

// GPIO35 → Left Motor Encoder
void IRAM_ATTR leftEncoderISR() {
    leftTicks++;
}

// ==========================
// Initialization Function
// ==========================

void encoder_init() {

    // Configure pins as input
    pinMode(RIGHT_ENCODER_PIN, INPUT);  // GPIO34 – Input only
    pinMode(LEFT_ENCODER_PIN, INPUT);   // GPIO35 – Input only

    // Attach interrupts
    attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_PIN), rightEncoderISR, RISING);
    attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_PIN), leftEncoderISR, RISING);
}

// ==========================
// Getter Functions
// ==========================

int32_t getRightTicks() {
    noInterrupts();
    int32_t temp = rightTicks;
    interrupts();
    return temp;
}

int32_t getLeftTicks() {
    noInterrupts();
    int32_t temp = leftTicks;
    interrupts();
    return temp;
}

// ==========================
// Reset Functions
// ==========================

void resetRightTicks() {
    noInterrupts();
    rightTicks = 0;
    interrupts();
}

void resetLeftTicks() {
    noInterrupts();
    leftTicks = 0;
    interrupts();
}