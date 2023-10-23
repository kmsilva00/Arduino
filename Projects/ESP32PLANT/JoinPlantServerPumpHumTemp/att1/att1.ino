#include <DHT.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

//server
const char* ssid = "PANZER";
const char* password = "eucalipto";

//humidity temp
const int DHTPin = 2;
DHT dht(DHTPin, DHT11);

//relays for pumps
const int relayPins[] = { 12, 13, 14, 15, 16 };
const int numRelays = 5;  // Number of relays

//Soil sensors
const int numSensors = 4;
int soilPins[numSensors] = {4,2,0,15};  // Pins for the 4 soil sensors

// Calibration values for air and water capacitance for each sensor
float airCalibration[numSensors] = {0.0, 0.0, 0.0, 0.0};  // Default to 0% in air
float waterCalibration[numSensors] = {1000.0, 1000.0, 1000.0, 1000.0};  // Default to 100% in water

//Html of webserver
const char* serverIndex = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <h1 style="color:blue;">ESP32 Weather Station</h1>
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
        function displayCamera(){
          //pass
        }
    </script>
</head>
<body>
    <p>Temperature: %TEMP% ;</p>
    <p>Humidity: %HUM% %</p>
    <p>TO IMPLEMENT Conductivity: %CON% </p>
    <p>TO IMPLEMENT pH : %PH% </p>
    <button onclick="toggleRelay(1)">Toggle Relay Pump Water 1</button> <br>
    <p>Soil humidity1 : %SH1% %</p>
    <button onclick="toggleRelay(2)">Toggle Relay Pump Water 2</button> <br>
    <p>Soil humidity2 : %SH1% %</p>
    <button onclick="toggleRelay(3)">Toggle Relay Pump Water 3</button> <br>
    <p>Soil humidity3 : %SH2% %</p>
    <button onclick="toggleRelay(4)">Toggle Relay Pump Water 4</button> <br>
    <p>Soil humidity4 : %SH3% %</p>
    TO IMPLEMENT <button onclick="displayCamera()">Camera</button> <br> 
</body>
</html>
)rawliteral";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  //temp humidity begin
  dht.begin();

  //soil sensor begin
  for (int i = 0; i < numSensors; i++) {
    // Initialize sensor setup here
    pinMode(soilPins[i], INPUT);
  }
  

  //server begin
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
    html.replace("%SH0%",String(getSoilHumidity(0)));
    html.replace("%SH1%",String(getSoilHumidity(1)));
    html.replace("%SH2%",String(getSoilHumidity(2)));
    html.replace("%SH3%",String(getSoilHumidity(3)));
    request->send(200, "text/html", html);
  });

  // Handle relay toggling requests
  for (int i = 0; i < numRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);  // Initially set to LOW (off)
  }

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

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  for (int i = 0; i < numSensors; i++) {
    float shumidity = getSoilHumidity(i);
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" Soil Humidity: ");
    Serial.print(shumidity);
    Serial.println("%");
}
}
float getSoilHumidity(int sensorIndex) {
    float capacitanceValue = analogRead(soilPins[sensorIndex]);  // Replace with actual reading
    float mappedHumidity = map(capacitanceValue, airCalibration[sensorIndex], waterCalibration[sensorIndex], 0, 100);
    return constrain(mappedHumidity, 0, 100);  // Ensure the value is within the range [0, 100]
  }
