// this feeds data into megasquirt over CAN bus
// MS3 setup under "CAN Receiving", "CAN ADC01", Std, identifier = 1, Size = B2U
// MS3 under Advanced Engine, "Generic Sensor Inputs", "CAN ADC01", Sensor 01, RAW

#include <SPI.h>      //Library for using SPI Communication
#include <Wire.h>     //this arduino board is fine using Wire, so we can just go ahead and unconditionally import this
#include <mcp2515.h>  //Library for using CAN Communication
#include <MPU6050.h>  //electronic cats library, downloaded from arduino library manager
#include <I2Cdev.h>   //also downloaded from arduino library manager

#define PRINTDEBUG

MCP2515 mcp2515(2);
struct can_frame canMsg;

MPU6050 accelgyro;
VectorInt16 aaReal;  // [x, y, z]

void setup() {
#ifdef PRINTDEBUG
  Serial.begin(115200);
  Serial.println("compiled with debug statements");
#endif
  Wire.begin();  //for the i2c protocol devices (the mpu6050 accelerometer board)
  SPI.begin();   //for the SPI protocol devices (the mcp2515 can board)


//initializing the can bus
#ifdef PRINTDEBUG
  Serial.println("Initializing SPI devices...");
#endif

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);  //Sets CAN at speed 500KBPS and clock to 8MHz
  mcp2515.setNormalMode();

// initialize the Accelerometer
#ifdef PRINTDEBUG
  Serial.println("Initializing I2C devices...");
#endif
  accelgyro.initialize(ACCEL_FS::A8G, GYRO_FS::G2000DPS); //will read up to 8g in both directions [-8g, 8g]
}

void loop() {
  aaReal.x = accelgyro.getAccelerationX();
  aaReal.y = accelgyro.getAccelerationY();
  aaReal.z = accelgyro.getAccelerationZ();
#ifdef PRINTDEBUG
  Serial.print("areal\t");
  Serial.print(aaReal.x);
  Serial.print("\t");
  Serial.print(aaReal.y);
  Serial.print("\t");
  Serial.println(aaReal.z);
#endif
  canMsg.can_id = 0x100;
  canMsg.can_dlc = 6;
  canMsg.data[0] = aaReal.x;
  canMsg.data[1] = aaReal.x >> 8;
  canMsg.data[2] = aaReal.y;
  canMsg.data[3] = aaReal.y >> 8;
  canMsg.data[4] = aaReal.z;
  canMsg.data[5] = aaReal.z >> 8;
  mcp2515.sendMessage(&canMsg);
  delay(1000);

}
