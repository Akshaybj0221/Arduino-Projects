int len=0;
String value;
int led=5;
int temp=0;
String a="aks";
int count=0;

void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}


void loop() 
{
    if(Serial.available()>0)
    {
      value = Serial.readString();
      len=value.length();
      if(value[0]=='o')
      {
          if(value[1]=='n')
          {
              if(len==3)
                  {
                    digitalWrite(led,HIGH);
                    Serial.println("HIGH");
                  }
          }
          if(value[1]=='f')
          {
                if(value[2]=='f')
                {
                  if(len==4)
                       {
                         digitalWrite(led,LOW);
                         Serial.println("LOW");
                       }
                }
          }
      }  
    }
} 
