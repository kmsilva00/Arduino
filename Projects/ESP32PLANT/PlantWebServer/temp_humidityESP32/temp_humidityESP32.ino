#include <DHT.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "PANZER";
const char* password = "eucalipto";

const int DHTPin = 2; // GPIO2

const int relayPins[] = { 12, 13, 14, 15, 16 };
const int numRelays = 5;  // Number of relays

DHT dht(DHTPin, DHT11);

const char* serverIndex = R"rawliteral(
<!DOCTYPE html>

<html>
    <head>
        <h1>ESP32 Weather Station</h1>
        <script>
            function toggleRelay(relayNumber) {
                // Send an HTTP request to toggle the relay based on the relay number
                fetch("/toggleRelay?relay=" + relayNumber)
                    .then(response => response.text())
                    .then(data => {
                        console.log("Relay toggled:", data);
                    })
                    .catch(error => console.error("Error toggling relay:", error));
                    console.log("Toggle Relay " + relayNumber);
                }
            
        </script>
        
    </head>
    <body>
        <p>Temperature: %TEMP% &#8451;</p>
        <p>Humidity: %HUM% %</p>
        <p>Conductivity: %CON% </p>
        <button onclick="toggleRelay(5)">Toggle Relay Acid Pump</button> <br>
        <p>pH : %PH% </p>
        <button onclick="toggleRelay(1)">Toggle Relay Pump Water 1</button> <br>
        <button onclick="toggleRelay(2)">Toggle Relay Pump Water 2</button> <br>
        <button onclick="toggleRelay(3)">Toggle Relay Pump Water 3</button> <br>
        <button onclick="toggleRelay(4)">Toggle Relay Pump Water 4</button> <br>
        <button>Camera</button> <br>
    </body>
    
</html>
)rawliteral";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Handle root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        String html = serverIndex;
        html.replace("%TEMP%", String(dht.readTemperature()));
        html.replace("%HUM%", String(dht.readHumidity()));
        html.replace("%CON%", String("Conductivity value")); // Replace with actual conductivity value
        html.replace("%PH%", String("pH value")); // Replace with actual pH value
        request->send(200, "text/html", html);
    });

    // Handle relay toggling requests
    server.on("/toggleRelay", HTTP_GET, [](AsyncWebServerRequest *request){
    String param = request->arg("relay");
    int relayNumber = param.toInt();

    // Check if the relay number is valid
    if (relayNumber >= 1 && relayNumber <= numRelays) {
        // Toggle the relay by changing its state from low to high or vice versa
        int relayPin = relayPins[relayNumber - 1];  // Relay numbers start from 1
        digitalWrite(relayPin, !digitalRead(relayPin));  // Toggle the pin state
        request->send(200, "text/plain", "Relay toggled");
        
    } else {
        request->send(400, "text/plain", "Invalid relay number");
    }
});
  // Start server
  server.begin();
}

void loop() {
  // Your DHT sensor reading code remains the same
  delay(2000);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  // float conductivity = sensor.read();
  // float pH = pHsensor.read()

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
}
