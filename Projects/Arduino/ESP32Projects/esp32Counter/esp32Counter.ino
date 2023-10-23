#include <Arduino.h>

// Define the analog pin connected to the pH sensor
const int phSensorPin = A0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Read the analog value from the pH sensor
  int sensorValue = analogRead(phSensorPin);

  // Convert the analog value to pH
  float pHValue = mapToPH(sensorValue);

  // Print the pH value to the Serial Monitor
  Serial.print("pH Value: ");
  Serial.println(pHValue, 2); // Print with 2 decimal places

  // Add a delay between readings
  delay(1000); // Adjust the delay as needed
}

float mapToPH(int sensorValue) {
  // Map the sensor values to pH values based on your observations.
  // This is a linear approximation and may not be accurate without calibration.
  // You should gather data by testing known pH solutions and adjust these values.

  // Adjust these mapping values based on your observations and calibrations.
  float pHValue;

  if (sensorValue < 100) {
    // Adjust these values to match your sensor's behavior.
    pHValue = map(sensorValue, 0, 100, 0.0, 4.0);
  } else if (sensorValue < 500) {
    // Adjust these values to match your sensor's behavior.
    pHValue = map(sensorValue, 100, 500, 4.0, 7.0);
  } else {
    // Adjust these values to match your sensor's behavior.
    pHValue = map(sensorValue, 500, 1023, 7.0, 14.0);
  }

  return pHValue;
}

