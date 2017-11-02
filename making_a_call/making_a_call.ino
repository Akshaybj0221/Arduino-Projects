char phone_no[] = "9009009177";
void setup()
{
  Serial.begin(9600);  //Open Serial Connection at baudrate 9600
  delay(2000);

  Serial.print("ATD=\""); 
  Serial.print(phone_no);
  Serial.print("\"");
  Serial.print(26); 
  Serial.println("hello");
}
void loop()
{
  //for making call once
}
  
