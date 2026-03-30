#include "esp32_udp.h"

// =============================================================
//  CONFIGURATION
// =============================================================

char*       ssid     = "M_U_J";
char*       password = "ros2humble";
const char* hostname = "ros2-esp32-robot";

IPAddress local_IP(192, 168, 0, 200);
IPAddress gateway(192, 168, 0,   1);
IPAddress subnet(255, 255, 255,  0);
IPAddress primaryDNS(192, 168,   1, 1);
IPAddress secondaryDNS(0, 0,     0, 0);
IPAddress pcIP(0, 0, 0, 0);   // learned dynamically from first command
bool pcIPknown = false;        // flag — don't send data until we know where to send

// ── UDP Instances ─────────────────────────────────────────────
WiFiUDP UDP;        // receives commands
WiFiUDP UDP_SEND;   // sends encoder data

// ── Port Numbers ─────────────────────────────────────────────
const uint16_t CMD_PORT  = 4210;   // ESP32 listens for commands here
const uint16_t DATA_PORT = 4212;   // PC (ROS2 receiver) listens here

// ── Shared Data ───────────────────────────────────────────────
EncoderData    encData = {0, 0, 0};
ControlCommand cmd     = {'S', 0};

// ── Timing ───────────────────────────────────────────────────
unsigned long       lastCmdTime          = 0;
const unsigned long CMD_TIMEOUT_MS       = 1000;   // safety stop after 300 ms silence

unsigned long       lastDataSend         = 0;
const uint16_t      DATA_SEND_INTERVAL_MS = 50;   // send encoder data at 20 Hz

// =============================================================
//  WIFI EVENT HANDLER
// =============================================================

void WiFiEventHandler(WiFiEvent_t event) {
  switch (event) {
    case ARDUINO_EVENT_WIFI_STA_START:
      Serial.println("[WiFi] Started");
      break;

    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
      Serial.println("[WiFi] Connected to AP");
      break;

    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.print("[WiFi] IP Address: ");
      Serial.println(WiFi.localIP());
      Serial.print("[WiFi] MAC Address: ");
      Serial.println(WiFi.macAddress());
      break;

    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("[WiFi] Connection lost! Reconnecting...");
      WiFi.reconnect();
      break;

    default:
      break;
  }
}

// =============================================================
//  WIFI INIT
// =============================================================

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(hostname);

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("[WiFi] Static IP config failed!");
  }

  WiFi.onEvent(WiFiEventHandler);
  WiFi.begin(ssid, password);

  Serial.println("[WiFi] Connecting...");
}

// =============================================================
//  UDP — RECEIVE COMMAND
//  Parses "D,PWM\0" format e.g. "F,170"
//  Returns: true if a valid command was received
// =============================================================

bool udp_receive_cmd() {
  int packetSize = UDP.parsePacket();
  if (packetSize <= 0) return false;

  // ── Learn PC's IP from whoever sent the command ──────────────
  if (!pcIPknown) {
    pcIP     = UDP.remoteIP();   // grab sender's IP automatically
    pcIPknown = true;
    Serial.print("[UDP] PC IP learned: ");
    Serial.println(pcIP);
  }

  char packet[64] = {0};
  int  len        = UDP.read(packet, sizeof(packet) - 1);
  if (len <= 0) return false;
  packet[len] = '\0';

  char dir;
  int  pwmVal;
  if (sscanf(packet, "%c,%d", &dir, &pwmVal) == 2) {
    cmd.direction = toupper(dir);
    cmd.pwm       = (uint8_t)constrain(pwmVal, 0, 255);
    lastCmdTime   = millis();
    return true;
  }

  return false;
}
// =============================================================
//  UDP — SEND ENCODER DATA
//  Sends encData struct to PC:DATA_PORT at fixed interval
//  Flow: ESP32:4213 ──▶ PC:4212
// =============================================================
void udp_send_encoder_data() {
  if (!pcIPknown) return;   // ← don't send until we know the PC's IP
  if (millis() - lastDataSend < DATA_SEND_INTERVAL_MS) return;

  lastDataSend = millis();
  UDP_SEND.beginPacket(pcIP, DATA_PORT);
  UDP_SEND.write((uint8_t*)&encData, sizeof(encData));
  UDP_SEND.endPacket();
}