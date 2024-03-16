// this feeds data into megasquirt over CAN bus
// pot with +5, GND, signal to A0
// MS3 setup under "CAN Receiving", "CAN ADC01", Std, identifier = 1, Size = B2U
// MS3 under Advanced Engine, "Generic Sensor Inputs", "CAN ADC01", Sensor 01, RAW
// setup gauge to display Sensor 01


//Wire.h is sufficient for this arduino based board, so we can just unconditionally import this.

#include <SPI.h>          //Library for using SPI Communication
#include <Wire.h>         //this arduino board is fine using Wire, so we can just go ahead and unconditionally import this
#include <mcp2515.h>      //Library for using CAN Communication
#include <MPU6050.h>    //electronic cats library, downloaded from arduino library manager
#include <I2Cdev.h>     //also downloaded from arduino library manager


MCP2515 mcp2515(2);
struct can_frame canMsg;

MPU6050 accelgyro;
int16_t ax, ay, az, gx, gy, gz;

void setup() {
  while (!Serial) {
		Serial.begin(9600);
	}

  Wire.begin(); //for the i2c protocol devices (the mpu6050 accelerometer board)
  SPI.begin();  //for the SPI protocol devices (the mcp2515 can board)
	
  //initializing the can bus
	Serial.println("Initializing SPI devices...");
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();

  // initialize the Accelerometer
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
}

void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  canMsg.can_id = 0x001;
  canMsg.can_dlc = 3;
  canMsg.data[0] = ay >> 8;
  canMsg.data[1] = ax >> 8;
  canMsg.data[2] = az >> 8;
  canMsg.data[3] = gy >> 8;
  canMsg.data[4] = gx >> 8;
  canMsg.data[5] = gz >> 8;


  mcp2515.sendMessage(&canMsg);

}
