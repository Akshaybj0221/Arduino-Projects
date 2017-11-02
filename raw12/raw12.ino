#include<Wire.h>

byte pins[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
const int MPU = 0x69;
int16_t AcX[15], AcY[15], AcZ[15], Tmp[15], GyX[15], GyY[15], GyZ[15];

void setup() {
  Wire.begin();

  for (int i = 0; i <= 11; i++)
    pinMode(pins[i], OUTPUT);

  Serial.begin(9600);
}
void loop() {
  for (int i = 0; i <= 11; i++) {
    switch (i) {
      case 0:
        digitalWrite(2, LOW);
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
      case 2:
        digitalWrite(12, LOW);
        digitalWrite(11, HIGH);
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
      case 3:
        digitalWrite(11, LOW);
        digitalWrite(10, HIGH);
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
      case 4:
        digitalWrite(10, LOW);
        digitalWrite(9, HIGH);
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
      case 5:
        digitalWrite(9, LOW);
        digitalWrite(8, HIGH);
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
      case 6:
        digitalWrite(8, LOW);
        digitalWrite(7, HIGH);
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
      case 7:
        digitalWrite(7, LOW);
        digitalWrite(6, HIGH);
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
      case 8:
        digitalWrite(6, LOW);
        digitalWrite(5, HIGH);
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
      case 9:
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);
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
      case 10:
        digitalWrite(4, LOW);
        digitalWrite(3, HIGH);
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
      case 11:
        digitalWrite(3, LOW);
        digitalWrite(2, HIGH);
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
