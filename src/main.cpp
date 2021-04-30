#include <Arduino.h>
// http://wikihandbk.com/wiki/%D0%AD%D0%BB%D0%B5%D0%BA%D1%82%D1%80%D0%BE%D0%BD%D0%BD%D1%8B%D0%B9_%D0%BA%D0%BE%D0%BC%D0%BF%D0%BE%D0%BD%D0%B5%D0%BD%D1%82:%D0%A8%D0%B8%D0%BB%D0%B4_CAN-BUS_V1.2#.D0.9F.D1.80.D0.B8.D0.B5.D0.BC.D0.BD.D1.8B.D0.B5_.D0.BC.D0.B0.D1.81.D0.BA.D0.B8_.D0.B8_.D1.84.D0.B8.D0.BB.D1.8C.D1.82.D1.80.D1.8B

// https://www.drive2.ru/l/485801071864709696/


// https://www.drive2.ru/c/516749850285442175/

//https://www.drive2.ru/c/486832413771563406/

//https://www.drive2.ru/b/508723415402676325/


#include <SPI.h>

#define CAN_2515

const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;

#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#define MAX_DATA_SIZE 8


void setup() {
    SERIAL_PORT_MONITOR.begin(9600);
    while (!SERIAL_PORT_MONITOR) {}
    while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k
        SERIAL_PORT_MONITOR.println("CAN init fail, retry...");
        delay(100);
    }
    SERIAL_PORT_MONITOR.println("CAN init ok!");

    randomSeed(millis());
}

uint32_t id;
uint8_t  type; // bit0: ext, bit1: rtr
unsigned len;
byte cdata[MAX_DATA_SIZE] = {0};

void loop() {
    type = random(4);
    if (type & 0x1) {
        // total 29 bits
        // Arduino AVR only generate up to 16 bits random number
        id = random(0x1U << 14);
        id |= (uint32_t)random(0x1U << 15) << 14;
    } else {
        id = random(0x1U << 11);
    }
    if (type & 0x2) {
        len = 0;
        // remote frame could also carry data
        // but don't do it.
        // len = random(0, MAX_DATA_SIZE + 1);
    } else {
        len = random(0, MAX_DATA_SIZE + 1);
    }

    int i;
    for (i = 0; i < len; i++) {
        cdata[i] = random(0x100);
    }

    CAN.sendMsgBuf(id, bool(type & 0x1),
                       bool(type & 0x2),
                       len,
                       cdata);

    char prbuf[32 + MAX_DATA_SIZE * 3];
    int n;

    /* Displayed type:
     *
     * 0x00: standard data frame
     * 0x02: extended data frame
     * 0x30: standard remote frame
     * 0x32: extended remote frame
     */
    static const byte type2[] = {0x00, 0x02, 0x30, 0x32};
    n = sprintf(prbuf, "TX: [%08lX](%02X) ", (unsigned long)id, type2[type]);
    // n = sprintf(prbuf, "TX: [%08lX](%02X) ", id, type);

    for (i = 0; i < len; i++) {
        n += sprintf(prbuf + n, "%02X ", cdata[i]);
    }
    SERIAL_PORT_MONITOR.println(prbuf);

    unsigned d = 2000;//random(50);
    SERIAL_PORT_MONITOR.println(d);
    delay(d);
}
// END FILE
