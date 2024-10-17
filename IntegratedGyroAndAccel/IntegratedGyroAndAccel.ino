// this feeds data into megasquirt over CAN bus
// pot with +5, GND, signal to A0
// MS3 setup under "CAN Receiving", "CAN ADC01", Std, identifier = 1, Size = B2U
// MS3 under Advanced Engine, "Generic Sensor Inputs", "CAN ADC01", Sensor 01, RAW
// setup gauge to display Sensor 01


//Wire.h is sufficient for this arduino based board, so we can just unconditionally import this.

#include <SPI.h>      //Library for using SPI Communication
#include <Wire.h>     //this arduino board is fine using Wire, so we can just go ahead and unconditionally import this
#include <mcp2515.h>  //Library for using CAN Communication
//#include <MPU6050.h>    //electronic cats library, downloaded from arduino library manager
#include <MPU6050_6Axis_MotionApps20.h>
#include <I2Cdev.h>  //also downloaded from arduino library manager

#define PRINTDEBUG

MCP2515 mcp2515(2);
struct can_frame canMsg;

MPU6050 accelgyro;
Quaternion q;        // [w, x, y, z]         quaternion container
VectorInt16 aa;      // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;  // [x, y, z]            gravity-free accel sensor measurements
VectorFloat gravity;
VectorFloat gyro;
int x, y, z, th;

uint8_t fifoBuffer[64];

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
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);  //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();

// initialize the Accelerometer
#ifdef PRINTDEBUG
  Serial.println("Initializing I2C devices...");
#endif
  accelgyro.initialize();
  accelgyro.dmpInitialize();
  accelgyro.CalibrateAccel(6);
  accelgyro.CalibrateGyro(6);
  accelgyro.setDMPEnabled(true);
}

void loop() {
  accelgyro.dmpGetCurrentFIFOPacket(fifoBuffer);
  accelgyro.dmpGetQuaternion(&q, fifoBuffer);
  accelgyro.dmpGetAccel(&aa, fifoBuffer);
  accelgyro.dmpGetGravity(&gravity, &q);
  accelgyro.dmpGetLinearAccel(&aaReal, &aa, &gravity);
#ifdef PRINTDEBUG
  Serial.print("areal\t");
  Serial.print(aaReal.x);
  Serial.print("\t");
  Serial.print(aaReal.y);
  Serial.print("\t");
  Serial.println(aaReal.z);
#endif
  canMsg.can_id = 0x100;
  canMsg.can_dlc = 3;
  canMsg.data[0] = aaReal.x >> 8;
  canMsg.data[1] = aaReal.y >> 8;
  canMsg.data[2] = aaReal.z >> 8;
  canMsg.data[3] = 0 >> 8;
  canMsg.data[4] = 0 >> 8;
  canMsg.data[5] = 0 >> 8;

  mcp2515.sendMessage(&canMsg);
}
