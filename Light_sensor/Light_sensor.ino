//Light Sensor Seeds studio

void setup() {
//  int 9;
  Serial.begin(9600);
}

void loop() {
  int x=analogRead(A0);
  Serial.println(x);
  
}
