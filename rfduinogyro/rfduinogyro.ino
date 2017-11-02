#include <RFduinoBLE.h>

int ad0 = 2;

void setup() {
  // setup the leds for output
  pinMode(ad0, OUTPUT);

  RFduinoBLE.advertisementData = "gyro";
  
  RFduinoBLE.begin();
}

void loop() {
  
  RFduino_ULPDelay(INFINITE);       // switch to lower power mode

}

void RFduinoBLE_onConnect() {

  analogWrite(ad0, 255);
  delay(500);
  analogWrite(ad0, 0);

}

void RFduinoBLE_onDisconnect() {
  
  digitalWrite(ad0, LOW);     // turn all leds off on disconnect and stop pwm

}

void RFduinoBLE_onReceive(char *data, int len) {
    
    digitalWrite(ad0, HIGH);
    uint8_t r = data[0];
    RFduinoBLE.send("value is",4);
    RFduinoBLE.sendInt(r);
    
}
