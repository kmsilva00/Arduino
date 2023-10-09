const int AirValue = 0;   //you need to replace this value with Value_1
const int WaterValue = 2280;  //you need to replace this value with Value_2
const int SensorPin = 2;
int soilMoistureValue = 0;
int soilmoisturepercent=0;
 
 
void setup() {
  Serial.begin(115200); // open serial port, set the baud rate to 9600 bps
}
 
 
void loop() 
{
soilMoistureValue = analogRead(SensorPin);  //put Sensor insert into soil
Serial.println(soilMoistureValue);
soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
if(soilmoisturepercent > 100)
{
  Serial.println("100 %");
  delay(250);
}
else if(soilmoisturepercent <0)
{
  Serial.println("0 %");
  delay(250);
}
else if(soilmoisturepercent >=0 && soilmoisturepercent <= 100)
{
  Serial.print(soilmoisturepercent);
  Serial.println("%");
  delay(250);
}  
}