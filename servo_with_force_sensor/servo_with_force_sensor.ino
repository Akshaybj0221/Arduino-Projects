void setup() {
Serial.begin(9600);
}

void loop() {
  int FReading = analogRead(A0);
//  Serial.print("Force Reading: ");
//  Serial.println(FReading);
  delay(50);
  analogWrite(9,20);
  Serial.print("Servo Reading: ");
  Serial.println(FReading/4);
}
