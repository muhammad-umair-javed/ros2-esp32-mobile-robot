#include "esp32_udp.h"

// ----------------- CONFIG VALUES -----------------
char* ssid = "M_U_J";
char* password = "ros2humble";
const char* hostname = "ros2-esp32-robot-";

IPAddress local_IP(192, 168, 0, 200);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(192, 168, 1, 1);
IPAddress secondaryDNS(0, 0, 0, 0);

IPAddress pcIP(192, 168, 0, 111);
const uint16_t UDP_PORT = 4210;
WiFiUDP UDP;
char packet[256];

// Data for communication
EncoderData encData;
ControlCommand cmd;
// ================= WIFI EVENT HANDLER =================
void WiFiEventHandler(WiFiEvent_t event) {
  switch(event) {
    case ARDUINO_EVENT_WIFI_STA_START:
      Serial.println("WiFi Started");
      break;

    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
      Serial.println("Connected to AP");
      break;

    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.print("Got IP: ");
      Serial.println(WiFi.localIP());
      Serial.print("MAC Address: ");
      Serial.println(WiFi.macAddress());
      break;

    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("WiFi Lost Connection!");
      Serial.println("Reconnecting...");
      WiFi.reconnect();
      break;

    default:
      break;
  }
}

// ================= WIFI INIT =================
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(hostname);

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Static IP Config Failed!");
  }

  WiFi.onEvent(WiFiEventHandler);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");
}

// ================= UDP COMMUNICATION =================
ControlCommand udp_receive_send() {

  int packetSize = UDP.parsePacket();
  if (packetSize) {
    Serial.print("Received packet! Size: ");
    Serial.println(packetSize); 

    int len = UDP.read(packet, 255);
    if (len > 0) packet[len] = '\0';

    Serial.print("Packet received: ");
    Serial.println(packet);

    // 🔹 Example expected format: "F,150"
    char dir;
    int pwmVal;

    if (sscanf(packet, "%c,%d", &dir, &pwmVal) == 2) {
      cmd.direction = dir;
      cmd.pwm = constrain(pwmVal, 0, 255);
      Serial.print(cmd.direction);
      Serial.print(',');
      Serial.println(cmd.direction);
    }

    // Send back encoder data
    UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
    UDP.write((uint8_t*)&encData, sizeof(encData));
    UDP.endPacket();
  }

  return cmd;
}
