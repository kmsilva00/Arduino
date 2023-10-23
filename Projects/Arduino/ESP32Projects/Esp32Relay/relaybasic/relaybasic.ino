int Signal_Pin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(Signal_Pin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Signal_Pin, HIGH);
  delay(2500);
  digitalWrite(Signal_Pin, LOW);
  delay(2500);
}
