#include "DHT.h"

#define DPIN 4        //Pin to connect DHT sensor (GPIO number)
#define DTYPE DHT11   // Define DHT 11 or DHT22 sensor type

DHT dht(DPIN,DTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);
  
  float tc = dht.readTemperature(false);  //Read temperature in C
  float tf = dht.readTemperature(true);   //Read Temperature in F
  float hu = dht.readHumidity();          //Read Humidity

  Serial.println("||| --- |--- |--- |--- |   End of cycle   | --- | --- | --- | --- |");
  Serial.print("Temp: ");
  Serial.print(tc);
  Serial.print(" C, ");
  Serial.print(tf);
  Serial.print(" F, Hum: ");
  Serial.print(hu);
  Serial.println("%");
}
