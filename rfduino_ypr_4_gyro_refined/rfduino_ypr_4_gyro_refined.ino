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
    RFduinoBLE.send("Initializing I2C",16);
    mpu.initialize();
    RFduinoBLE.send("Testing connections",20);    
    if(mpu.testConnection()== 1)
    {
       RFduinoBLE.send("connection success",17);
    }
    else
    {
       RFduinoBLE.send("connection failed",17);
    }
    delay(500);                                                       // wait for ready

    devStatus = mpu.dmpInitialize();                                 // load and configure the DMP

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788);

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
   
       RFduinoBLE.send("Enabling DMP",12);
   
        mpu.setDMPEnabled(true);

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        
        dmpReady = true;
   
        packetSize = mpu.dmpGetFIFOPacketSize();                      // get expected DMP packet size for later comparison
     
    } else {
      

       RFduinoBLE.send("DMP init failed",17);                                   // ERROR!
                                                                                // 1 = initial memory load failed
                                                                                // 2 = DMP configuration updates failed
                                                                                // (if it's going to break, usually the code will be 1     
    }

    // configure AD0 for output
    
    for(int i=1; i<=4; i++)
    {
      pinMode(pin[i], OUTPUT);
    }
}

void RFduinoBLE_onConnect() {

  analogWrite(ad0, 255);
  delay(500);
  analogWrite(ad0, 0);

}

void RFduinoBLE_onDisconnect() {
  
  digitalWrite(ad0, LOW);                                               // turn all leds off on disconnect and stop pwm

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
  for (int i = 1; i <= 4; i++) 
  {
        switch (i) 
        {
            case 4:
                  digitalWrite(1, LOW);
                  digitalWrite(2, LOW);
                  digitalWrite(3, LOW);
                  digitalWrite(4, HIGH);
                  mpu.getFIFOBytes(fifoBuffer, packetSize);
                  while (fifoCount < packetSize)
                  fifoCount = mpu.getFIFOCount();
 
                  mpu.getFIFOBytes(fifoBuffer, packetSize);                               // read a packet from FIFO

                  fifoCount -= packetSize;                                               // track FIFO count here in case there is > 1 packet available

                  break;
            case 3:
                  digitalWrite(1, LOW);
                  digitalWrite(2, LOW);
                  digitalWrite(3, HIGH);
                  digitalWrite(4, LOW);
                  mpu.getFIFOBytes(fifoBuffer, packetSize);
                  while (fifoCount < packetSize)
                  fifoCount = mpu.getFIFOCount();
 
                  mpu.getFIFOBytes(fifoBuffer, packetSize);                               // read a packet from FIFO

                  fifoCount -= packetSize;                                                // track FIFO count here in case there is > 1 packet available

                  break;
            case 2:
                  digitalWrite(1, LOW);
                  digitalWrite(2, HIGH);
                  digitalWrite(3, LOW);
                  digitalWrite(4, LOW);
                  mpu.getFIFOBytes(fifoBuffer, packetSize);
                  while (fifoCount < packetSize)
                  fifoCount = mpu.getFIFOCount();
 
                  mpu.getFIFOBytes(fifoBuffer, packetSize);                               // read a packet from FIFO

                  fifoCount -= packetSize;                                               // track FIFO count here in case there is > 1 packet available

                  break;
             case 1:
                  digitalWrite(1, HIGH);
                  digitalWrite(2, LOW);
                  digitalWrite(3, LOW);
                  digitalWrite(4, LOW);
                  mpu.getFIFOBytes(fifoBuffer, packetSize);
                  while (fifoCount < packetSize)
                  fifoCount = mpu.getFIFOCount();
 
                  mpu.getFIFOBytes(fifoBuffer, packetSize);                               // read a packet from FIFO

                  fifoCount -= packetSize;                                               // track FIFO count here in case there is > 1 packet available

                  break;
  }

              #ifdef OUTPUT_READABLE_YAWPITCHROLL
              mpu.dmpGetQuaternion(&q, fifoBuffer);
              mpu.dmpGetGravity(&gravity, &q);
              mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
 
             RFduinoBLE.send("ypr   ",6);
             RFduinoBLE.send(i);
             RFduinoBLE.send(ypr[0] * 180/M_PI);
             RFduinoBLE.send(ypr[1] * 180/M_PI);
             RFduinoBLE.send(ypr[2] * 180/M_PI);
             #endif
  }
}  
