// this feeds data into megasquirt over CAN bus
// pot with +5, GND, signal to A0
// MS3 setup under "CAN Receiving", "CAN ADC01", Std, identifier = 1, Size = B2U
// MS3 under Advanced Engine, "Generic Sensor Inputs", "CAN ADC01", Sensor 01, RAW
// setup gauge to display Sensor 01

#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication

#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

#define OUTPUT_READABLE_ACCELGYRO

struct can_frame canMsg;
struct can_frame canMsg1;
MCP2515 mcp2515(2);
int s1, a, b;

void setup() 
{
  while (!Serial);
  Serial.begin(9600);
  
  SPI.begin();               //Begins SPI communication
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();

  // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() 
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  for(int i = 0; i < 5; i=i+2){
    if(i==0){
      s1=ay/8;
    }
    else if(i==2){
      s1=ax/8;
    }
    else{
      s1=az/8;
    }
  Serial.println(s1);

  b=s1%256;
  //a=highByte(s1); alternate way of doing it
  //b=lowByte(s1);
  
  canMsg.can_id  = 0x001;           //CAN id as 0x001 (leading zeros matter on this field)
  canMsg.can_dlc = 8;               //CAN data length as 8
  canMsg.data[i]=s1/256;            
  canMsg.data[i+1] = b;               
  canMsg.data[6] = 0x00;
  canMsg.data[7] = 0x00;
  mcp2515.sendMessage(&canMsg);     //Sends the CAN message
  }
  for(int i = 0; i < 5; i=i+2){
    if(i==0){
      s1=gy/8;
    }
    else if(i==2){
      s1=gx/8;
    }
    else{
      s1=gz/8;
    }
  Serial.println(s1);

  b=s1%256;
  //a=highByte(s1); alternate way of doing it
  //b=lowByte(s1);
  
  canMsg.can_id  = 0x002;           //CAN id as 0x001 (leading zeros matter on this field)
  canMsg.can_dlc = 8;               //CAN data length as 8
  canMsg.data[i]=s1/256;            
  canMsg.data[i+1] = b;               
  canMsg.data[6] = 0x00;
  canMsg.data[7] = 0x00;
  mcp2515.sendMessage(&canMsg);     //Sends the CAN message
  }
  }