void setup() {
  Serial.begin(9600);
}

void loop() {
   int i = analogRead(A0);
   Serial.println(i);
}
