void setup()
{
Serial.begin(9600);
}

void loop()
{
  delay(1200);
  Serial.print("AT");
  delay(1200);
  bool bOK = false;
  while (Serial.available() > 0)
  {
    char inChar = (char)Serial.read();
    bOK = true;
  }

if(bOK)
{
int index = 0;
Serial.println();
Serial.println("AT+CMGF=1"); // sets the SMS mode to text
delay(100);
delay(1200);
bool bOK = false;
while (Serial.available() > 0) {
//Serial.write(Serial.read());
char inChar = (char)Serial.read();
bOK = true;
}
if(bOK)
{
Serial.println();
Serial.println("AT+CMGS=\"+919009009177\"\r");
delay(1000);
Serial.print("A post is created "); // SMS body

delay(500);

Serial.write(0x1A);
Serial.write(0x0D);
Serial.write(0x0A);

}
}
}
