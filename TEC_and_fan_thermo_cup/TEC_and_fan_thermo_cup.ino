void setup() {
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}

void loop() {
  int coolp= 8;
  int cooln= 9;
  int fanp= 10;
  int fann= 11;
  digitalWrite(coolp, HIGH);
  digitalWrite(cooln, LOW);
  digitalWrite(fanp, HIGH);
  digitalWrite(fann, LOW);
//  analogWrite(coolp, 255);
//  analogWrite(cooln, 0);
//  analogWrite(fanp, 255);
//  analogWrite(fann, 0);

//  delay(20000);
//  digitalWrite(coolp, LOW);
//  digitalWrite(cooln, LOW);
//  digitalWrite(fanp, LOW);
//  digitalWrite(fann, LOW);
//  delay(2000);
}
