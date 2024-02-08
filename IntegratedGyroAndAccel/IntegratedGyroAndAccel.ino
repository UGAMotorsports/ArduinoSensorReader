// this feeds data into megasquirt over CAN bus
// pot with +5, GND, signal to A0
// MS3 setup under "CAN Receiving", "CAN ADC01", Std, identifier = 1, Size = B2U
// MS3 under Advanced Engine, "Generic Sensor Inputs", "CAN ADC01", Sensor 01, RAW
// setup gauge to display Sensor 01

#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication
#include "src/MPU6050.h"  //library is downloaded from online
#include "src/I2Cdev.h"   //library is downloaded from online
#include "Wire.h"         //this arduino board is fine using Wire, so we can just go ahead and unconditionally 
                          //import this without using compiler preprocessing.


MCP2515 mcp2515(2);
struct can_frame canMsg;
struct can_frame canMsg1;

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  while (!Serial);
  Serial.begin(9600);
  
  SPI.begin();               //Begins SPI communication
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();

  //we can just use the Wire.h library for this arduino uno board, it works fine, so no preprocesser commands needed.
  Wire.begin();

  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  //cleaned up the code
  //the two for loops can be simplified into these two can messages being sent
  canMsg.can_id = 0x001;
  canMsg.can_dlc = 8;
  canMsg.data[0] = ay >> 8; //each direction (x, y, and z) needs 2 bytes (16 bits). This shifts over ay to the left by 8 to isolate only the first byte.
  canMsg.data[1] = ay ^ 255; // ^ is the xor operator. To xor a number with 255 will leave only the last 8 bits, which is the second byte we need.
  canMsg.data[2] = ax >> 8;  // rightshift by 8 throws away the second byte and only leaves the first
  canMsg.data[3] = ax ^ 255; // xor by 255 throws away the first byte and only leaves the second.
  canMsg.data[4] = az >> 8;
  canMsg.data[5] = az ^ 255;
  canMsg.data[6] = 0;
  canMsg.data[7] = 0;
  mcp2515.sendMessage(&canMsg); 

  canMsg.can_id = 0x002;
  canMsg.can_dlc = 8;
  canMsg.data[0] = gy >> 8;
  canMsg.data[1] = gy ^ 255;
  canMsg.data[2] = gx >> 8;
  canMsg.data[3] = gx ^ 255;
  canMsg.data[4] = gz >> 8;
  canMsg.data[5] = gz ^ 255;
  canMsg.data[6] = 0;
  canMsg.data[7] = 0;
  mcp2515.sendMessage(&canMsg); 
}