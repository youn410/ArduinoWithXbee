#include <XBee.h>

XBee xbee = XBee();
uint8_t payload[] = {'H', 'i'};
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x40B3C07A);
Tx64Request tx64 = Tx64Request(addr64, payload, sizeof(payload));

void setup() {
  Serial.begin(9600);
  xbee.setSerial(Serial);
}

void loop() {
  xbee.send(tx64);
  delay(1000);
  Serial.print("Send packet!! --> ");
  
  xbee.readPacket(100);
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
