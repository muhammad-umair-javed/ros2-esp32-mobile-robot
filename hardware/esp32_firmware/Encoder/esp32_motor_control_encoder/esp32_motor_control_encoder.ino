#include "Encoder.h"
#include "esp32_udp.h"
#include "esp32_motor.h"

void setup() {
  // WIFI Credentials
  ssid = "M_U_J";
  password = "ros2humble";
  
  Serial.begin(115200);

  // Initialize Wifi Communication via UDP Protocol
  initWiFi();

    // Begin UDP listening
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);

  // Initialize Mootrs
  initMotors(); // Initialize motor pins
  MOTOR_SPEED = 170;

  // Encoders Setup
  encoder_init();
  Serial.println("Simple Modular Encoder System Started");
}

void loop() {
  // Encoder Ticks Count
  encData.left_ticks = getLeftTicks();
  encData.right_ticks = getRightTicks();
  encData.timestamp = millis();

  cmd = udp_receive_send();
  commandMotor(cmd.direction, cmd.pwm);
  Serial.print("Right Motor: ");
  Serial.print(encData.right_ticks);
  Serial.print(" | Left Motor: ");
  Serial.println(encData.left_ticks);

  delay(50);

}










