
#include <mcp2515.h>

struct can_frame frame;
MCP2515 mcp2515_send(3);
MCP2515 mcp2515_recieve(2);


void setup() {
  Serial.begin(9600);
  mcp2515_send.reset();
  mcp2515_send.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515_send.setNormalMode();

  mcp2515_recieve.reset();
  mcp2515_recieve.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515_recieve.setNormalMode();

  Serial.print("hello arduino nano is starting\n");

  frame.can_id = 0x000;
  frame.can_dlc = 5;
  frame.data[0] = 'h';
  frame.data[1] = 'e';
  frame.data[2] = 'l';
  frame.data[3] = 'l';
  frame.data[4] = 'o';
  
}

void loop() {
  //mcp2515_send.sendMessage(&frame);
  delay(400);

  Serial.print("attemepting the read again\n");
  struct can_frame theMessage;
  MCP2515::ERROR theError;

  if ((theError = mcp2515_recieve.readMessage(&theMessage)) == MCP2515::ERROR_OK) {
    Serial.print("the id was: \t");
    Serial.print(theMessage.can_id);
    Serial.print("\n");
    Serial.print("the length was: \t");
    Serial.print(theMessage.can_dlc);
    Serial.print("\n");
    for (int i = 0; i < theMessage.can_dlc; i++) {
      Serial.print(theMessage.data[i]);
      Serial.print(" ");
    }
    Serial.print("\n");
  }
  Serial.print("the error was ");
  Serial.print(theError);
  Serial.print("\n\n");

}
