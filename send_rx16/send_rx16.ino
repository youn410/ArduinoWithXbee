#include <XBee.h>
#include <SoftwareSerial.h>

XBee xbee = XBee();
uint8_t payload[] = { 0 , 0 };
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x40B3C215);
//XBeeAddress64 addr64 = XBeeAddress64(0xFFFFFFFF, 0xFFFFFFFF);
Tx64Request tx64 = Tx64Request(addr64, payload, sizeof(payload));

void setup() {
  Serial.begin(9600);
  xbee.begin(Serial);
}

void loop() {
  xbee.send(tx64);
  delay(1000);
  Serial.print("Send packet!! --> ");
  
  xbee.readPacket(500);
  if(xbee.getResponse().isAvailable()){
    if(xbee.getResponse().getApiId() == TX_STATUS_RESPONSE){
      Serial.print("TX_STATUS_RESPONSE : ");
      Serial.println(xbee.getResponse().getApiId());
    }else{
      Serial.print("not TX_STATUS_RESPONSE : ");
      Serial.println(xbee.getResponse().getApiId());
    }
  }else{
    Serial.println("Miss!!");
  }
  delay(4000);
}
