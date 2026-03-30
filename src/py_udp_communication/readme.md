# py_udp_communication

A ROS 2 package that handles UDP communication between a host machine and an ESP32-based mobile robot. It contains two nodes: one for sending velocity commands to the ESP32, and one for receiving encoder feedback from it.

---

## Package Structure

```
py_udp_communication/
├── py_udp_communication/
│   ├── py_udp_sender.py       # Sends commands to ESP32 over UDP
│   └── py_udp_receiver.py     # Receives encoder data from ESP32 over UDP
├── package.xml
├── setup.py
└── README.md
```

---

## Nodes

### 1. `sender` — `py_udp_sender.py`

Subscribes to the `car_cmd` topic and forwards commands to the ESP32 via UDP.

| Property        | Value                        |
|-----------------|------------------------------|
| Node Name       | `UDP_SENDER`                 |
| Subscribed Topic | `car_cmd` (`std_msgs/String`) |
| ESP32 IP        | `192.168.0.200`              |
| Sends To        | ESP32 on port `4210`         |
| Binds On        | `0.0.0.0:4211`               |

**Behavior:**
- Listens on the `car_cmd` topic for string commands (e.g. `"FORWARD"`, `"STOP"`)
- Encodes and transmits each command as a UTF-8 UDP packet to the ESP32

---

### 2. `receiver` — `py_udp_receiver.py`

Receives encoder tick data from the ESP32 and publishes it as a ROS 2 topic.

| Property         | Value                                  |
|------------------|----------------------------------------|
| Node Name        | `UDP_RECEIVER`                         |
| Published Topic  | `enc_data` (`custom_interfaces/EncoderData`) |
| Listens On       | `0.0.0.0:4212`                         |
| Timer Period     | `20ms` (50 Hz)                         |
| Packet Format    | `struct '<iiI'` → `left_ticks`, `right_ticks`, `timestamp` |

**Behavior:**
- Polls the UDP socket every 20ms in a non-blocking manner
- Unpacks a 12-byte binary packet from the ESP32 using little-endian format (`<iiI`)
- On new data, updates and publishes an `EncoderData` message
- If no new data arrives, re-publishes the last known encoder values

---

## Dependencies

- `rclpy`
- `std_msgs`
- `custom_interfaces` — must be built first (provides the `EncoderData` message)

---

## UDP Port Map

| Direction              | Host Port | ESP32 Port |
|------------------------|-----------|------------|
| Host → ESP32 (commands) | `4211`   | `4210`     |
| ESP32 → Host (encoder)  | `4212`   | —          |

---

## Building

From your workspace root:

```bash
colcon build --packages-select custom_interfaces py_udp_communication
source install/setup.bash
```

> `custom_interfaces` must be built before `py_udp_communication` since the receiver depends on the `EncoderData` message type.

---

## Running

**Start the sender node:**
```bash
ros2 run py_udp_communication sender
```

**Start the receiver node:**
```bash
ros2 run py_udp_communication receiver
```

**Publish a test command manually:**
```bash
ros2 topic pub /car_cmd std_msgs/msg/String "data: 'FORWARD'"
```

**Monitor encoder data:**
```bash
ros2 topic echo /enc_data
```

---

## EncoderData Message (`custom_interfaces/EncoderData`)

| Field         | Type     | Description                        |
|---------------|----------|------------------------------------|
| `left_ticks`  | `int32`  | Left wheel encoder tick count      |
| `right_ticks` | `int32`  | Right wheel encoder tick count     |
| `timestamp`   | `uint32` | Timestamp from ESP32 (milliseconds)|

---

## Notes

- Make sure the ESP32 is connected to the same network as the host and reachable at `192.168.0.200`
- The receiver uses a non-blocking socket, so it will not crash if the ESP32 is temporarily offline — it simply holds the last received values
- Remember to `source install/setup.bash` after every `colcon build`
