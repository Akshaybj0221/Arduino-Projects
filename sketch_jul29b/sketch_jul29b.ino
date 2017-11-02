#include <SoftwareSerial.h>

SoftwareSerial serial(2, 3);

void setup()
{
  serial.begin(9600);
  delay(1200);
  serial.print( "AT");
  delay(1200);
  serial.println();
  serial.println("AT+CMGF=1"); // sets the SMS mode to text
  delay(100);
  serial.println("AT+CMGS=\"9009009177\"");  
  delay(1000);
  serial.print("A post is created "); // SMS body
  
  delay(500);
  
  serial.write(26);

}

void loop()
{

}
