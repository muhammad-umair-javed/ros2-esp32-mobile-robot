#include <WiFi.h>

const char* ssid = "M_U_J";
const char* password = "ros2humble";


// ================= WIFI EVENT HANDLER =================
void WiFiEventHandler(WiFiEvent_t event) {

  switch(event) {

    case WIFI_EVENT_STA_START:
      Serial.println("WiFi Started");
      break;

    case WIFI_EVENT_STA_CONNECTED:
      Serial.println("Connected to AP");
      break;

    case IP_EVENT_STA_GOT_IP:
      Serial.print("Got IP: ");
      Serial.println(WiFi.localIP());
      break;

    case WIFI_EVENT_STA_DISCONNECTED:
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
  WiFi.onEvent(WiFiEventHandler);   // ✅ Register event handler
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