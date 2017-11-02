#include <Wire.h>

#define MPU6050_ACCEL_XOUT_H       0x3B   // R  
#define MPU6050_PWR_MGMT_1         0x6B   // R/W
#define MPU6050_WHO_AM_I           0x75   // R
#define MPU6050_I2C_BYPASS_EN      0x37   //MPU6050_D1
#define MPU6050_USER_CTRL          0x6A

#define MPU6050_I2C_ADDRESS 0x69
#define MPU6050_I2C_ADDRESS_SLAVE 0x68

typedef union accel_t_gyro_union
{
  struct
  {
    uint8_t x_accel_h;
    uint8_t x_accel_l;
    uint8_t y_accel_h;
    uint8_t y_accel_l;
    uint8_t z_accel_h;
    uint8_t z_accel_l;
    uint8_t t_h;
    uint8_t t_l;
    uint8_t x_gyro_h;
    uint8_t x_gyro_l;
    uint8_t y_gyro_h;
    uint8_t y_gyro_l;
    uint8_t z_gyro_h;
    uint8_t z_gyro_l;
  } reg;
  struct 
  {
    int16_t x_accel;
    int16_t y_accel;
    int16_t z_accel;
    int16_t temperature;
    int16_t x_gyro;
    int16_t y_gyro;
    int16_t z_gyro;
  } value;
};
typedef union accel_t_gyro_union2
{
  struct
  {
    uint8_t x_accel_h2;
    uint8_t x_accel_l2;
    uint8_t y_accel_h2;
    uint8_t y_accel_l2;
    uint8_t z_accel_h2;
    uint8_t z_accel_l2;
    uint8_t t_h2;
    uint8_t t_l2;
    uint8_t x_gyro_h2;
    uint8_t x_gyro_l2;
    uint8_t y_gyro_h2;
    uint8_t y_gyro_l2;
    uint8_t z_gyro_h2;
    uint8_t z_gyro_l2;
  } reg;
  struct 
  {
    int16_t x_accel2;
    int16_t y_accel2;
    int16_t z_accel2;
    int16_t temperature2;
    int16_t x_gyro2;
    int16_t y_gyro2;
    int16_t z_gyro2;
  } value;
};

void setup()
{      
  int error;
  uint8_t c;

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  Serial.begin(9600);
  Serial.println(F("InvenSense MPU-6050"));
  Serial.println(F("June 2014"));

  Wire.begin();

  error = MPU6050_read (MPU6050_WHO_AM_I, &c, 1);
  Serial.print(F("WHO_AM_I : "));
  Serial.print(c,HEX);
  Serial.print(F(", error = "));
  Serial.println(error,DEC);

  error = MPU6050_read2 (MPU6050_WHO_AM_I, &c, 1);
  Serial.print(F("WHO_AM_I2 : "));
  Serial.print(c,HEX);
  Serial.print(F(", error = "));
  Serial.println(error,DEC);

  error = MPU6050_read (MPU6050_PWR_MGMT_1, &c, 1);
  Serial.print(F("PWR_MGMT_1 : "));
  Serial.print(c,BIN);
  Serial.print(F(", error = "));
  Serial.println(error,DEC);

  error = MPU6050_read2 (MPU6050_PWR_MGMT_1, &c, 1);
  Serial.print(F("PWR_MGMT_2 : "));
  Serial.print(c,BIN);
  Serial.print(F(", error = "));
  Serial.println(error,DEC);

  MPU6050_write_reg2 (MPU6050_PWR_MGMT_1, 0); 
  
  MPU6050_write_reg (MPU6050_PWR_MGMT_1, 0);                //112
  MPU6050_writeBit(MPU6050_I2C_BYPASS_EN, 1, 1);
  MPU6050_writeBit(MPU6050_USER_CTRL, 5, 0);
}


void loop()
{
  int error;
  double dT;
  accel_t_gyro_union accel_t_gyro;
  accel_t_gyro_union2 accel_t_gyro2;
  
  Serial.println(F(""));
  Serial.println(F("MPU-6050"));

  error = MPU6050_read (MPU6050_ACCEL_XOUT_H, (uint8_t *) &accel_t_gyro, sizeof(accel_t_gyro));
  error = MPU6050_read2 (MPU6050_ACCEL_XOUT_H, (uint8_t *) &accel_t_gyro2, sizeof(accel_t_gyro2));
  Serial.print(F("Read accel, temp and gyro, error = "));
  Serial.println(error,DEC);

  uint8_t swap;
  #define SWAP(x,y) swap = x; x = y; y = swap

  SWAP (accel_t_gyro.reg.x_accel_h, accel_t_gyro.reg.x_accel_l);
  SWAP (accel_t_gyro.reg.y_accel_h, accel_t_gyro.reg.y_accel_l);
  SWAP (accel_t_gyro.reg.z_accel_h, accel_t_gyro.reg.z_accel_l);
  SWAP (accel_t_gyro.reg.t_h, accel_t_gyro.reg.t_l);
  SWAP (accel_t_gyro.reg.x_gyro_h, accel_t_gyro.reg.x_gyro_l);
  SWAP (accel_t_gyro.reg.y_gyro_h, accel_t_gyro.reg.y_gyro_l);
  SWAP (accel_t_gyro.reg.z_gyro_h, accel_t_gyro.reg.z_gyro_l);

  SWAP (accel_t_gyro2.reg.x_accel_h2, accel_t_gyro2.reg.x_accel_l2);
  SWAP (accel_t_gyro2.reg.y_accel_h2, accel_t_gyro2.reg.y_accel_l2);
  SWAP (accel_t_gyro2.reg.z_accel_h2, accel_t_gyro2.reg.z_accel_l2);
  SWAP (accel_t_gyro2.reg.t_h2, accel_t_gyro2.reg.t_l2);
  SWAP (accel_t_gyro2.reg.x_gyro_h2, accel_t_gyro2.reg.x_gyro_l2);
  SWAP (accel_t_gyro2.reg.y_gyro_h2, accel_t_gyro2.reg.y_gyro_l2);
  SWAP (accel_t_gyro2.reg.z_gyro_h2, accel_t_gyro2.reg.z_gyro_l2);

  Serial.print(F("accel x,y,z: "));
  Serial.print(accel_t_gyro.value.x_accel, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro.value.y_accel, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro.value.z_accel, DEC);
  Serial.println(F(""));

  Serial.print(F("temperature: "));
  dT = ( (double) accel_t_gyro.value.temperature + 12412.0) / 340.0;
  Serial.print(dT, 3);
  Serial.print(F(" degrees Celsius"));
  Serial.println(F(""));

  Serial.print(F("gyro x,y,z : "));
  Serial.print(accel_t_gyro.value.x_gyro, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro.value.y_gyro, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro.value.z_gyro, DEC);
  Serial.print(F(", "));
  Serial.println(F(""));

  Serial.print(F("accel2 x,y,z: "));
  Serial.print(accel_t_gyro2.value.x_accel2, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro2.value.y_accel2, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro2.value.z_accel2, DEC);
  Serial.println(F(""));

  Serial.print(F("temperature2: "));
  dT = ( (double) accel_t_gyro2.value.temperature2 + 12412.0) / 340.0;
  Serial.print(dT, 3);
  Serial.print(F(" degrees Celsius"));
  Serial.println(F(""));

  Serial.print(F("gyro2 x,y,z : "));
  Serial.print(accel_t_gyro2.value.x_gyro2, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro2.value.y_gyro2, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro2.value.z_gyro2, DEC);
  Serial.print(F(", "));
  Serial.println(F(""));
 
  delay(1000);
}

int MPU6050_read(int start, uint8_t *buffer, int size)
{
  int i, n, error;

  Wire.beginTransmission(MPU6050_I2C_ADDRESS);
  n = Wire.write(start);
  if (n != 1)
    return (-10);

  n = Wire.endTransmission(false);    // hold the I2C-bus
  if (n != 0)
    return (n);

  Wire.requestFrom(MPU6050_I2C_ADDRESS, size, true);
  i = 0;
  while(Wire.available() && i<size)
  {
    buffer[i++]=Wire.read();
  }
  if ( i != size)
    return (-11);

  return (0);  // return : no error
}

int MPU6050_write(int start, const uint8_t *pData, int size)
{
  int n, error;

  Wire.beginTransmission(MPU6050_I2C_ADDRESS);
  n = Wire.write(start);        // write the start address
  if (n != 1)
    return (-20);

  n = Wire.write(pData, size);  // write data bytes
  if (n != size)
    return (-21);

  error = Wire.endTransmission(true); // release the I2C-bus
  if (error != 0)
    return (error);

  return (0);         // return : no error
}

int MPU6050_write_reg(int reg, uint8_t data)
{
  int error;

  error = MPU6050_write(reg, &data, 1);

  return (error);
}

int MPU6050_read2(int start, uint8_t *buffer, int size)
{
  int i, n, error;

  Wire.beginTransmission(MPU6050_I2C_ADDRESS_SLAVE);
  n = Wire.write(start);
  if (n != 1)
    return (-10);

  n = Wire.endTransmission(false);    // hold the I2C-bus
  if (n != 0)
    return (n);

  Wire.requestFrom(MPU6050_I2C_ADDRESS_SLAVE, size, true);
  i = 0;
  while(Wire.available() && i<size)
  {
    buffer[i++]=Wire.read();
  }
  if ( i != size)
    return (-11);

  return (0);  // return : no error
}

int MPU6050_write2(int start, const uint8_t *pData, int size)
{
  int n, error;

  Wire.beginTransmission(MPU6050_I2C_ADDRESS_SLAVE);
  n = Wire.write(start);        // write the start address
  if (n != 1)
    return (-20);

  n = Wire.write(pData, size);  // write data bytes
  if (n != size)
    return (-21);

  error = Wire.endTransmission(true); // release the I2C-bus
  if (error != 0)
    return (error);

  return (0);         // return : no error
}

int MPU6050_write_reg2(int reg, uint8_t data)
{
  int error;

  error = MPU6050_write2(reg, &data, 1);

  return (error);
}


void MPU6050_writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data) {
    uint8_t b;
    int x = MPU6050_read(regAddr, &b, 1);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    MPU6050_write_reg(regAddr, b);
}
