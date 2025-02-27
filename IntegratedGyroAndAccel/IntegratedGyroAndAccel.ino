<<<<<<< HEAD
// this feeds data into megasquirt over CAN bus
// MS3 setup under "CAN Receiving", "CAN ADC01", Std, identifier = 1, Size = B2U
// MS3 under Advanced Engine, "Generic Sensor Inputs", "CAN ADC01", Sensor 01, RAW
=======
>>>>>>> 1f36a88db655166ee3812ab6e4aec87f55b917de

#include <SPI.h>      //Library for using SPI Communication
#include <Wire.h>     //this arduino board is fine using Wire, so we can just go ahead and unconditionally import this
#include <mcp2515.h>  //Library for using CAN Communication
<<<<<<< HEAD
#include <MPU6050.h>  //electronic cats library, downloaded from arduino library manager
#include <I2Cdev.h>   //also downloaded from arduino library manager
=======
//#include <MPU6050.h>    //electronic cats library, downloaded from arduino library manager
#include <MPU6050_6Axis_MotionApps20.h>
#include <I2Cdev.h>  //also downloaded from arduino library manager
#include <MovingAverage.h> //custom made library (in the github)

#define PRINTDEBUG //define this if you want println statements for debugging. When in car you can comment this out.
#define SEND_INTERVAL 10 //counter will tick up every loop, canboard will send data every sendInterval loops
#define CAN_ID 0x100
#define POLLING_DELAY 10 //amount of milliseconds between accelerometer polls (POLLING_DELAY * SEND_INTERVAL = time between each sending of data)
>>>>>>> 1f36a88db655166ee3812ab6e4aec87f55b917de


MCP2515 mcp2515(2);
struct can_frame canMsg;

MPU6050 accelgyro;
VectorInt16 aaReal;  // [x, y, z]
<<<<<<< HEAD
=======
MovingAverage x(20), y(20), z(20); //each axis will have moving average of previous 20 values

int counter = 0; //when counter reaches SEND_INTERVAL, the data will be sent over can
>>>>>>> 1f36a88db655166ee3812ab6e4aec87f55b917de

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
<<<<<<< HEAD
  accelgyro.initialize(ACCEL_FS::A8G, GYRO_FS::G2000DPS); //will read up to 8g in both directions [-8g, 8g]
=======
  accelgyro.initialize(ACCEL_FS::A4G, GYRO_FS::G2000DPS); //measures up to 8g of range [-4g, 4g]
  accelgyro.CalibrateAccel(5);
>>>>>>> 1f36a88db655166ee3812ab6e4aec87f55b917de
}

void loop() {
  aaReal.x = x.getMovingAverage(accelgyro.getAccelerationX());
  aaReal.y = y.getMovingAverage(accelgyro.getAccelerationY());
  aaReal.z = z.getMovingAverage(accelgyro.getAccelerationZ());

#ifdef PRINTDEBUG
  Serial.print("areal\t");
  Serial.print(aaReal.x);
  Serial.print("\t");
  Serial.print(aaReal.y);
  Serial.print("\t");
  Serial.println(aaReal.z);
#endif
<<<<<<< HEAD
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
=======

  counter++;
  if (counter > SEND_INTERVAL) {
    canMsg.can_id = CAN_ID;
    canMsg.can_dlc = 6;
    canMsg.data[0] = aaReal.x >> 8;
    canMsg.data[1] = aaReal.x;
    canMsg.data[2] = aaReal.y >> 8;
    canMsg.data[3] = aaReal.y;
    canMsg.data[4] = aaReal.z >> 8;
    canMsg.data[5] = aaReal.z;

    mcp2515.sendMessage(&canMsg);
>>>>>>> 1f36a88db655166ee3812ab6e4aec87f55b917de

    counter = 0;
  }

  delay(POLLING_DELAY);
}
