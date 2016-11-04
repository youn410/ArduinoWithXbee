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
  Serial.println("Send packet!! --> ");
  
  xbee.readPacket(500);
  RemoteAtCommandResponse response = RemoteAtCommandResponse();
  if(xbee.getResponse().isAvailable()){
    if(xbee.getResponse().getApiId() == REMOTE_AT_COMMAND_RESPONSE){
      
      Serial.print("API ID : ");
      Serial.println(xbee.getResponse().getApiId());
      
      uint8_t frameDataLength = xbee.getResponse().getFrameDataLength();
      uint8_t* frameData = xbee.getResponse().getFrameData();
      Serial.print("Length : ");
      Serial.println(frameDataLength);
      
      Serial.print("Value : ");
      for(int i=0;i<frameDataLength;i++){
        Serial.print(frameData[i], HEX);
        Serial.print(" ");
      }
      Serial.println("");

      XBeeAddress64 fromAddr = response.getRemoteAddress64();
      for(int i=0;i<response.getValueLength();i++){
         Serial.print(response.getValue()[i], HEX);
         Serial.print(" ");
      }
      Serial.println("");
      //Serial.println(response.getRemoteAddress16(), HEX);
      
    }else{
      Serial.print("not REMOTE_AT_COMMAND_RESPONSE : ");
      Serial.println(xbee.getResponse().getApiId());
    }
  }else{
    Serial.println("Miss!!");
  }
  delay(4500);
}
