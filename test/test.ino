#include <Servo.h>
int store[5] ;
int pos = 0, x = 0, y = 0, temp = 0;

Servo myservo;

void setup()
{
  myservo.attach(9);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    temp = Serial.read();
    if (temp == 13) {
      Serial.print((store[0] - 48) * 100 + (store[1] - 48) * 10 + (store[2] - 48));
      exi((store[0] - 48) * 100 + (store[1] - 48) * 10 + (store[2] - 48));
      y = 0;
      store[3] = 0;
    }
    else {
      store[y] = temp;
      Serial.print(':');
      Serial.write(store[y]);
      Serial.print('|');
      y++;
    }
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
