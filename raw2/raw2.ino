#include<Wire.h>
#include<math.h>
#include "Quaternion.h"
#include "XimuReceiver.h"

#define dmpPacketBuffer 0

byte pins[] = {13, 12, 2};
const int MPU = 0x69;
int16_t AcX[15], AcY[15], AcZ[15], Tmp[15], GyX[15], GyY[15], GyZ[15];
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

XimuReceiver ximuReceiver;

    if(ximuReceiver.isQuaternionGetReady()) {
        QuaternionStruct quaternionStruct = ximuReceiver.getQuaternion();
        Quaternion quaternion = Quaternion(quaternionStruct.w, quaternionStruct.x, quaternionStruct.y, quaternionStruct.z);
        EulerAnglesStruct eulerAnglesStruct = quaternion.getEulerAngles();
        Serial.print("roll = ");
        Serial.print(eulerAnglesStruct.roll);
        Serial.print(", pitch = ");
        Serial.print(eulerAnglesStruct.pitch);
        Serial.print(", yaw = ");
        Serial.print(eulerAnglesStruct.yaw);
        Serial.print("\r");
    }

/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
/*
 * quaternion.cpp
 * Copyright (C) Andrew Tridgell 2012
 *
 * This file is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *s
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include<AP_Math.h>

// return the rotation matrix equivalent for this quaternion
void Quaternion::rotation_matrix(Matrix3f &m)
{
        float q3q3 = q3 * q3;
        float q3q4 = q3 * q4;
        float q2q2 = q2 * q2;
        float q2q3 = q2 * q3;
        float q2q4 = q2 * q4;
        float q1q2 = q1 * q2;
        float q1q3 = q1 * q3;
        float q1q4 = q1 * q4;
    float q4q4 = q4 * q4;

    m.a.x = 1-2*(q3q3 + q4q4);
    m.a.y =   2*(q2q3 - q1q4);
    m.a.z =   2*(q2q4 + q1q3);
    m.b.x =   2*(q2q3 + q1q4);
    m.b.y = 1-2*(q2q2 + q4q4);
    m.b.z =   2*(q3q4 - q1q2);
    m.c.x =   2*(q2q4 - q1q3);
    m.c.y =   2*(q3q4 + q1q2);
    m.c.z = 1-2*(q2q2 + q3q3);
}

// convert a vector from earth to body frame
void Quaternion::earth_to_body(Vector3f &v)
{
    Matrix3f m;
    // we reverse z before and afterwards because of the differing
    // quaternion conventions from APM conventions.
    v.z = -v.z;
    rotation_matrix(m);
    v = m * v;
    v.z = -v.z;
}

// create a quaternion from Euler angles
void Quaternion::from_euler(float roll, float pitch, float yaw)
{
    float cr2 = cos(roll*0.5);
    float cp2 = cos(pitch*0.5);
    float cy2 = cos(yaw*0.5);
    float sr2 = sin(roll*0.5);
    float sp2 = sin(pitch*0.5);
    float sy2 = sin(yaw*0.5);

    q1 = cr2*cp2*cy2 + sr2*sp2*sy2;
    q2 = sr2*cp2*cy2 - cr2*sp2*sy2;
    q3 = cr2*sp2*cy2 + sr2*cp2*sy2;
    q4 = cr2*cp2*sy2 - sr2*sp2*cy2;
}



class Quaternion
{
public:
  float q1, q2, q3, q4;

  // constructor creates a quaternion equivalent
  // to roll=0, pitch=0, yaw=0
  Quaternion() { q1 = 1; q2 = q3 = q4 = 0; }

  // setting constructor
  Quaternion(const float _q1, const float _q2, const float _q3, const float _q4):
  q1(_q1), q2(_q2), q3(_q3), q4(_q4) {}

  // function call operator
  void operator ()(const float _q1, const float _q2, const float _q3, const float _q4)
  { q1 = _q1; q2 = _q2; q3 = _q3; q4 = _q4; }

  // check if any elements are NAN
  bool is_nan(void)
  {   return isnan(q1) || isnan(q2) || isnan(q3) || isnan(q4); }

  // return the rotation matrix equivalent for this quaternion
  void rotation_matrix(Matrix3f &m);

  // convert a vector from earth to body frame
  void earth_to_body(Vector3f &v);

    // create a quaternion from Euler angles
  void from_euler(float roll, float pitch, float yaw);

    // create eulers from a quaternion
  void to_euler(float *roll, float *pitch, float *yaw);
};
  
int dmpGetYawPitchRoll(float *data, Quaternion *q, VectorFloat *gravity) {
    // yaw: (about Z axis)
    data[0] = atan2(2*q -> x*q -> y - 2*q -> w*q -> z, 2*q -> w*q -> w + 2*q -> x*q -> x - 1);
    // pitch: (nose up/down, about Y axis)
    data[1] = atan(gravity -> x / sqrt(gravity -> y*gravity -> y + gravity -> z*gravity -> z));
    // roll: (tilt left/right, about X axis)
    data[2] = atan(gravity -> y / sqrt(gravity -> x*gravity -> x + gravity -> z*gravity -> z));
    return 0;
}

int dmpGetGravity(VectorFloat *v, Quaternion *q) {
    v -> x = 2 * (q -> x*q -> z - q -> w*q -> y);
    v -> y = 2 * (q -> w*q -> x + q -> y*q -> z);
    v -> z = q -> w*q -> w - q -> x*q -> x - q -> y*q -> y + q -> z*q -> z;
    return 0;
}

int dmpGetQuaternion(int32_t *data, const uint8_t* packet) {
    dmpGetYawPitchRoll();
    if (packet == 0) packet = dmpPacketBuffer;
    data[0] = ((packet[0] << 24) + (packet[1] << 16) + (packet[2] << 8) + packet[3]);
    data[1] = ((packet[4] << 24) + (packet[5] << 16) + (packet[6] << 8) + packet[7]);
    data[2] = ((packet[8] << 24) + (packet[9] << 16) + (packet[10] << 8) + packet[11]);
    data[3] = ((packet[12] << 24) + (packet[13] << 16) + (packet[14] << 8) + packet[15]);
    return 0;
}

void setup() {
  Wire.begin();

  for (int i = 0; i <= 1; i++)
    pinMode(pins[i], OUTPUT);

  Serial.begin(9600);
}
void loop() {
  for (int i = 0; i <= 1; i++) {
    switch (i) {
      case 0:
        digitalWrite(12, LOW);
        digitalWrite(13, HIGH);
        Wire.beginTransmission(MPU);
        Wire.write(0x6B);
        Wire.write(0);
        Wire.endTransmission(true);
        Wire.beginTransmission(MPU);
        Wire.write(0x3B);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU, 14, true);
        AcX[i] = Wire.read() << 8 | Wire.read();
        AcY[i] = Wire.read() << 8 | Wire.read();
        AcZ[i] = Wire.read() << 8 | Wire.read();
        Tmp[i] = Wire.read() << 8 | Wire.read();
        GyX[i] = Wire.read() << 8 | Wire.read();
        GyY[i] = Wire.read() << 8 | Wire.read();
        GyZ[i] = Wire.read() << 8 | Wire.read();
        
            #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Serial.print("ypr\t");
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(ypr[2] * 180/M_PI);
        
        #endif

        break;
        
      case 1:
        digitalWrite(13, LOW);
        digitalWrite(12, HIGH);
        Wire.beginTransmission(MPU);
        Wire.write(0x6B);
        Wire.write(0);
        Wire.endTransmission(true);
        Wire.beginTransmission(MPU);
        Wire.write(0x3B);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU, 14, true);
        AcX[i] = Wire.read() << 8 | Wire.read();
        AcY[i] = Wire.read() << 8 | Wire.read();
        AcZ[i] = Wire.read() << 8 | Wire.read();
        Tmp[i] = Wire.read() << 8 | Wire.read();
        GyX[i] = Wire.read() << 8 | Wire.read();
        GyY[i] = Wire.read() << 8 | Wire.read();
        GyZ[i] = Wire.read() << 8 | Wire.read();
        break;
    }
    Serial.print("AcX"); Serial.print(i); Serial.print(" = "); Serial.print(AcX[i]);
    Serial.print(" | AcY"); Serial.print(i); Serial.print(" = "); Serial.print(AcY[i]);
    Serial.print(" | AcZ"); Serial.print(i); Serial.print(" = "); Serial.print(AcZ[i]);
    Serial.print(" | Tmp"); Serial.print(i); Serial.print(" = "); Serial.print(Tmp[i] / 340.00 + 36.53); //equation for temperature in degrees C from datasheet
    Serial.print(" | GyX"); Serial.print(i); Serial.print(" = "); Serial.print(GyX[i]);
    Serial.print(" | GyY"); Serial.print(i); Serial.print(" = "); Serial.print(GyY[i]);
    Serial.print(" | GyZ"); Serial.print(i); Serial.print(" = "); Serial.println(GyZ[i]);
    delay(100);
  }
  Serial.println();
  Serial.println();
  delay(1000);
}
