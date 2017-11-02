// physical cnonnection:
// D11 arduino  -  Rx of HC05
// D10 arduino  -  Tx of HC05


int ledpin=13;                     // led on D13 will show blink on / off
int BluetoothData;                 // the data given from Computer

void setup() {
  Serial.begin(9600);
  Serial.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin,OUTPUT);
}

void loop() {
    if (Serial.available())
    {
      BluetoothData=Serial.read();
      if(BluetoothData=='1')
        { 
          digitalWrite(ledpin,1);
          Serial.println("LED  On D13 ON ! ");
        }
      if (BluetoothData=='0')
       {
          digitalWrite(ledpin,0);
          Serial.println("LED  On D13 Off ! ");
        }
   }
delay(100);// prepare for next data ...
}
