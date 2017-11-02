#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // configure software serial port
 
void setup()
{
  mySerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);               
  //SIM900power();  
 // delay(20000);  // give time to log on to network. 
}
 
void SIM900power()
// software equivalent of pressing the GSM shield "power" button
{
  Serial.println("SIM Power");
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
}
 
void callSomeone()
{
  Serial.println("call");
  Serial.println("ATD + +919009009177;"); // dial US (212) 8675309
  delay(100);
  Serial.println();
  delay(30000);            // wait for 30 seconds...
  Serial.println("ATH");   // hang up
}
 
void loop()
{
   if (Serial.available())
   mySerial.write(Serial.read()); 
   if (mySerial.available())
   Serial.write(mySerial.read());
   callSomeone(); // call someone
  SIM900power();   // power off GSM shield
  do {} while (1); // do nothing
}
