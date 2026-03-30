// =============================================================
//  MAIN — ESP32 Differential Drive Robot
//  Handles: WiFi init, UDP communication, motors, encoders
// =============================================================

#include "Encoder.h"
#include "esp32_udp.h"
#include "esp32_motor.h"

// -----------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(500);

  // ── WiFi ──────────────────────────────────────────────────────
  initWiFi();

  // Wait until connected before starting UDP
  Serial.print("Waiting for WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  // ── UDP ───────────────────────────────────────────────────────
  UDP.begin(CMD_PORT);        // listen for commands  on :4210
  UDP_SEND.begin(4213);       // send encoder data    from :4213  →  PC:4212
  Serial.print("Listening for commands on UDP port ");
  Serial.println(CMD_PORT);

  // ── Motors & Encoders ─────────────────────────────────────────
  initMotors();
  encoder_init();

  Serial.println("ESP32 Robot Ready!");
}

// -----------------------------------------------------------------
void loop() {
  // 1. Read encoders into the shared struct
  encData.left_ticks  = getLeftTicks();
  encData.right_ticks = getRightTicks();
  encData.timestamp   = (uint32_t)millis();

  // 2. Push encoder data to PC at fixed rate (rate set in esp32_udp.cpp)
  udp_send_encoder_data();

  // 3. Check for new command; apply it or safety-stop on timeout
  if (udp_receive_cmd()) {
    commandMotor(cmd.direction, cmd.pwm);
    Serial.print("CMD → dir: "); Serial.print(cmd.direction);
    Serial.print("  pwm: ");     Serial.println(cmd.pwm);
  }
  else if (millis() - lastCmdTime > CMD_TIMEOUT_MS) {
    stopMotors();   // no command received within timeout window
  }

  // 4. Debug encoder output
  Serial.print("L: "); Serial.print(encData.left_ticks);
  Serial.print("  R: "); Serial.println(encData.right_ticks);

  delay(20);   // ~50 Hz main loop
}