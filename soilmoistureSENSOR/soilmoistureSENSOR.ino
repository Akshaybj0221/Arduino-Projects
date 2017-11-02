
void setup() {
  Serial.begin(9600);
}

void loop() {

  int sensorValue = analogRead(A5);
//  sensorValue=sensorValue*5;
  Serial.println(sensorValue);
  delay(1);

}
