#include "Encoder.h"

void setup() {
    Serial.begin(115200);

    encoder_init();

    Serial.println("Simple Modular Encoder System Started");
}

void loop() {
    int32_t right = getRightTicks();
    int32_t left  = getLeftTicks();

    Serial.print("Right Motor: ");
    Serial.print(right);
    Serial.print(" | Left Motor: ");
    Serial.println(left);

    delay(500);
}