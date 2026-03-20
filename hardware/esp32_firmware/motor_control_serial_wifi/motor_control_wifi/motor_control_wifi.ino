#include "esp32_udp.h"
#include "esp32_motor.h"


void setup() {
  // WIFI Credentials
  ssid = "home";
  password = "12345678900";
  
  Serial.begin(115200);

  // Initialize Wifi Communication via UDP Protocol
  initWiFi();

    // Begin UDP listening
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);

  // Initialize Mootrs
  initMotors(); // Initialize motor pins
  MOTOR_SPEED = 200;
}

void loop() {
  // Dummy encoder values
  encData.left_ticks = 100;
  encData.right_ticks = 30;
  encData.timestamp = millis();

  cmd = udp_receive_send();
  commandMotor(cmd.direction, cmd.pwm);


  delay(200);
}