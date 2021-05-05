#include <Arduino.h>
// http://wikihandbk.com/wiki/%D0%AD%D0%BB%D0%B5%D0%BA%D1%82%D1%80%D0%BE%D0%BD%D0%BD%D1%8B%D0%B9_%D0%BA%D0%BE%D0%BC%D0%BF%D0%BE%D0%BD%D0%B5%D0%BD%D1%82:%D0%A8%D0%B8%D0%BB%D0%B4_CAN-BUS_V1.2#.D0.9F.D1.80.D0.B8.D0.B5.D0.BC.D0.BD.D1.8B.D0.B5_.D0.BC.D0.B0.D1.81.D0.BA.D0.B8_.D0.B8_.D1.84.D0.B8.D0.BB.D1.8C.D1.82.D1.80.D1.8B

// https://www.drive2.ru/l/485801071864709696/


// https://www.drive2.ru/c/516749850285442175/

//https://www.drive2.ru/c/486832413771563406/

//https://www.drive2.ru/b/508723415402676325/
// https://habr.com/ru/post/442184/
// http://arduino.ru/forum/apparatnye-voprosy/arduino-uno-i-mcp2515-can?page=13
// https://it4it.club/topic/38-arduino-v-avtomobile/

//https://en.wikipedia.org/wiki/OBD-II_PIDs#Mode_01


// CAN Send Example
//

#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10);     // Set CS to pin 10

void setup()
{
  Serial.begin(9600);

  // Initialize MCP2515 running at 8MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
  CAN0.enOneShotTX();
}

byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

void loop()
{
  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  byte sndStat = CAN0.sendMsgBuf(0x100, 0, 8, data);
  if(sndStat == CAN_OK){
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }
  delay(2000);   // send data per 2000ms
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/ 
