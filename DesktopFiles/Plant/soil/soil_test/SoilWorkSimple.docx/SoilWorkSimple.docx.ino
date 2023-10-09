const int SensorPin = 2;

void setup() {
  Serial.begin(9600);  // Set the baud rate to your preference
}

void loop() {
  int sensorValue = analogRead(SensorPin);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  delay(1000);  // Adjust the delay as needed to control the reading frequency
}
//4095 air