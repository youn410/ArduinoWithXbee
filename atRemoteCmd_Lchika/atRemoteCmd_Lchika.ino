#include <XBee.h>
#include <SoftwareSerial.h>

uint8_t p2Cmd[] = {'D', '1'}; // Pin19のデジタルアウトプットインプット
uint8_t p2Low[] = {0x04}; // Set Low
uint8_t p2High[] = {0x05}; // Set High

XBee xbee = XBee();
//XBeeAddress64 remoteAddress = XBeeAddress64(0x0013A200, 0x40B3C215);
XBeeAddress64 remoteAddress = XBeeAddress64(0x00000000, 0x0000ffff);
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, p2Cmd, p2Low, sizeof(p2Low));

void setup() {
  Serial.println("Start Led ON/OFF");
  delay(2000);
  Serial.begin(9600);
  delay(1000);
  xbee.begin(Serial);
}

void loop() {
  remoteAtRequest.setCommandValue(p2Low);
  remoteAtRequest.setCommandValueLength(sizeof(p2Low));
  xbee.send(remoteAtRequest);
  xbee.readPacket(1000);
  Serial.print("Low ");
  Serial.println(xbee.getResponse().isAvailable());
  delay(2000);

  remoteAtRequest.setCommandValue(p2High);
  remoteAtRequest.setCommandValueLength(sizeof(p2High));
  xbee.send(remoteAtRequest);
  xbee.readPacket(1000);
  Serial.print("High ");
  Serial.println(xbee.getResponse().isAvailable());
  delay(2000);
}
