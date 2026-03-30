#include "Encoder.h"

// =============================================================
//  TICK COUNTERS
//  volatile — modified inside ISR, read in main context
// =============================================================

volatile int32_t rightTicks = 0;
volatile int32_t leftTicks  = 0;

// =============================================================
//  INTERRUPT SERVICE ROUTINES
//  IRAM_ATTR — must run from IRAM for reliable ISR execution
//  Counts one tick per RISING edge (single-channel encoder)
// =============================================================

void IRAM_ATTR rightEncoderISR() { rightTicks++; }
void IRAM_ATTR leftEncoderISR()  { leftTicks++;  }

// =============================================================
//  INITIALIZATION
// =============================================================

void encoder_init() {
  pinMode(RIGHT_ENCODER_PIN, INPUT);   // GPIO34/35 have no internal pull-up
  pinMode(LEFT_ENCODER_PIN,  INPUT);   // add external 10kΩ pull-up if signal is noisy

  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_PIN), rightEncoderISR, RISING);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_PIN),  leftEncoderISR,  RISING);
}

// =============================================================
//  TICK READERS — interrupt-safe
// =============================================================

int32_t getRightTicks() {
  noInterrupts();
  int32_t val = rightTicks;
  interrupts();
  return val;
}

int32_t getLeftTicks() {
  noInterrupts();
  int32_t val = leftTicks;
  interrupts();
  return val;
}

// =============================================================
//  TICK RESETTERS — interrupt-safe
// =============================================================

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