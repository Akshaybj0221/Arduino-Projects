#include <SoftwareSerial.h>
SoftwareSerial serial(2, 3);
void setup() {
  serial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if(serial.available())
    Serial.write(serial.read());
  
  if(Serial.available())
    serial.write(Serial.read());
}
