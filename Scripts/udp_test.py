import socket
import struct

# ESP32 IP and port
ESP32_IP = "192.168.0.200"
ESP32_PORT = 4210

# Create UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind to receive data (important!)
sock.bind(("0.0.0.0", 4210))

print("Listening...")

while True:
    # 🔹 Send trigger packet to ESP32
    message = "hello esp32"
    sock.sendto(message.encode(), (ESP32_IP, ESP32_PORT))

    # 🔹 Receive response
    data, addr = sock.recvfrom(1024)

    print(f"\nReceived {len(data)} bytes from {addr}")

    # 🔥 Decode binary int array (2 integers)
    left, right, time = struct.unpack("iii", data)

    print(f"Left Encoder: {left}")
    print(f"Right Encoder: {right}")
    print(f"Hardware Timestamp: {time}")