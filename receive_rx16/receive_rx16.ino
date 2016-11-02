#include <SpacebrewYun.h>

#include <XBee.h>
#include <SoftwareSerial.h>

XBee xbee = XBee();
Rx16Response rx16 = Rx16Response();

void setup() {
  Serial.begin(9600);
  xbee.begin(Serial);
}

void loop() {
  xbee.readPacket(500);
  if(xbee.getResponse().isAvailable()){
    if(xbee.getResponse().getApiId() == RX_16_RESPONSE){
      xbee.getResponse().getRx16Response(rx16);
      Serial.print("RSSI : ");
      Serial.println(rx16.getRssi());
    }
  }else{
    Serial.println("Cant read packet!");
  }
  delay(1000);
}
