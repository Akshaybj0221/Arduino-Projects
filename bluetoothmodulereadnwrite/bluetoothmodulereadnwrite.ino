// physical cnonnection:
// D11 arduino  -  Rx of HC05
// D10 arduino  -  Tx of HC05


int ledpin=13;                     // led on D13 will show blink on / off
long previousMillis = 0;           // will store last time LED was updated

long interval = 1000;           // interval at which to blink (milliseconds)
int ledState = LOW;             // ledState used to set the LED
long Counter=0;                 // counter will increase every 1 second

void setup() {
  Serial.begin(9600);
  Serial.println("Bluetooth On please wait....");
  pinMode(ledpin,OUTPUT);
}

void loop() {

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;  
    Counter+=1;
  
    Serial.println(Counter);
  
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(ledpin, ledState);
  }
}
