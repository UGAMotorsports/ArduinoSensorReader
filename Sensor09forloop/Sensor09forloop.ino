// this feeds data into megasquirt over CAN bus
// pot with +5, GND, signal to A0
// MS3 setup under "CAN Receiving", "CAN ADC01", Std, identifier = 1, Size = B2U
// MS3 under Advanced Engine, "Generic Sensor Inputs", "CAN ADC01", Sensor 01, RAW
// setup gauge to display Sensor 01

#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication

struct can_frame canMsg;
struct can_frame canMsg1;
MCP2515 mcp2515(2);

int sensor01=A0;
int s1, a, b;

void setup() 
{
  while (!Serial);
  Serial.begin(9600);
  
  SPI.begin();               //Begins SPI communication
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();

}

void loop() 
{
  for(int i = 0; i < 200; i++){
  s1=i;
  Serial.println(i);
  canMsg.data[0]=s1/256;
  b=s1%256;
  //a=highByte(s1); alternate way of doing it
  //b=lowByte(s1);
  
  canMsg.can_id  = 0x001;           //CAN id as 0x001 (leading zeros matter on this field)
  canMsg.can_dlc = 8;               //CAN data length as 8
  //canMsg.data[0] = a;               
  canMsg.data[1] = b;               
  canMsg.data[2] = 0x00;            
  canMsg.data[3] = 0x00;
  canMsg.data[4] = 0x00;
  canMsg.data[5] = 0x00;
  canMsg.data[6] = 0x00;
  canMsg.data[7] = 0x00;
  mcp2515.sendMessage(&canMsg);     //Sends the CAN message

  delay(10);
  }
  
}