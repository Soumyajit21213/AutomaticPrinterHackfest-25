#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "ESP32-WIFI";
const char* password = "12345678";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // Start Wi-Fi in AP mode
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Handle GET request with 3 parameters
  server.on("/print", HTTP_GET, [](AsyncWebServerRequest *request) {
    String paper = "", number = "", type = "";

    if (request->hasParam("paper")) {
      paper = request->getParam("paper")->value();
    }
    if (request->hasParam("number")) {
      number = request->getParam("number")->value();
    }
    if (request->hasParam("type")) {
      type = request->getParam("type")->value();
    }

    Serial.println("----- New Print Request -----");
    Serial.println("Paper Type: " + paper);
    Serial.println("Number: " + number);
    Serial.println("Printing Type: " + type);
    Serial.println("-----------------------------");

    request->send(200, "text/plain", "Received");
  });

  server.begin();
}
