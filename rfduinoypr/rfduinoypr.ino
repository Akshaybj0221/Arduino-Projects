//DMP without INT and FIFO Overflow and 6 sensors connected n tested

#include <RFduinoBLE.h>

#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"

#include "Wire.h"

MPU6050 mpu(0x68); // <-- use for AD0 high

#define OUTPUT_READABLE_YAWPITCHROLL

int pin[15];

int ad0 = 2;

bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector


// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {

    Wire.beginOnPins(5,6);
  
    pinMode(ad0, OUTPUT);

    RFduinoBLE.advertisementData = "gyro";
  
    RFduinoBLE.begin();
   
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
     //   TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)

    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    
    #endif

//    Serial.begin(115200);
    //while (!Serial);
    //Serial.println(F("Initializing I2C devices..."));
    RFduinoBLE.send("Initializing I2C",16);
    mpu.initialize();
    // Serial.println(F("Testing device connections..."));
    RFduinoBLE.send("Testing connections",20);    
   // Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
    if(mpu.testConnection()== 1)
    {
       RFduinoBLE.send("connection success",17);
    }
    else
    {
       RFduinoBLE.send("connection failed",17);
    }
    // wait for ready
    delay(500);
    
  //  while (Serial.available() && Serial.read()); // empty buffer again
  //  Serial.println("after delay and serial . read");
    // load and configure the DMP
    devStatus = mpu.dmpInitialize();
 //   Serial.println("after initialize");
    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
   //     Serial.println(F("Enabling DMP..."));
   
       RFduinoBLE.send("Enabling DMP",12);
   
        mpu.setDMPEnabled(true);

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
    //    Serial.println(F("DMP ready! Waiting for first interrupt..."));
        
        dmpReady = true;

        // get expected DMP packet size for later comparison
        
        packetSize = mpu.dmpGetFIFOPacketSize();
     
     //   Serial.println(packetSize);
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
       RFduinoBLE.send("DMP init failed",17);
     //   Serial.print(F("DMP Initialization failed (code "));
       // Serial.print(devStatus);
        //Serial.println(F(")"));
    }

    // configure AD0 for output
    
    for(int i=3; i<=3; i++)
    {
      pinMode(pin[i], OUTPUT);
//          Serial.println("void loop for enter");
    
    }
}
void RFduinoBLE_onConnect() {

  analogWrite(ad0, 255);
  delay(500);
  analogWrite(ad0, 0);

}

void RFduinoBLE_onDisconnect() {
  
  digitalWrite(ad0, LOW);     // turn all leds off on disconnect and stop pwm

}

void RFduinoBLE_onReceive(char *data, int len) {
    
    digitalWrite(ad0, HIGH);
    uint8_t r = data[0];
    RFduinoBLE.send("value is",9);
    RFduinoBLE.sendInt(r);
    
}

// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() 
{
//  RFduinoBLE.send("In loop",9);
  for (int i = 3; i <= 3; i++) 
  {
        switch (i) 
        {
            case 3:
 //                 RFduinoBLE.send("in case",9);
//                  digitalWrite(6, LOW);    
//                  digitalWrite(7, LOW);    
//                  digitalWrite(8, LOW);    
//                  digitalWrite(9, LOW);
//                  digitalWrite(10, LOW);        
//                  digitalWrite(11, LOW);
//                  digitalWrite(12, LOW);
                  digitalWrite(3, HIGH);
  //                if (!dmpReady) return;
    //              RFduinoBLE.send("aftr dmp",15);
                  mpu.getFIFOBytes(fifoBuffer, packetSize);
                  while (fifoCount < packetSize)
                  fifoCount = mpu.getFIFOCount();
 
                  // read a packet from FIFO
                  mpu.getFIFOBytes(fifoBuffer, packetSize);
                  
                  // track FIFO count here in case there is > 1 packet available
                  // (this lets us immediately read more without waiting for an interrupt)
                  fifoCount -= packetSize;
                  break;
 }
     //digitalWrite(,255);   
             
              #ifdef OUTPUT_READABLE_YAWPITCHROLL
              mpu.dmpGetQuaternion(&q, fifoBuffer);
              mpu.dmpGetGravity(&gravity, &q);
              mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
  //            Serial.print("ypr\t");Serial.println(i);
  //            Serial.print(ypr[0] * 180/M_PI);
  //            Serial.print("\t");
  //            Serial.print(ypr[1] * 180/M_PI);
  //            Serial.print("\t");
  //            Serial.println(ypr[2] * 180/M_PI);
             RFduinoBLE.send("ypr   ",6);
             RFduinoBLE.send(i);
             RFduinoBLE.send(ypr[0] * 180/M_PI);
             RFduinoBLE.send(ypr[1] * 180/M_PI);
             RFduinoBLE.send(ypr[2] * 180/M_PI);
             #endif
  }
}  
