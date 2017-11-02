/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
} 
 
void loop() 
{   
    int FReading = analogRead(A0);      //force sensor input reading
    delay(20);
    int NextRead = analogRead(A0);     //for getting an offset value 
    int offset=NextRead-FReading;      //for refinement of values

    // to make the negative value of offset into positive
    if(offset<0)
    {
      offset= offset * -1;
    }
//    Serial.print("Positive Offset: ");
//    Serial.println(offset); 
   
    //FOR CALIBRATION
    if(offset>50)
    {
     myservo.write(0);              // tell servo to go to position in variable 'pos' 
     if(FReading>550)
     {
       Serial.print("Force Reading: ");
       Serial.println(FReading);
       delay(50);
       int prevalue = FReading/4; 
       myservo.write(prevalue);              // tell servo to go to position in variable 'pos' 
       delay(100);                       // waits 15ms for the servo to reach the position  
    }
       else
    {
       Serial.print("Force Reading: ");
       Serial.println(FReading);
       delay(50);
       myservo.write(50);              // tell servo to go to position in variable 'pos' 
       delay(100);                       // waits 15ms for the servo to reach the position  
    }
   }
} 

