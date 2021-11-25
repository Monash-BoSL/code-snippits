#include <SoftwareSerial.h>


#define BAUD 9600               //radio baud rate
#define PAKLEN 32               //length of data packets  

char buffer[PAKLEN];

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  HC12.begin(BAUD);               // Serial port to HC12
  
  HC12.setTimeout(100);          //time to wait for packets//adjust as small as possible
}

void loop() {
    HC12.readBytes(buffer, PAKLEN);
    HC12.write(buffer, PAKLEN);
}
