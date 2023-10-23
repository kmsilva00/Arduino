#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Nidavellir";
const char* password = "Present";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://your-web-server-url");  // Replace with the URL of the web server you want to connect to

    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
    } else {
      Serial.println("Error on HTTP request");
    }

    http.end();
    delay(5000); // Wait for a few seconds before making the next request
  }
}
