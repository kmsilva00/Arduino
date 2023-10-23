// #include <Arduino.h>

const int numSensors = 4;
int soilPins[numSensors] = {4,2,0,15};  // Pins for the 4 soil sensors


//13,12,14
// Calibration values for air and water capacitance for each sensor
float airCalibration[numSensors] = {0.0, 0.0, 0.0, 0.0};  // Default to 0% in air
float waterCalibration[numSensors] = {1000.0, 1000.0, 1000.0, 1000.0};  // Default to 100% in water

void setup() {
  // Initialize sensors and perform calibration if needed
  for (int i = 0; i < numSensors; i++) {
    // Initialize sensor setup here
    pinMode(soilPins[i], INPUT);
    // For simplicity, we'll just print the pins and calibration values
    Serial.begin(9600);
  }
}

// Function to get soil humidity for each sensor, mapped between 0 and 100
float getSoilHumidity(int sensorIndex) {
  // Assuming you read the capacitance values from the sensor
  // Replace this with your actual logic to read the capacitance
  float capacitanceValue = analogRead(soilPins[sensorIndex]);  // Replace with actual reading

  // Map the capacitance values between air and water calibration values
  float mappedHumidity = map(capacitanceValue, airCalibration[sensorIndex], waterCalibration[sensorIndex], 0, 100);
  return constrain(mappedHumidity, 0, 100);  // Ensure the value is within the range [0, 100]
}

void loop() {
  // Example of how to use the getSoilHumidity function
  for (int i = 0; i < numSensors; i++) {
    float humidity = getSoilHumidity(i);
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" Soil Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  }
  delay(1000);
}
