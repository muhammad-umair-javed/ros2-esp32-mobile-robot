#include "esp32_udp.h"

void setup() {
  Serial.begin(115200);

  initWiFi();

  // Begin UDP listening
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);
}

void loop() {
  // Dummy encoder values
  encData.left_ticks = 100;
  encData.right_ticks = 30;
  encData.timestamp = millis();

  udp_receive_send();
  delay(200);
}