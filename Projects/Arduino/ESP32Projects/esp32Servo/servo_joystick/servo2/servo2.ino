#include <ESP32Servo.h>
#define PIN_SG90 22 // Output pin used

Servo sg90;

int JoyStick_X = 15; //x
int JoyStick_Y = 16; //y
int JoyStick_Z = 5; //key
  void setup() 
{
  sg90.setPeriodHertz(50); // PWM frequency for SG90
  sg90.attach(PIN_SG90, 500, 2400); // Minimum and maximum pulse width (in µs) to go from 0° to 180
  pinMode(JoyStick_Z, INPUT); 
  Serial.begin(9600); // 9600 bps
}
void loop() 
{
  int x,y,z;
  x=analogRead(JoyStick_X);
  y=analogRead(JoyStick_Y);
  z=digitalRead(JoyStick_Z);
  Serial.print(x ,DEC);
  Serial.print(",");
  Serial.print(y ,DEC);
  Serial.print(",");
  Serial.println(z ,DEC);
  delay(10);
  y = map(x,0,4095,180,0);
  if ( y < 1875 && y >1855){
    y = 1860;
  }
  sg90.write(y);
  

}