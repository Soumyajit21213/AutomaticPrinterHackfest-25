#include <WiFi.h>
#include "SPIFFS.h"
#include <WebServer.h>

// UPI Payment Details
#define UPI_PAYEE_ADDRESS    "7908056641@axl"
#define UPI_PAYEE_NAME       "Soumyajit Samanta"
#define UPI_AMOUNT           "10.00"
#define UPI_CURRENCY         "INR"
#define UPI_TRANSACTION_NOTE "Test Payment"

// WiFi credentials
const char* ssid     = "JARVIS";
const char* password = "yg5817m9";

// Web server on port 80
WebServer server(80);

// Generate UPI Payment URL
String generateUPIURL() {
  String upi = "upi://pay?pa=";
  upi += UPI_PAYEE_ADDRESS;
  upi += "&pn=";
  upi += UPI_PAYEE_NAME;
  upi += "&am=";
  upi += UPI_AMOUNT;
  upi += "&cu=";
  upi += UPI_CURRENCY;
  upi += "&tn=";
  upi += UPI_TRANSACTION_NOTE;
  return upi;
}

// Load and modify index.html
String loadAndInjectHTML(String upiUrl) {
  if (!SPIFFS.exists("/index.html")) {
    Serial.println("❌ index.html not found in SPIFFS");
    return "<h1>index.html not found</h1>";
  }

  File file = SPIFFS.open("/index.html", "r");
  if (!file || file.size() == 0) {
    Serial.println("❌ Failed to open index.html or file is empty");
    return "<h1>Error loading index.html</h1>";
  }

  String html = file.readString();
  file.close();

  // Debug file content
  Serial.println("✅ index.html loaded:");
  Serial.println(html);

  html.replace("%%UPIURL%%", upiUrl);
  html.replace("%%AMOUNT%%", UPI_AMOUNT);
  return html;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // WiFi
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("✅ Connected! IP: ");
  Serial.println(WiFi.localIP());

  // SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("❌ SPIFFS Mount Failed");
    return;
  }
  Serial.println("✅ SPIFFS Mounted");

  // List files
  Serial.println("📂 Files in SPIFFS:");
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while (file) {
    Serial.println(" - " + String(file.name()));
    file = root.openNextFile();
  }

  // Route to serve the QR page
  server.on("/", HTTP_GET, []() {
    String upiUrl = generateUPIURL();
    String html = loadAndInjectHTML(upiUrl);
    server.send(200, "text/html", html);
  });

  server.begin();
  Serial.println("✅ HTTP server started");
}

void loop() {
  server.handleClient();
}
