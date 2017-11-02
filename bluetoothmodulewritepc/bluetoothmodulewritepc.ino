// physical cnonnection:
// D11 arduino  -  Rx of HC05
// D10 arduino  -  Tx of HC05


#include <SoftwareSerial.h>// import the serial library

SoftwareSerial Genotronex(10, 11); // RX, TX
int ledpin=13;                     // led on D13 will show blink on / off
int BluetoothData;                 // the data given from Computer

void setup() {
  Genotronex.begin(9600);
  Genotronex.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin,OUTPUT);
}

void loop() {
    if (Genotronex.available())
    {
      BluetoothData=Genotronex.read();
      if(BluetoothData=='1')
        { 
          digitalWrite(ledpin,1);
          Genotronex.println("LED  On D13 ON ! ");
        }
      if (BluetoothData=='0')
       {
          digitalWrite(ledpin,0);
          Genotronex.println("LED  On D13 Off ! ");
        }
   }
delay(100);// prepare for next data ...
}
