#include <WiFi.h>

const char* ssid = "M_U_J";
const char* password = "ros2humble";

const char* hostname = "ros2-esp32-robot-";

// 🔹 Static IP Configuration
IPAddress local_IP(192, 168, 1, 200);   // choose unused IP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(192, 168, 1, 1);
IPAddress secondaryDNS(0, 0, 0, 0);



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
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(hostname);

  // Set static IP address for ESP32
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Static IP Config Failed!");
  }

  WiFi.onEvent(WiFiEventHandler);   // Register event handler
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  initWiFi();
}

// ================= LOOP =================
void loop() {

  // Non-blocking monitoring
  static unsigned long lastCheck = 0;

  if (millis() - lastCheck > 5000) {  // every 5 sec
    lastCheck = millis();

    Serial.print("Status: ");
    Serial.println(WiFi.status());

    Serial.print("RSSI: ");
    Serial.println(WiFi.RSSI());
  }
}