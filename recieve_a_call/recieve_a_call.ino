void setup() 
{
  Serial.begin(9600);
  delay(200);
}

void loop() {
  char c;
 if(Serial.available())
 {
   c=Serial.read();
   if(c=='R')
   Serial.println("ATA");
   delay(5000);
   Serial.println("ATH");
 }
}
