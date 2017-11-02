#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
int x = 0;
void setup()
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop()
{
  int FReading = analogRead(A0);      //force sensor input reading
  Serial.println(FReading);
  if (FReading > 99)
  {
    Serial.print("Force Reading: ");
    Serial.println(FReading);
    delay(50);
    exi(179);            // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position
  }
  else
  {
    Serial.print("Force Reading: ");
    Serial.println(FReading);
    delay(50);
    exi(108);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position
  }
}

void exi(int val) {
  if (x - val > 0)
    for (int i = x; i >= val; i--) {
      myservo.write(i);
      delay(3);
    }
  else if (val - x > 0)
    for (int i = x; i <= val; i++) {
      myservo.write(i);
      delay(3);
    }
  x = val;
}

