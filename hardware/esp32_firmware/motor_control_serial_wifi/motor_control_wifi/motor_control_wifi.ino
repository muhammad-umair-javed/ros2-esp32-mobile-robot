#include <WiFi.h>

const char* ssid = "M_U_J";
const char* password = "ros2humble";

void initWiFi () {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  initWiFi();
  Serial.print("Status: ");
  Serial.println(WiFi.status());
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());

}

void loop() {
  if (WiFi.status() == WL_CONNECTION_LOST){
    // Preventive measures to be taken in case of Network Lost
    initWiFi();

  }

}