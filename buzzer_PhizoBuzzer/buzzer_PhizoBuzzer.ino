//PHIZOBUZZER SEEDSTUDIO.COM

void setup() {
//  int 9;
  Serial.begin(9600);
  pinMode(9,OUTPUT);
}

void loop() {
  for(int i=0;i<=255;i++)
  {
   analogWrite(9,i);
   Serial.println(i);
  }
  
  for(int i=255;i>=0;i--)
  {
     Serial.println(i);
     analogWrite(9,i);
  }
}
