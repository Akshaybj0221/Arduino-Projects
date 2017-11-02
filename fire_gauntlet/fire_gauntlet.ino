int lefttmotor_p=4;
int lefttmotor_n=5;
int rightmotor_n=6;
int rightmotor_p=7;
int x=9;
int y=10;
int z=11;
int zero=282;

void setup()
{
  Serial.begin(9600);
  Serial.print(9);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  Serial.print("rockstar");
}

void one_inch()
{
  Serial.print("one inch");
  forward();
  delay(150);
  stopp();
  delay(200);
}

void forward()
{
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW); 
}

void stopp()
{
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW); 
}

void reverse()
{
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH); 
}

void sense()
{
  Serial.print("SENSE");
  int x=digitalRead(9);
  int y=digitalRead(10);
  int z=digitalRead(11);
  
 if(x==LOW && y==LOW && z==LOW)
 {
   forward();
   delay(50);
   stopp();
 }
 if(x==HIGH && y==HIGH && z==HIGH)
 {
   reverse();
   delay(50);
   stopp();
 }
}

void loop()
{
  int x=digitalRead(9);
  int y=digitalRead(10);
  int z=digitalRead(11);
  sense();
}
