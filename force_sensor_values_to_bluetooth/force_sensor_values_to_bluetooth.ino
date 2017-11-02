#include <SoftwareSerial.h>


SoftwareSerial Genotronex(10, 11); // RX, TX

int FSR_Pin = A0;
int ledpin=13;                     // led on D13 will show blink on / off
long previousMillis = 0;           // will store last time LED was updated

long interval = 200;                // interval at which to blink (milliseconds)
int ledState = FSR_Pin;             // ledState used to set the LED
long Counter=0;                     // counter will increase every 1 second


void setup(){
  Genotronex.begin(9600);
  Genotronex.println("Bluetooth On please wait....");
  pinMode(FSR_Pin,INPUT);
}

void loop()
{
  int FSRReading = analogRead(FSR_Pin); 
  
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) 
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;  
    Counter+=1;
//    Genotronex.println(Counter);
    
    // send the reading of the pressure on the sensor:
      Genotronex.println(FSRReading);
  //  delay(250);
  }
  
}
