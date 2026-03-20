#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "M_U_J";
const char* password = "ros2humble";
const char* hostname = "ros2-esp32-robot-";

// 🔹 Static IP Configuration
IPAddress local_IP(192, 168, 0, 200);   // ESP32 static IP
IPAddress gateway(192, 168, 0, 1);      // Your router
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(192, 168, 1, 1);
IPAddress secondaryDNS(0, 0, 0, 0);

// UDP Protocol
IPAddress pcIP(192, 168, 0, 111);
# define UDP_PORT 4210
WiFiUDP UDP;
char packet[256];
int reply[] = {100, 20};
int lastSend = 0;

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
      WiFi.reconnect();        // 🔁 Auto reconnect
      break;

    default:
      break;
  }
}

// ================= WIFI INIT =================
void initWiFi() {
  WiFi.mode(WIFI_STA);

  // Set custom Hostname
  WiFi.setHostname(hostname);

  // Set static IP address for ESP32
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Static IP Config Failed!");
  }

  WiFi.onEvent(WiFiEventHandler);   // Register event handler
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");
}

// UDP Communication Send and Receive Data
void udp_receive_send(){
  // If packet received...
  int packetSize = UDP.parsePacket();
  if (packetSize) {
    Serial.print("Received packet! Size: ");
    Serial.println(packetSize); 
    int len = UDP.read(packet, 255);
    if (len > 0)
    {
      packet[len] = '\0';
    }
    Serial.print("Packet received: ");
    Serial.println(packet);
  
    // Send at 10 Hz
  if (millis() - lastSend > 100) {
    lastSend = millis();

    UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
    UDP.write((uint8_t*)reply, sizeof(reply));
    UDP.endPacket();
  }
  }
}



// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  initWiFi();

  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);
}

// ================= LOOP =================
void loop() {

  udp_receive_send();
  


  
}