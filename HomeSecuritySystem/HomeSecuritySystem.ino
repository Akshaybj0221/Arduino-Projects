// physical cnonnection:
// D11 arduino  -  Rx of HC05
// D10 arduino  -  Tx of HC05



#include <SoftwareSerial.h>

SoftwareSerial serial(2, 3);      // for GSM module

SoftwareSerial Genotronex(10, 11); // RX, TX
int ledpin=13;                     // led on D13 will show blink on / off
char BluetoothData[100];                 // the data given from Computer
int i;
int condition=1;
int flag=0;
char string[100];
char data[] = "aks";


//GSM MODULE
char phone_no[] = "7835020049";


void setup() 
{
  //BLE
  
  Genotronex.begin(9600);
  Genotronex.println("Bluetooth On...");
  pinMode(ledpin,OUTPUT);
  delay(500);
  
}


void loop() 
{
    if (Genotronex.available())
    {
      while(condition)
      {
          int count=0;
          int temp=0;
          BluetoothData[i]=Genotronex.read();
          temp=BluetoothData[i];
          Genotronex.print("BluetoothData"); Genotronex.print(i); Genotronex.print("= "); Genotronex.print(BluetoothData[i]);
          Genotronex.println();
          Genotronex.println("flag= ");Genotronex.print(flag);
          Genotronex.println();
          i++;
          flag=i;
          count=temp+1;
          if(count==0)
          {
            BluetoothData[i]='\0';
            condition=0;
            flag--;
          }
      }
      condition=1;
      

      Genotronex.println("bluetooth data after for: ");
      for(i=0;i<=flag-1;i++)
      {      
        Genotronex.print(BluetoothData[i]);
        string[i]=BluetoothData[i];
        string[i+1]='\0';
      } 
        Genotronex.println();
        Genotronex.print("string is: ");  Genotronex.print(string);
        
      if(String(string) == "aks")
        { 
            //GSM
//              serial.print( "ATD+919009009177;");
            serial.print( "AT");
            delay(1200);
            serial.println();
            serial.println("AT+CMGF=1"); // sets the SMS mode to text
            delay(100);
            serial.println("AT+CMGS=\"9009009177\"");  
            delay(1000);
            serial.print(string); // SMS body
            delay(500);
            serial.write(26);

          //EXAMPLE
             
          digitalWrite(ledpin,1);
          Genotronex.println("LED  D13 ON ! ");

          for(i=0;i<=flag;i++)          //emptying string in the end
          {
            string[i]='\0';  
          }
        
        }
        
      else
       {
          digitalWrite(ledpin,0);
          Genotronex.println("LED  D13 Off ! ");

          for(i=0;i<=flag;i++)          //emptying string in the end
          {
            string[i]='\0';  
          }

       }
      
                 
       flag=0;
       i=0;
   }
 delay(100);// prepare for next data ...
}
