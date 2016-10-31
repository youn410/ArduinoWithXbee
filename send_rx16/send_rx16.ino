#include <XBee.h>

XBee xbee = XBee();
uint8_t payload[] = {'H', 'i'};
XBeeAddress64 addr64 = XBeeAddress64(,);
Tx16Request tx16 = Tx16Request(addr64, payload, sizeof(payload));

void setup() {
  xbee.begin(9600);
}

void loop() {
  xbee.send(tx16);
  delay(50);
}
