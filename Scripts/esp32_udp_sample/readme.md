# ESP32 UDP WiFi Communication Boilerplate

## 📌 Overview

This project implements a **modular communication framework** between an ESP32 and a host machine (e.g., ROS2 PC) using **WiFi + UDP protocol**.

The goal of this boilerplate is to establish:

* Reliable WiFi connection (with auto-reconnect)
* Static IP configuration for deterministic communication
* Modular bidirectional UDP communication
* Event-driven WiFi handling

This serves as a **foundation for mobile robot communication**, where commands and sensor data must be exchanged efficiently.

---

## ⚙️ Features

* ✅ WiFi Station Mode (ESP32 connects to router)
* ✅ Static IP configuration
* ✅ Event-based WiFi monitoring
* ✅ Modular UDP send & receive communication functions
* ✅ Non-blocking architecture
* ✅ Easy integration with main program (`setup()` & `loop()` remain clean)
* ✅ Basic rate control for packet transmission

---

## 🌐 Network Configuration

### ESP32 Configuration

```cpp
IPAddress local_IP(192, 168, 0, 200);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
```

* ESP32 is assigned a **static IP address** for stable communication
* Ensures ROS2 node or host machine can always reach the ESP32

---

### PC Configuration

```cpp
IPAddress pcIP(192, 168, 0, 111);
```

* This is the IP address of the host machine
* Used by ESP32 to send data back (e.g., encoder values)

---

## 📡 UDP Communication

### Port Configuration

```cpp
const uint16_t UDP_PORT = 4210;
```

* Both ESP32 and PC communicate using this port

---

### Data Flow

#### 📥 Receiving Data

* ESP32 listens for incoming UDP packets
* Incoming data is stored in a buffer (`packet`)
* Example use case: receiving velocity commands from PC

#### 📤 Sending Data

* ESP32 sends response data back to sender
* Uses:

```cpp
UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
UDP.write((uint8_t*)&encData, sizeof(encData));
UDP.endPacket();
```

* Ensures reply is sent to the correct client
* Data sending can be modular and called independently

---

### 🔁 Communication Frequency

* Transmission rate can be controlled using `millis()` for timing, e.g., 10 Hz
* Prevents network flooding

---

## 📶 WiFi Handling

### WiFi Mode

```cpp
WiFi.mode(WIFI_STA);
```

* ESP32 acts as a **client** connecting to a router

---

### Event-Based System

WiFi events are handled using:

```cpp
WiFi.onEvent(WiFiEventHandler);
```

Handled events include:

* Connection start
* Connection success
* IP assignment
* Disconnection

---

### Auto-Reconnect

```cpp
WiFi.reconnect();
```

* Automatically reconnects when connection is lost

---

## 🧠 Design Considerations

### Why UDP?

* Low latency communication
* Suitable for real-time robotics
* Matches ROS2 DDS communication style

### Limitations

* No guaranteed delivery
* Requires application-level safety mechanisms

---

## 🚀 Modular Design

* `esp32_udp.h` and `esp32_udp.cpp` encapsulate WiFi and UDP logic
* `initWiFi()` handles WiFi setup and event registration
* `udp_receive_send()` handles both receiving and sending data
* Main program can focus on higher-level logic like motor control or sensor reading
* Easy to extend with functions like `sendEncoderData()` or `setPCIP()`

---

## 🚀 Future Improvements

* Add command parsing (e.g., `cmd_vel`)
* Integrate motor control logic
* Implement watchdog / timeout safety
* Send encoder feedback continuously
* Add ROS2 bridge node

---

## 📚 Resources

* [https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/#3](https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/#3)
* [https://deepbluembedded.com/esp32-wifi-library-examples-tutorial-arduino/](https://deepbluembedded.com/esp32-wifi-library-examples-tutorial-arduino/)
* [https://siytek.com/esp8266-udp-send-receive/](https://siytek.com/esp8266-udp-send-receive/)
