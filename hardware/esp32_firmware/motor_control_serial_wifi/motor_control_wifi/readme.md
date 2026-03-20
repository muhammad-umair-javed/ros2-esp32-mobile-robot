# ESP32 UDP Motor Control System

## Overview

This project implements a WiFi-based motor control system using an ESP32 and UDP communication. A Python client sends control commands over the network, and the ESP32 receives these commands to drive motors accordingly.

## Features

* UDP-based wireless communication
* Real-time motor control
* Modular code structure (.ino, .h, .cpp separation)
* Expandable for ROS2 integration

## Project Structure

```
.
├── esp32_firmware/
│   ├── motor_control_wifi/
│   │   ├── motor_control_wifi.ino
│   │   ├── esp32_motor.h
│   │   ├── esp32_motor.cpp
│   │   ├── esp32_udp.h
│   │   ├── esp32_udp.cpp
├── Scripts/
│   ├── udp_test.py
```

## Hardware Requirements

* ESP32 Development Board
* Motor Driver (e.g., L298N)
* DC Motors
* Power Supply

## Software Requirements

* Arduino IDE (with ESP32 support)
* Python 3.x

## Setup Instructions

### 1. ESP32 Firmware

* Open `motor_control_wifi.ino` in Arduino IDE
* Set your WiFi credentials:

```cpp
ssid = "YOUR_WIFI_NAME";
password = "YOUR_WIFI_PASSWORD";
```

* Upload the code to ESP32

### 2. Python Client

* Update ESP32 IP address in script:

```python
ESP32_IP = "192.168.0.200"
ESP32_PORT = 4210
```

* Run the script:

```bash
python3 udp_control.py
```

## Communication Protocol

* UDP is used for low-latency communication
* Commands are sent as characters:

  * `F` → Forward
  * `B` → Backward
  * `L` → Left
  * `R` → Right
  * `S` → Stop

## Future Work

* Integration with ROS2 nodes
* Sensor feedback (encoders, IMU)
* Autonomous navigation


## 📚 Resources

* [https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/#3](https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/#3)
* [https://deepbluembedded.com/esp32-wifi-library-examples-tutorial-arduino/](https://deepbluembedded.com/esp32-wifi-library-examples-tutorial-arduino/)
* [https://siytek.com/esp8266-udp-send-receive/](https://siytek.com/esp8266-udp-send-receive/)
