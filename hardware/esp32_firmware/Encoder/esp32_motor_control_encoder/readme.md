# ESP32 Differential Drive Robot — Firmware

Firmware for an ESP32-based differential drive robot that communicates with a ROS2 host over WiFi using UDP. It receives motor commands from the host, drives two DC motors via an H-bridge, reads wheel encoder ticks using hardware interrupts, and streams encoder data back to the host in real time.

---

## Table of Contents

- [System Architecture](#system-architecture)
- [Hardware](#hardware)
- [File Structure](#file-structure)
- [Module Descriptions](#module-descriptions)
- [UDP Communication Protocol](#udp-communication-protocol)
- [Data Structures](#data-structures)
- [Pin Reference](#pin-reference)
- [Configuration](#configuration)
- [Setup & Flash Instructions](#setup--flash-instructions)
- [Safety Features](#safety-features)
- [ROS2 Interface](#ros2-interface)
- [Known Limitations](#known-limitations)

---

## System Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                        ROS2 Host (PC)                       │
│                                                             │
│   [UDP_SENDER node]          [UDP_RECEIVER node]            │
│   publishes: /car_cmd        subscribes: /enc_data          │
│   binds:  PC:4211            binds:  PC:4212                │
│       │                                  ▲                  │
│       │  "F,170"                         │  EncoderData     │
└───────┼──────────────────────────────────┼──────────────────┘
        │         WiFi (UDP)               │
        ▼                                  │
┌─────────────────────────────────────────────────────────────┐
│                     ESP32 (192.168.0.200)                   │
│                                                             │
│   UDP socket (CMD_PORT :4210)    UDP_SEND socket (:4213)    │
│   ┌─────────────────────┐        ┌──────────────────────┐   │
│   │   udp_receive_cmd() │        │ udp_send_encoder_    │   │
│   │   parse "D,PWM"     │        │ data() @ 20 Hz       │   │
│   └────────┬────────────┘        └──────────┬───────────┘   │
│            │                                │               │
│   commandMotor(dir, pwm)         encData ◄──┘               │
│            │                        ▲                       │
│   ┌────────▼────────┐    ┌──────────┴──────────┐            │
│   │   L298N H-Bridge │    │  Encoder Interrupts │            │
│   │   Motor A + B    │    │  GPIO34 / GPIO35    │            │
│   └─────────────────┘    └─────────────────────┘            │
└─────────────────────────────────────────────────────────────┘
```

---

## Hardware

| Component | Details |
|-----------|---------|
| Microcontroller | ESP32 (tested on ESP32-WROOM-32) |
| Motor Driver | L298N H-Bridge (or compatible) |
| Motors | 2× DC geared motors with single-channel encoders |
| Power | 7–12V for motors, 3.3V/5V regulated for ESP32 |
| Network | 2.4 GHz WiFi (802.11 b/g/n) |

---

## File Structure

```
esp32_robot_firmware/
│
├── esp32_motor_control_encoder.ino   # Main entry point — setup() and loop()
│
├── esp32_udp.h                       # UDP config, data structures, extern declarations
├── esp32_udp.cpp                     # WiFi init, command receive, encoder data send
│
├── esp32_motor.h                     # Motor pin externs and function declarations
├── esp32_motor.cpp                   # Motor initialization and drive logic
│
├── Encoder.h                         # Encoder pin definitions and function declarations
├── Encoder.cpp                       # ISR-based tick counting, interrupt-safe reads
│
└── README.md
```

---

## Module Descriptions

### `esp32_motor_control_encoder.ino` — Main

The top-level Arduino sketch. Runs at approximately 50 Hz (~20 ms loop delay).

Each loop iteration:
1. Reads left and right encoder ticks from interrupt counters
2. Pushes encoder data to the host via UDP (rate-limited to 20 Hz internally)
3. Checks for a new motor command via UDP
4. Applies the command, or triggers a safety stop if no command has arrived within `CMD_TIMEOUT_MS`

---

### `esp32_udp` — WiFi & UDP Communication

Handles all network logic.

**WiFi** connects to a configured access point using a static IP. The connection is event-driven via `WiFiEventHandler` — automatic reconnection is triggered on disconnect.

**Command receiving** (`udp_receive_cmd`) parses ASCII packets on `CMD_PORT` (`:4210`). On the first valid packet, the sender's IP is dynamically learned and stored as `pcIP` — this eliminates the need to hardcode the host's IP address, which is important when the host gets its IP via DHCP.

**Encoder sending** (`udp_send_encoder_data`) sends the 12-byte `EncoderData` binary struct to `pcIP:DATA_PORT` at a fixed 20 Hz rate using a dedicated socket (`UDP_SEND` on `:4213`). Using a separate socket for sending prevents interference with the receive buffer on `UDP`.

---

### `esp32_motor` — Motor Control

Controls two DC motors through an L298N H-bridge using 4 direction pins and 2 PWM pins. Accepts a direction character and a PWM value (0–255).

| Command | Behaviour |
|---------|-----------|
| `F` | Both motors forward |
| `B` | Both motors backward |
| `L` | Motor A reverse, Motor B forward (left pivot turn) |
| `R` | Motor A forward, Motor B reverse (right pivot turn) |
| `S` | Stop all motors |

Any unrecognised character also stops the motors for safety.

---

### `Encoder` — Interrupt-Based Tick Counting

Counts rising-edge pulses from single-channel wheel encoders on GPIO34 and GPIO35 (input-only pins on ESP32 — no internal pull-ups available). All ISR functions are placed in IRAM (`IRAM_ATTR`) for reliable execution during WiFi activity. All counter reads and resets use `noInterrupts()` / `interrupts()` guards to prevent data corruption from concurrent ISR writes.

---

## UDP Communication Protocol

### Port Map

```
Direction                 Source         Destination
─────────────────────────────────────────────────────────
PC  →  ESP32 (commands)   PC:4211    →   ESP32:4210
ESP32 →  PC  (enc data)   ESP32:4213 →   PC:4212
```

### Command Packet Format (PC → ESP32)

Encoded as an ASCII string:

```
"<DIR>,<PWM>\0"

Examples:
  "F,170"   → Forward  at PWM 170
  "B,200"   → Backward at PWM 200
  "L,150"   → Left     at PWM 150
  "R,150"   → Right    at PWM 150
  "S,0"     → Stop
```

### Encoder Data Packet Format (ESP32 → PC)

Binary struct, little-endian, 12 bytes total. Matches Python `struct.unpack('<iiI', data)`:

```
Offset   Size   Type      Field
──────────────────────────────────────────
0        4      int32     left_ticks
4        4      int32     right_ticks
8        4      uint32    timestamp (ms since boot)
```

---

## Data Structures

```cpp
// esp32_udp.h

#pragma pack(1)
struct EncoderData {
  int32_t  left_ticks;    // signed — supports reverse tick counting
  int32_t  right_ticks;
  uint32_t timestamp;     // millis() at time of read
};
#pragma pack()

struct ControlCommand {
  char    direction;   // 'F' | 'B' | 'L' | 'R' | 'S'
  uint8_t pwm;         // 0–255
};
```

`#pragma pack(1)` is critical — without it the compiler may insert padding bytes, making the struct a different size than what Python expects, causing silent data corruption.

---

## Pin Reference

### Motor Driver (L298N)

| Signal | ESP32 GPIO | Description |
|--------|-----------|-------------|
| IN1 | 27 | Motor A direction |
| IN2 | 26 | Motor A direction |
| IN3 | 25 | Motor B direction |
| IN4 | 33 | Motor B direction |
| PWM1 | 14 | Motor A speed |
| PWM2 | 32 | Motor B speed |

### Encoders

| Signal | ESP32 GPIO | Description |
|--------|-----------|-------------|
| Right encoder | 34 | Input-only pin, rising-edge interrupt |
| Left encoder | 35 | Input-only pin, rising-edge interrupt |

> **Note:** GPIO34 and GPIO35 have no internal pull-up resistors. If encoder signal lines are noisy or floating, add external 10 kΩ pull-up resistors to 3.3V.

---

## Configuration

All network configuration lives in `esp32_udp.cpp`:

```cpp
char* ssid         = "your_network_name";
char* password     = "your_password";

IPAddress local_IP(192, 168, 0, 200);   // ESP32 static IP
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

// pcIP is learned automatically from the first command packet.
// No need to set the host IP manually.

const uint16_t CMD_PORT  = 4210;   // ESP32 listens for commands
const uint16_t DATA_PORT = 4212;   // PC listens for encoder data
```

Timing constants:

```cpp
const unsigned long CMD_TIMEOUT_MS       = 300;   // safety stop threshold (ms)
const uint16_t      DATA_SEND_INTERVAL_MS = 50;   // encoder send rate (ms) = 20 Hz
```

---

## Setup & Flash Instructions

**Requirements:**
- Arduino IDE 2.x or PlatformIO
- ESP32 board package by Espressif (`esp32` ≥ 2.0)
- No additional libraries required (uses built-in `WiFi` and `WiFiUdp`)

**Steps:**

1. Clone the repository and open `esp32_motor_control_encoder.ino` in Arduino IDE
2. In `esp32_udp.cpp`, set `ssid` and `password` to match your network
3. Set `local_IP` to an available static IP on your subnet
4. Set `CMD_PORT` / `DATA_PORT` to match your ROS2 node configuration
5. Select your ESP32 board under **Tools → Board → ESP32 Arduino**
6. Select the correct COM/USB port
7. Upload — open Serial Monitor at `115200` baud to verify WiFi connection and IP assignment

**Expected Serial output on successful boot:**
```
[WiFi] Connecting...
[WiFi] IP Address: 192.168.0.200
[WiFi] MAC Address: XX:XX:XX:XX:XX:XX
Listening for commands on UDP port 4210
ESP32 Robot Ready!
```

**On first command received:**
```
[UDP] PC IP learned: 192.168.0.127
CMD → dir: F  pwm: 170
```

---

## Safety Features

**Command timeout:** If no valid command is received within `CMD_TIMEOUT_MS` (300 ms), `stopMotors()` is called automatically. This prevents the robot from running indefinitely if the host crashes or the WiFi link drops.

**PWM clamping:** All PWM values are constrained to `[0, 255]` via `constrain()` regardless of what the packet contains.

**Unknown command → stop:** Any unrecognised direction character in `commandMotor()` falls through to `stopMotors()` rather than leaving the motors in an undefined state.

**Dynamic IP learning:** The host IP is never hardcoded. It is learned from the UDP source address of the first valid command packet, making the firmware robust to DHCP address changes on the host without reflashing.

**WiFi auto-reconnect:** `WiFiEventHandler` calls `WiFi.reconnect()` on `ARDUINO_EVENT_WIFI_STA_DISCONNECTED`. The encoder send function guards against sending before `pcIP` is known (`if (!pcIPknown) return`).

---

## ROS2 Interface

This firmware is designed to work with two ROS2 nodes running on the host:

| Node | Topic | Direction | Port |
|------|-------|-----------|------|
| `UDP_SENDER` | `/car_cmd` (`std_msgs/String`) | PC → ESP32 | Send from `:4211` to ESP32`:4210` |
| `UDP_RECEIVER` | `/enc_data` (`custom_interfaces/EncoderData`) | ESP32 → PC | Listen on `:4212` |

The `custom_interfaces/EncoderData` message must define:

```
int32  left_ticks
int32  right_ticks
uint32 timestamp
```

---

## Known Limitations

**Single-channel encoders:** Only rising edges are counted, giving tick counts but no direction information. For full quadrature (direction-aware) encoding, a second signal wire per encoder and a 4-pin interrupt scheme would be needed.

**No encoder overflow handling:** `int32_t` tick counters will overflow after ~2.1 billion ticks. For long-running sessions, periodically call `resetRightTicks()` / `resetLeftTicks()` and handle cumulative counting on the ROS2 side.

**Same PWM for both motors:** Both motors receive the same PWM value. For a proper differential drive controller (e.g. closed-loop PID), the ROS2 side should compute per-wheel PWM targets and send them separately.

**2.4 GHz WiFi only:** The ESP32-WROOM-32 does not support 5 GHz networks.
