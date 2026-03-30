#ifndef ESP32_UDP_H
#define ESP32_UDP_H

#include <WiFi.h>
#include <WiFiUdp.h>

// =============================================================
//  CONFIGURATION — extern declarations (defined in esp32_udp.cpp)
// =============================================================

extern char*       ssid;
extern char*       password;
extern const char* hostname;

extern IPAddress local_IP;
extern IPAddress gateway;
extern IPAddress subnet;
extern IPAddress primaryDNS;
extern IPAddress secondaryDNS;
extern IPAddress pcIP;
extern bool      pcIPknown;

// ── UDP Instances ─────────────────────────────────────────────
extern WiFiUDP UDP;       // receives commands        on  CMD_PORT  (:4210)
extern WiFiUDP UDP_SEND;  // sends encoder data       to  PC:DATA_PORT (:4212)

// ── Port Numbers ─────────────────────────────────────────────
extern const uint16_t CMD_PORT;    // ESP32 listens here  (4210)
extern const uint16_t DATA_PORT;   // PC listens here     (4212)

// ── Timing ───────────────────────────────────────────────────
extern unsigned long       lastCmdTime;       // timestamp of last received command
extern const unsigned long CMD_TIMEOUT_MS;    // stop motors if silent > this (ms)

// =============================================================
//  DATA STRUCTURES
// =============================================================

// Must match Python: struct.unpack('<iiI', data)
//   i = int32_t  (signed 32-bit)
//   I = uint32_t (unsigned 32-bit)
#pragma pack(1)
struct EncoderData {
  int32_t  left_ticks;    // 'i'
  int32_t  right_ticks;   // 'i'
  uint32_t timestamp;     // 'I'  — millis()
};
#pragma pack()

struct ControlCommand {
  char    direction;   // 'F', 'B', 'L', 'R', 'S'
  uint8_t pwm;         // 0–255
};

extern EncoderData    encData;
extern ControlCommand cmd;


// =============================================================
//  FUNCTION DECLARATIONS
// =============================================================

void initWiFi();

// Returns true if a new valid command was parsed
bool udp_receive_cmd();

// Sends encData to PC at DATA_SEND_INTERVAL_MS rate
void udp_send_encoder_data();

#endif // ESP32_UDP_H