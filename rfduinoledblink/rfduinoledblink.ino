int value[3];
int count=0;
int led=13;
int ledn=12;
int i=0;
int temp=0;
int n=0;

int flag=0;

void setup()
{
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(ledn,OUTPUT);
}

void execute()
{
   temp = Serial.read();
   value[i] = temp;
   Serial.println();
   Serial.print("value on position ");
   Serial.print(i);
   Serial.print("is:");
   Serial.print(value[i]);
   i++;
   value[i] = '\0';
   if(count==0)
   {
      if(value[n]==111)
        {
           Serial.println("o enter");
           count++;       
           if(value[n+1] == 110)
           {
               Serial.println("n enter");
               i++;
               value[i]='\0';
               count++;
               if(count==2)
                {
                   digitalWrite(led,HIGH);
                   digitalWrite(ledn,LOW);
                }
                  i=0;
                flag++;
            }
            if(value[n+1] == 102)
             {
                 Serial.println("f1 enter");
                 i++;
                 count++;
                 temp=Serial.read();           
                 if(value[n+2] == 102)
                  {
                   Serial.println("f2 enter");
                   i++;
                   count++;
                   temp=Serial.read();
                   digitalWrite(led,LOW);
                   digitalWrite(ledn,LOW);
                   i=0;
                  }
              }
              if(flag>1)
              {
                  if(value[n]==111)
                   {
                     Serial.println("o enter");
                     count++;
                      if(value[n+2] == 110)
                        {
                           Serial.println("n enter");
                           i++;
                           value[i]='\0';
                           count++;
                           digitalWrite(led,HIGH);
                           digitalWrite(ledn,LOW);
                           i=0;
                           flag++;
                        }
                   if(value[n+2] == 102)
                    {
                      Serial.println("f1 enter");
                      i++;
                      count++;
                      temp=Serial.read();                    
                      if(value[n+3] == 102)
                       {
                         Serial.println("f2 enter");
                         i++;
                         count++;
                         temp=Serial.read();
                         digitalWrite(led,LOW);
                         digitalWrite(led,LOW);
                         i=0;
                       }
                     }
             }
         }    
      }
   }
}


void loop()
{
  if(Serial.available() >0)
  {    
       execute();    
  }
}
