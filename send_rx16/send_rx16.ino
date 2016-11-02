#include <XBee.h>
#include <SoftwareSerial.h>

XBee xbee = XBee();
uint8_t payload[] = { 0 , 0 };
//XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x40B3C215);
XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x0000ffff);
//Tx64Request tx64 = Tx64Request(addr64, payload, sizeof(payload));
uint8_t cmd[] = {'D', 'B'};
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(addr64, cmd);

void setup() {
  Serial.begin(9600);
  xbee.begin(Serial);
}

void loop() {
  xbee.send(remoteAtRequest);
  delay(1000);
  Serial.print("Send packet!! --> ");
  
  xbee.readPacket(500);
  if(xbee.getResponse().isAvailable()){
    if(xbee.getResponse().getApiId() == REMOTE_AT_COMMAND_RESPONSE){
      //Serial.print("REMOTE_AT_COMMAND_RESPONSE : ");
      //Serial.println(xbee.getResponse().getApiId());
      Serial.print("Value : ");
      uint8_t frameDataLength = xbee.getResponse().getFrameDataLength();
      uint8_t* frameData = xbee.getResponse().getFrameData();
      for(int i=0;i<frameDataLength;i++){
        Serial.print(frameData[i]);
        Serial.print(" ");
      }
      Serial.println("");
    }else{
      Serial.print("not REMOTE_AT_COMMAND_RESPONSE : ");
      Serial.println(xbee.getResponse().getApiId());
    }
  }else{
    Serial.println("Miss!!");
  }
  delay(4000);
}
