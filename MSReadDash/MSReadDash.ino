// CAN receiving
#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(10); // SPI CS Pin 10

// megasquirt variablez
int RPM, TPS, CLT;

// can variables
unsigned long previousMillis=0;
int delayPeriod=1000;

void setup() {
Serial.begin(115200);

mcp2515.reset();
mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
mcp2515.setNormalMode();

Serial.println("Hello MCP2515 Arduino");

}

void loop() {
Serial.println(mcp2515.readMessage(&canMsg));
if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
/*
Serial.print("CanMsg.can_id: ");
Serial.print(canMsg.can_id); // print ID
Serial.print(" "); 
Serial.print("CanMsg.can_dlc: ");
Serial.print(canMsg.can_dlc, HEX); // print DLC
Serial.print(" ");
*/
/*
for (int i = 0; i<canMsg.can_dlc; i++) { // print the data
Serial.print(canMsg.data[i],HEX);
Serial.print(" ");
}
Serial.println(); 
*/
switch (canMsg.can_id) {
case 1512: // dash broadcasting group
RPM = (float)(word(canMsg.data[2], canMsg.data[3]));
CLT = (float)(word(canMsg.data[4], canMsg.data[5])); CLT = (CLT / 10);
TPS = (float)(word(canMsg.data[6], canMsg.data[7])); TPS = (TPS / 10);
break;
}
previousMillis=0; // reset no data timer
}
else { // no CAN bus data coming in
unsigned long currentMillis = millis();
if(previousMillis == 0){
previousMillis = currentMillis; // entered no data timer
}
else if(currentMillis - previousMillis > delayPeriod) { // no data timer expired
previousMillis = currentMillis;
RPM = -999;
CLT = -999;
TPS = -999;
}

}
Serial.print("RPM: ");
Serial.print(RPM);
Serial.print(" CLT: ");
Serial.print(CLT);
Serial.print(" TPS: ");
Serial.println(TPS);
}