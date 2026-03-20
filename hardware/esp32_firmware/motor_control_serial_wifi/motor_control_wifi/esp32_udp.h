#ifndef ESP32_UDP_H
#define ESP32_UDP_H

#include <WiFi.h>
#include <WiFiUdp.h>

// ----------------- CONFIG -----------------
extern const char* ssid;
extern const char* password;
extern const char* hostname;

// Static IP configuration
extern IPAddress local_IP;
extern IPAddress gateway;
extern IPAddress subnet;
extern IPAddress primaryDNS;
extern IPAddress secondaryDNS;

// UDP settings
extern IPAddress pcIP;
extern const uint16_t UDP_PORT;
extern WiFiUDP UDP;
extern char packet[256];

// ----------------- DATA STRUCTURES -----------------
struct EncoderData {
  int32_t left_ticks;
  int32_t right_ticks;
  uint32_t timestamp;
};

extern EncoderData encData;

// ----------------- FUNCTIONS -----------------
void initWiFi();
void udp_receive_send();

#endif