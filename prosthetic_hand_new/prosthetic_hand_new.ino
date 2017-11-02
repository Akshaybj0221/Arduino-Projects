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
         if(FReading>750)
         {
             Serial.print(" 'If' Force Reading: ");
             Serial.println(FReading);
             delay(50);
             myservo.write(180);              // tell servo to go to position in variable 'pos' 
             delay(300);                       // waits 15ms for the servo to reach the position  
        }
        else
        {
             Serial.print(" 'else' Force Reading: ");
             Serial.println(FReading);
             delay(50);
             myservo.write(100);              // tell servo to go to position in variable 'pos' 
             delay(300);                       // waits 15ms for the servo to reach the position      
        }
   }
} 

