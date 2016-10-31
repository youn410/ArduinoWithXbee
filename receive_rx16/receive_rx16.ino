#include <Printers.h>
#include <XBee.h>
#include <Wire.h>

XBee xbee = XBee();
Rx16Response rx16 = Rx16Response();

void setup() {
  Serial.begin(9600);
  xbee.setSerial(Serial);
}

void loop() {
  xbee.readPacket(100);
  if(xbee.getResponse().isAvailable()){
    if(xbee.getResponse().getApiId() == RX_16_RESPONSE){
      xbee.getResponse().getRx16Response(rx16);
      Serial.print("RSSI : ");
      Serial.println(rx16.getRssi());
    }
  }else{
    Serial.println(xbee.getResponse().isAvailable());
  }
}
