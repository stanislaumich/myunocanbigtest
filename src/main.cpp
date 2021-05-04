#include <Arduino.h>
// http://wikihandbk.com/wiki/%D0%AD%D0%BB%D0%B5%D0%BA%D1%82%D1%80%D0%BE%D0%BD%D0%BD%D1%8B%D0%B9_%D0%BA%D0%BE%D0%BC%D0%BF%D0%BE%D0%BD%D0%B5%D0%BD%D1%82:%D0%A8%D0%B8%D0%BB%D0%B4_CAN-BUS_V1.2#.D0.9F.D1.80.D0.B8.D0.B5.D0.BC.D0.BD.D1.8B.D0.B5_.D0.BC.D0.B0.D1.81.D0.BA.D0.B8_.D0.B8_.D1.84.D0.B8.D0.BB.D1.8C.D1.82.D1.80.D1.8B

// https://www.drive2.ru/l/485801071864709696/


// https://www.drive2.ru/c/516749850285442175/

//https://www.drive2.ru/c/486832413771563406/

//https://www.drive2.ru/b/508723415402676325/
// https://habr.com/ru/post/442184/
// http://arduino.ru/forum/apparatnye-voprosy/arduino-uno-i-mcp2515-can?page=13
// https://it4it.club/topic/38-arduino-v-avtomobile/


#include <SPI.h>
#define CAN_2515

// For Arduino MCP2515 Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;

#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif

void setup() {
    SERIAL_PORT_MONITOR.begin(9600);
    while(!Serial){};

    while (CAN_OK != CAN.begin(CAN_500KBPS,MCP_8MHz)) {             // init can bus : baudrate = 500k
        SERIAL_PORT_MONITOR.println("CAN init fail, retry...");
        delay(100);
    }
    SERIAL_PORT_MONITOR.println("CAN init ok!");
}

unsigned char stmp[8] = {1, 2, 3, 9, 8, 7, 5, 5};
void loop() {
    // send data:  id = 0xDF, standrad frame, data len = 8, stmp: data buf
 
    CAN.sendMsgBuf(0xDF, 0, 8, stmp);
    delay(2000);                       // send data per 2000ms
    SERIAL_PORT_MONITOR.println("CAN BUS sendMsgBuf ok!");
    SERIAL_PORT_MONITOR.println(stmp[7]);
}