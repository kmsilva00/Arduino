#include <Servo.h>
#include <NewPing.h>
#include <SoftwareSerial.h>

NewPing sonar (10, 11, 300);

Servo myservo;

int pos = 0;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(7);
  Serial.begin(9600);
  delay(100);
  pinMode(13,OUTPUT);



}

void loop() {
  // put your main code here, to run repeatedly:

  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);
    digitalWrite(13,LOW);
    Serial.print("distance: ");
    Serial.println(sonar.ping_cm());
    delay(100);
    digitalWrite(13,HIGH);
    delay(100);
    
}
}
