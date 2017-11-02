//DMP without INT and FIFO Overflow and 6 sensors connected n tested

#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"

#include "Wire.h"

MPU6050 mpu(0x68); // <-- use for AD0 high

#define OUTPUT_READABLE_YAWPITCHROLL

int pin[5];


bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
//uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
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
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    // verify connection
    Serial.println(F("Testing device connections..."));
   Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // wait for ready
    delay(500);
    
    while (Serial.available() && Serial.read()); // empty buffer again
    Serial.println("after delay and serial . read");
    // load and configure the DMP
    devStatus = mpu.dmpInitialize();
    Serial.println("after initialize");
    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
        Serial.println("before devstatus");
    
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
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
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

    // configure AD0 for output
    
    for(int i=12; i<=13; i++)
    {
      pinMode(pin[i], OUTPUT);
          Serial.println("void loop for enter");
    
    }
}


// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
  for (int i = 12; i <= 13; i++) {
        Serial.println("for loop enter");
    
    switch (i) {

        Serial.println("switch case enter");
        
      case 13:
        Serial.println("i at start of case 13:");
        Serial.println(i);    
        digitalWrite(8, LOW);    
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);        
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, HIGH);
      if (!dmpReady) return;
      
     // while (fifoCount < packetSize)
      Serial.println("fifocount comparison");

          mpu.getFIFOBytes(fifoBuffer, packetSize);
      
         while (fifoCount < packetSize)
         fifoCount = mpu.getFIFOCount();
  
          // read a packet from FIFO
          mpu.getFIFOBytes(fifoBuffer, packetSize);
          
          // track FIFO count here in case there is > 1 packet available
          // (this lets us immediately read more without waiting for an interrupt)
         fifoCount -= packetSize;
         break;
      case 12:
        Serial.println("i at start of case 12:");
        Serial.println(i);
               digitalWrite(8, LOW);    
               digitalWrite(9, LOW);    
               digitalWrite(10, LOW);
               digitalWrite(11, LOW);
               digitalWrite(12, HIGH);
               digitalWrite(13, LOW);

          if (!dmpReady) return;
      
          while (fifoCount < packetSize){
  
          mpu.getFIFOBytes(fifoBuffer, packetSize);
          
         while (fifoCount < packetSize)
         fifoCount = mpu.getFIFOCount();
  
          // read a packet from FIFO
          mpu.getFIFOBytes(fifoBuffer, packetSize);
          
          // track FIFO count here in case there is > 1 packet available
          // (this lets us immediately read more without waiting for an interrupt)
         fifoCount -= packetSize;
         
         break;
//        
//      case 11:
//        Serial.println("i at start of case 11:");
//        Serial.println(i);    
//               digitalWrite(8, LOW);    
//               digitalWrite(9, LOW);    
//               digitalWrite(10, LOW);
//               digitalWrite(11, HIGH);
//               digitalWrite(12, LOW);
//               digitalWrite(13, LOW);
//
//          if (!dmpReady) return;
//      
//          while (fifoCount < packetSize){
//  
//          mpu.getFIFOBytes(fifoBuffer, packetSize);
//          
//         while (fifoCount < packetSize)
//         fifoCount = mpu.getFIFOCount();
//  
//          // read a packet from FIFO
//          mpu.getFIFOBytes(fifoBuffer, packetSize);
//          
//          // track FIFO count here in case there is > 1 packet available
//          // (this lets us immediately read more without waiting for an interrupt)
//         fifoCount -= packetSize;
//         
//         }   break;
//       
//
//        case 10:
//        Serial.println("i at start of case 10:");
//        Serial.println(i);    
//        digitalWrite(8, LOW);    
//        digitalWrite(9, LOW);    
//        digitalWrite(10, HIGH);
//        digitalWrite(11, LOW);
//        digitalWrite(12, LOW);
//        digitalWrite(13, LOW);
//       // Wire.beginTransmission(MPU);
//       // Wire.write(0x6B);
//      //  Wire.write(0);
////        Wire.endTransmission(true);
////        Wire.beginTransmission(MPU);
////        Wire.write(0x3B);
////        Wire.endTransmission(false);
////        Wire.requestFrom(MPU, 14, true);
//  
//      if (!dmpReady) return;
//      
//      while (fifoCount < packetSize){
//  
//          mpu.getFIFOBytes(fifoBuffer, packetSize);
//      
//         while (fifoCount < packetSize)
//         fifoCount = mpu.getFIFOCount();
//  
//          // read a packet from FIFO
//          mpu.getFIFOBytes(fifoBuffer, packetSize);
//          
//          // track FIFO count here in case there is > 1 packet available
//          // (this lets us immediately read more without waiting for an interrupt)
//         fifoCount -= packetSize;
//      
//      }    break;
////      
////
////          
////              #ifdef OUTPUT_READABLE_YAWPITCHROLL
////              mpu.dmpGetQuaternion(&q, fifoBuffer);
////              mpu.dmpGetGravity(&gravity, &q);
////              mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
////              Serial.print("ypr\t");Serial.println(i);
////              Serial.print(ypr[0] * 180/M_PI);
////              Serial.print("\t");
////              Serial.print(ypr[1] * 180/M_PI);
////              Serial.print("\t");
////              Serial.println(ypr[2] * 180/M_PI);
////              #endif
////
//       case 9:
//        Serial.println("i at start of case 9:");
//        Serial.println(i);    
//        digitalWrite(8, LOW);    
//        digitalWrite(9, HIGH);    
//        digitalWrite(10, LOW);
//        digitalWrite(11, LOW);
//        digitalWrite(12, LOW);
//        digitalWrite(13, LOW);
//       // Wire.beginTransmission(MPU);
//       // Wire.write(0x6B);
//      //  Wire.write(0);
////        Wire.endTransmission(true);
////        Wire.beginTransmission(MPU);
////        Wire.write(0x3B);
////        Wire.endTransmission(false);
////        Wire.requestFrom(MPU, 14, true);
//  
//      if (!dmpReady) return;
//      
//      while (fifoCount < packetSize){
//  
//          mpu.getFIFOBytes(fifoBuffer, packetSize);
//      
//         while (fifoCount < packetSize)
//         fifoCount = mpu.getFIFOCount();
//  
//          // read a packet from FIFO
//          mpu.getFIFOBytes(fifoBuffer, packetSize);
//          
//          // track FIFO count here in case there is > 1 packet available
//          // (this lets us immediately read more without waiting for an interrupt)
//         fifoCount -= packetSize;
//      }    break;
//      
//       case 8:
//        Serial.println("i at start of case 8:");
//        Serial.println(i);    
//        digitalWrite(8, HIGH);    
//        digitalWrite(9, LOW);    
//        digitalWrite(10, LOW);
//        digitalWrite(11, LOW);
//        digitalWrite(12, LOW);
//        digitalWrite(13, LOW);
//       // Wire.beginTransmission(MPU);
//       // Wire.write(0x6B);
//      //  Wire.write(0);
////        Wire.endTransmission(true);
////        Wire.beginTransmission(MPU);
////        Wire.write(0x3B);
////        Wire.endTransmission(false);
////        Wire.requestFrom(MPU, 14, true);
//  
//      if (!dmpReady) return;
//      
//      while (fifoCount < packetSize){
//  
//          mpu.getFIFOBytes(fifoBuffer, packetSize);
//      
//         while (fifoCount < packetSize)
//         fifoCount = mpu.getFIFOCount();
//  
//          // read a packet from FIFO
//          mpu.getFIFOBytes(fifoBuffer, packetSize);
//          
//          // track FIFO count here in case there is > 1 packet available
//          // (this lets us immediately read more without waiting for an interrupt)
//         fifoCount -= packetSize;
//      }    break;

    }
    Serial.println("b4 display");
              #ifdef OUTPUT_READABLE_YAWPITCHROLL
              mpu.dmpGetQuaternion(&q, fifoBuffer);
              mpu.dmpGetGravity(&gravity, &q);
              mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
              Serial.print("ypr\t");Serial.println(i);
              Serial.print(ypr[0] * 180/M_PI);
              Serial.print("\t");
              Serial.print(ypr[1] * 180/M_PI);
              Serial.print("\t");
              Serial.println(ypr[2] * 180/M_PI);
              #endif
}
  }  }
